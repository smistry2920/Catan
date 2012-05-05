#include "Player.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>


//constructor
Player::Player(){
    srand ( time(NULL) );
    this->victoryPoints_= 0;
    this->roadLength_   = 0;
    this->armySize_     = 0;
    char color = 'g';
    this->playerColor_  = color;
    this->yellow_       = 2;
    this->lightGreen_   = 2;
    this->darkGreen_    = 4;
    this->blue_         = 0;
    this->red_          = 4;

    this->knight_       = 0;
    this->victoryPointCard_ = 0;
    this->roadBuilder_  = 0;
    this->monopoly_     = 0;
    this->yearOfPlenty_ = 0;
}

Player::~Player(){
//destroy the lists
}

//public function for rolling dice
int Player::roll(){

    return rand() %6 +1;
}

//This function shows the basic numbers for a given player.
void Player::checkStats(){
    cout<<"Victory Points: "<<victoryPoints_<<endl;
    cout<<"Army Size: "<<armySize_<<endl;
    cout<<"Road Length: "<<roadLength_<<endl;
    cout<<"Num of Resources: " <<numberOfResources()<<endl;
    cout<<"Num of Development: "<<numberOfDevelopments()<<endl<<endl;
}

//this private function calculates the total number of resources a player has
int Player::numberOfResources(){
    int total = yellow_;
    total = total + lightGreen_;
    total = total + darkGreen_;
    total = total + blue_;
    total = total + red_;
    return total;
}

//***Returns the amount of resources are in your hand. Should use this function above
//  because it will be able to send QStringList to GUI

QString Player::outputHand()
{
       QString hand;
//       QString wheat, sheep, lumber, stone, brick;

        hand.append("wheat: ");
        hand.append(QString::number(yellow_));
        qDebug() << "FUCKING YELLOW" << yellow_;

        hand.append("\nsheep: ");
        hand.append(QString::number(lightGreen_));

        hand.append("\nlumber: ");
        hand.append(QString::number(darkGreen_));

        hand.append("\nstone: ");
        hand.append(QString::number(blue_));

        hand.append("\nbrick: ");
        hand.append(QString::number(red_));

//       wheat.append(QString("%1").arg(yellow_));
//       sheep.append(QString("%1").arg(lightGreen_));
//       lumber.append(QString("%1").arg(darkGreen_));
//       stone.append(QString("%1").arg(blue_));
//       brick.append(QString("%1").arg(red_));


        qDebug() << hand;
        return hand;
}


//this private function calculates the
//totalnumber of development cards a player has
int Player::numberOfDevelopments(){
    int total = knight_;
    total +=victoryPointCard_;
    total +=roadBuilder_;
    total +=monopoly_;
    total +=yearOfPlenty_;
    return total;
}


/***use this altered function to output Qstrings instead of cout
**QStringList Player::seeDevelopments(){
    QStringList developmentCards;
    QString Knights, VictoryPoint, RoadBuilder, Monopoly, YearofPlenty;

    Knights.append(QString("%1").arg(knight_));
    VictoryPoint.append(QString("%1").arg(victoryPointCard_));
    RoadBuilder.append(QString("%1").arg(roadBuilder_));
    Monopoly.append(QString("%1").arg(monopoly_));
    YearofPlenty.append(QString("%1").arg(yearOfPlenty_));

    return developmentCards << Knights << VictoryPoint << RoadBuilder << Monopoly << YearofPlenty;
}*/

//This public functionallows a player to see
//which resources he or she has
void Player::seeResources(){
    cout<<"Yellow: "<<yellow_<<endl;
    cout<<"Light Green: "<<lightGreen_<<endl;
    cout<<"Dark Green: "<<darkGreen_<<endl;
    cout<<"Blue: "<<blue_<<endl;
    cout<<"Red: "<<red_<<endl<<endl;
    seeDevelopments();
}

//This public functionallows a player to see
//which development cards he or she has
void Player::seeDevelopments(){
    cout<<"Knights: "<<knight_<<endl;
    cout<<"Victory Point Card(s): "<<victoryPointCard_<<endl;
    cout<<"Road Builder: "<<roadBuilder_<<endl;
    cout<<"Monoply: "<<monopoly_<<endl;
    cout<<"Year Of Plenth: "<<yearOfPlenty_<<endl<<endl;
}

/*This public function has to be called for each opponent (everyone but the player you are on).
It checks to see if a settlement is being placed in a spot that would
block 2 consecutive roads of an opponent. If it returns false, there is no match. If it returns 
for any opponent, then the settlement can not be placed there. */
bool Player::areRoadsBlockingSettlement(int location){
    list<roads>::iterator current = pavement.begin();
    int size = pavement.size();
    int matches = 0;
    for(int i = 0; i<size; ++i){
        if(current->top == location || current->bottom == location)
            matches++;
        current++;
    }

    if(matches<2)
        return false;
    else
        return true;
}


/*This public function has to be called for each opponent (everyone but the player you are on).
It checks to see if they have a city or settlement at the location input. If it returns true FOR
ANYOE, thereis a match and the current player can now place a road down. If it returns false FOR
EVERYONE, then the player can place the road. */
bool Player::isSettlementBlockingRoad(int location){
    list<settlement>::iterator current = pieces.begin();
    int size = pieces.size();

    for(int i = 0; i<size; ++i){
        if(current->cityNumber == location)
            return true;
        current++;
    }
    return false;
}

/* This private function checks to see if you have  city/settlement already in a location
thereby allowing you to place a road.*/
bool Player::roadOffOwnCity(int top, int bottom){

    list<settlement>::iterator current = pieces.begin();
    int size = pieces.size();
    for(int i = 0; i<size; ++i){
        if(current->cityNumber == top || current->cityNumber== bottom)
            return true;
        current++;
    }
    return false;
}

/*private function that determines if a road can be placed. Returns -1 if absolutly true, 0 if false. An integer>0 will be returned
if it finds a match to a the players own road in which case we need to check to see if other players have a city/settlement
in that corresponding integer location. */
int Player::checkRoad(){
    int top, bottom;//these are somehow the known values of the road that will be placesd
    
    bool offCity = roadOffOwnCity(top, bottom);
    if (offCity==true)
        return -1;

    list<roads>::iterator current = pavement.begin();
    int size =pavement.size();
    for(int i = 0; i<size; ++i){
        if(current->top == top || current->bottom == top)
            return top;
        else if (current->top == bottom || current->bottom ==bottom)
            return bottom;
        current++;
    }

    //by this point, it exists off no roads, and no other cities/settlements
    return 0;

}


//public function allows player to see if they can purchase a road
bool Player::affordRoad(){
    if(red_>0 && darkGreen_>0)
        return 1;
    cout<<"You do not have the resources to purchase a road!"<<endl<<endl;
    return 0;

}

//this public function allows a player to purchase a road
void Player::buyRoad(){
    //do action to place road
    red_--;
    darkGreen_--;

    struct roads ro;
    //filling in the .top and .bottom @suneil
    ro.top = 0;
    ro.bottom = 0;
    //end @suneil
    pavement.push_front(ro);

}

/***Same function just outputs a QString
QString Player::buyRoad(){

QString roadFails = "You do not have the resources to purchase a road!";
QString roadWorks = "Road Purchased";

    red_--;
    darkGreen_--;

    struct roads ro;
    //filling in the .top and .bottom @suneil
    ro.top = 0;
    ro.bottom = 0;
    //end @suneil
    pavement.push_front(ro);
}*/

//public function check to see if player can afford settlement
bool Player::affordSettlement(){
        if(red_ >0 && darkGreen_ >0 && lightGreen_ >0 && yellow_>0)
            return 1;
        cout<<"You do not have the resources to purchase a settlement!"<<endl<<endl;
        return 0;
}


//This public fuction allows a player to purchase a settlement.
void Player::buySettlement(QString line){

    //Format is city ID|left Color|left node|right Color|right node|top color|top node|port
    bool ok = true;
    char lC;
    char rC;
    char tC;
    char port;
    QString ID_temp = line.section("|",0,0);
    int ID = ID_temp.toInt(&ok, 10);
    ID_temp = line.section("|",1,1);

    {
        QByteArray ba = ID_temp.toLocal8Bit();
        const char *cstring = ba.data();
        lC = *cstring;
    }

    ID_temp = line.section("|",2,2);
    int lN = ID_temp.toInt(&ok, 10);
    ID_temp = line.section("|",3,3);
    {
        QByteArray ba = ID_temp.toLocal8Bit();
        const char *cstring = ba.data();
        rC = *cstring;
    }

    ID_temp = line.section("|",4,4);
    int rN = ID_temp.toInt(&ok, 10);
    ID_temp = line.section("|",5,5);
    {
        QByteArray ba = ID_temp.toLocal8Bit();
        const char *cstring = ba.data();
        tC = *cstring;
    }
    ID_temp = line.section("|",6,6);
    int tN = ID_temp.toInt(&ok, 10);
    ID_temp = line.section("|", 7,7);
    {
        QByteArray ba = ID_temp.toLocal8Bit();
        const char *cstring = ba.data();
        port = *cstring;
    }

    cout<<"buying sett:"<<endl;
    cout<<ID<<lC<<lN<<rC<<rN<<tC<<tN<<port<<endl;



    //do action to place settlement
    red_--;
    darkGreen_--;
    yellow_--;
    lightGreen_--;
    victoryPoints_++;

    struct settlement set;
    set.city = 1;

    set.cityNumber  = ID;
    set.left.node   = lN;
    set.left.color  = lC;
    set.right.node  = rN;
    set.right.color = rC;
    set.top.node    = tN;
    set.top.color   = tC;

    set.port = port;

    pieces.push_front(set);//add city to list.


}


bool Player::affordCity(){
    if(blue_>=3 && yellow_>=2)
        return 1;
    cout<<"You do not have the resources to purchase a city!"<<endl<<endl;
    return 0;


}

/*This public function does the action of changing a settlement into a city and
charging the respective resources.*/
void Player::buyCity(QString line){

    bool ok = true;
    QString ID_temp = line.section("|",0,0);
    int ID = ID_temp.toInt(&ok, 10);

    cout<<"In buy city, city id: "<<ID<<endl;


    //find settlement and change it to a city
    list<settlement>::iterator current = pieces.begin();
    int size = pieces.size();

    for(int i = 0; i<size; i++){
        if(current->cityNumber==ID)
            current->city = 2;
        current++;
    }

    //charge user
    blue_ -= 3;
    yellow_ -= 2;
    victoryPoints_++;

}


bool Player::affordDevelopmentCard(){
    if(blue_>0 && yellow_>0 && lightGreen_>0)
        return 1;

    cout<<"You do not have the resources to purchase a developmentCard!"<<endl<<endl;
    return 0;
}

/*This public function lets you buy a development card.
It will have to call the private function UNKOWNRIGHTNOW
to figure out which card you get
*/
void Player::buyDevelopmentCard(){
    //do action to fetch developmentCard
    blue_--;
    yellow_--;
    lightGreen_--;
    int num = rand() %25;

    if(num<2)
        yearOfPlenty_++;
    else if (num<4)
        monopoly_++;
    else if (num<6)
        roadBuilder_++;
    else if(num<11)
        victoryPointCard_++;
    else
        knight_++;


}

void Player::changeColor(char &color){
    playerColor_ = color;
}

/*This public function searches through all the settlements/cities
a player has to give them the respective resources gained on
a roll. */


void Player::gainResources(int roll, Node onlyNode){
    list<settlement>::iterator current = pieces.begin();

    int size = pieces.size();
    //need to know how the city will be attached to a the color;

    for(int i = 0; i<size; i++){
        if(onlyNode.findNode(current->top.node) == roll){
            addProperColor(current->top.color, current->city);
        }
        if(onlyNode.findNode(current->left.node) == roll){
            addProperColor(current->left.color, current->city);
        }
        if(onlyNode.findNode(current->right.node) == roll){
            addProperColor(current->right.color, current->city);
        }
        
        current++;
    }
   
}

/*This is a private function called by gainResources. It finds which 
of the players resources to add to given that he his settlement/city
has a part matching a number*/
void Player::addProperColor(char color, int city){
    if(color=='y'){
        yellow_ += city;
    }else if(color=='l'){
        lightGreen_ +=city;
    }else if(color=='d'){
        darkGreen_ +=city;
    }else if(color=='b'){
        blue_ += city;
    }else { //color = red
        red_ += city;
    }

}


/*this is a public function where you decide what you want to trade for.
The private function whichCardsToTrade decides which cards you will give up to attain the
card you decide on here */

void Player::convertResources(){
    seeResources();
    
    cout<<"1) Trade for yellow"<<endl;
    cout<<"2) Trade for light green"<<endl;
    cout<<"3) Trade for dark green"<<endl;
    cout<<"4) Trade for blue"<<endl;
    cout<<"5) Trade for red"<<endl;
    cout<<"0) Cancel"<<endl<<endl;
    int input;
    cin>>input;
    if(input==1 || input==2 || input==3 || input==4 || input==5){
        this->whichCardsToTrade();

        if(input==1)
            this->yellow_++;
        else if (input==2)
            this->lightGreen_++;
        else if(input==3)
            this->darkGreen_++;
        else if(input==4)
            this->blue_++;
        else if(input==5)
            this->red_++;

    }else
        cout<<"Cancelled"<<endl;
    
}

/***Same function above just uses Qstrings to output
QString Player::convertResources(){
    seeResources();

    QString convertPass = "Conversion successful!";
    QString convertCancel = "Conversion Cancelled";

    //Need to have this either printed to an ouput or made into a pop-up window
    cout<<"1) Trade for yellow"<<endl;
    cout<<"2) Trade for light green"<<endl;
    cout<<"3) Trade for dark green"<<endl;
    cout<<"4) Trade for blue"<<endl;
    cout<<"5) Trade for red"<<endl;
    cout<<"0) Cancel"<<endl<<endl;
    int input;
    cin>>input;         //Need to find button that corresponds with this
    if(input==1 || input==2 || input==3 || input==4 || input==5){
        this->whichCardsToTrade();

        if(input==1)
            this->yellow_++;
        else if (input==2)
            this->lightGreen_++;
        else if(input==3)
            this->darkGreen_++;
        else if(input==4)
            this->blue_++;
        else if(input==5)
            this->red_++;
        return convertPass;

    }else
        return convertCancel;

}*/

/*this private function lets you trade cards with the bank.
it finds the conversion factor to get a trade. The defualt
is 4, it has to check ports to see if you can get a better deal though. */

void Player::whichCardsToTrade(){
    //maybe show the conversion too rather than just assuming the person knows

    int yellow = findBestTrade('y');
    int lightGreen = findBestTrade('l');
    int darkGreen = findBestTrade('d');
    int blue = findBestTrade('b');
    int red = findBestTrade('r');

    cout<<"1) Give up yellow        "<<yellow<<":1"<<endl;
    cout<<"2) Give up light green   "<<lightGreen<<":1"<<endl;
    cout<<"3) Give up dark green    "<<darkGreen<<":1"<<endl;
    cout<<"4) Give up blue          "<<blue<<":1"<<endl;
    cout<<"5) Give up red           "<<red<<":1"<<endl;
    cout<<"0) Cancel"<<endl;
    int input;
    cin>>input;

    if(input==1 || input==2 || input==3 || input==4 || input==5){

        if(input==1 && this->yellow_ >=yellow){
            this->yellow_ -=yellow;
        }else if (input==2 &&this->lightGreen_ >=lightGreen){
            this->lightGreen_ -=lightGreen;
        }else if(input==3 && this->darkGreen_ >=darkGreen){
            this->darkGreen_-=darkGreen;
        }else if(input==4 && this->blue_ >=blue){
            this->blue_ -=blue;
        }else if(input==5 && this->red_ >= red){
            this->red_ -=red;
        } else{
            cout<<"Not enough resources for conversion!"<<endl<<endl;        
        }
        seeResources();

    }else
        cout<<"Cancelled"<<endl;
}

/*Same as function above just has output QStrings
QString Player::whichCardsToTrade(){
    //maybe show the conversion too rather than just assuming the person knows

    QString insuffientResources = "Not enough resources for conversion!"
    QString tradeCancel = "Cancelled";

    int yellow = findBestTrade('y');
    int lightGreen = findBestTrade('l');
    int darkGreen = findBestTrade('d');
    int blue = findBestTrade('b');
    int red = findBestTrade('r');

    //Need to make pop up window that will display these options
    cout<<"1) Give up yellow        "<<yellow<<":1"<<endl;
    cout<<"2) Give up light green   "<<lightGreen<<":1"<<endl;
    cout<<"3) Give up dark green    "<<darkGreen<<":1"<<endl;
    cout<<"4) Give up blue          "<<blue<<":1"<<endl;
    cout<<"5) Give up red           "<<red<<":1"<<endl;
    cout<<"0) Cancel"<<endl;
    int input;
    cin>>input;       //Need a way to take in this value might need to make more than one function

    if(input==1 || input==2 || input==3 || input==4 || input==5){

        if(input==1 && this->yellow_ >=yellow){
            this->yellow_ -=yellow;
        }else if (input==2 &&this->lightGreen_ >=lightGreen){
            this->lightGreen_ -=lightGreen;
        }else if(input==3 && this->darkGreen_ >=darkGreen){
            this->darkGreen_-=darkGreen;
        }else if(input==4 && this->blue_ >=blue){
            this->blue_ -=blue;
        }else if(input==5 && this->red_ >= red){
            this->red_ -=red;
        } else{
            return insuffientResources;
        }
        seeResources();

    }else
        return tradeCancel;
}*/

/*This is a private function called by whichCardsToTrade.
It takes a given color and determines if you have a port that matches it.
Otherwise, it searches for a 3:1 port, and if that doesn't exist returns 4
(the default).*/
int Player::findBestTrade(char color){
    list<settlement>::iterator current = pieces.begin();

    int tradeDefault = 4;

    int size = pieces.size();
    for(int i = 0; i<size; ++i){
        if(current->port == color)
            return 2;
        else if(current->port == '3')
            tradeDefault=3;

        current++;
    }

    return tradeDefault;

}

/*This public function removes 50% +1 (if odd) of a players card count.
It should be called for every player and removes the cards at
random. */
void Player::removeCardsOn7(){
    int num = numberOfResources();

    if(num>7){
        num = num/2 + num%2; //number of cards that will be removed
        for(int i = 0; i<num; ++i){
            removeRandomCard(); //removes card at random in this function we dont care what is returned.
        }
    }
}

/* This private function can be called by either the knight function,
or the removeCardsOn7 function where it removes a random card from a players hand. 
returns y on yellow, l on lightblue, etc. It returns '0' on if a player has no
cards to give!*/

char Player::removeRandomCard(){
    int i = rand() %5;
    //if(numberOfResources() <=7) shouldn't need this because of the caller function. It should also be re-used for when the robber is used.
    //   return '0';
    if(numberOfResources()!=0){
        if(i ==0){
            if(yellow_ >0){
                yellow_--;
                return 'y';
            }
            else
                removeRandomCard();
        }
        if(i ==1){
            if(lightGreen_ >0){
                lightGreen_--;
                return 'l';
            }
            else
                removeRandomCard();
        }
        if(i ==2){
            if(darkGreen_ >0){
                darkGreen_--;
                return 'd';
            }
            else
                removeRandomCard();
        }
        if(i ==3){
            if(blue_ >0){
                blue_--;
                return 'b';
            }
            else
                removeRandomCard();
        }
        if(i ==4){
            if(red_ >0){
                red_--;
                return 'r';
            }
            else
                removeRandomCard();
        }
    }
    return '0';
}

/*This public function deteremines if the player has a city/settlement on a particular node(this is used for the robber)
  */
bool Player::nodeOnRobber(int robber){
    list<settlement>::iterator current = pieces.begin();

    int size = pieces.size();
    for(int i = 0; i<size; ++i){
        if(current->top.node ==robber || current->right.node == robber || current->left.node == robber)
            return true;

        current++;
    }

    return false;
}

void Player::addCard(char color){
    if(color=='l')
        lightGreen_++;
    else if (color=='d')
        darkGreen_++;
    else if (color=='r')
        red_++;
    else if (color=='y')
        yellow_++;
    else if(color=='b')
        blue_++;
}

/*This public function decides which development card
the player wants to play. The main function then uses if
statements to decide what to do next. */
int Player::playDevCard(){
    cout<<"Which Development Card would you like to play?"<<endl;
    cout<<"1) Knight Card"<<endl;
    cout<<"2) Victory Point"<<endl;
    cout<<"3) Road Builder"<<endl;
    cout<<"4) Monopoly"<<endl;
    cout<<"5) Year Of Plenty"<<endl;
    cout<<"6) Cancel"<<endl;
    int input;
    cin>>input;

    if(input==1 ){
        if(knight_ >0){
            return 1;
        }
        cout<<"You have no Knight Cards!"<<endl;
    }
    else if (input==2){
        if(victoryPointCard_>0){
            playVictoryPoint();
            return 2;
        }
        cout<<"You have no Victor Point Cards!"<<endl;
    }
    else if (input ==3){
        if(roadBuilder_>0){
            //buildRoadSomehow, we'd need to call same functions
            //as buy road twice without actually buying (spending resources).
            //roadBuilder--;
            return 3;
        }
        cout<<"You have no Road Builder Cards!"<<endl;
    }
    else if (input ==4){
        if(monopoly_>0){
            monopoly_--;
            return 4;
        }
        cout<<"You have no Monopoly Cards!"<<endl;
    }
    else if (input ==5){
        if(yearOfPlenty_>0){
            yearOfPlenty_--;
            return 5;
        }
        cout<<"You have no Year Of Plenty Cards!"<<endl;
    }
    
    return 0;
}

/* This public function playMonoply decides which card the player will take from the other players. A subsequent function should be called for each remainign player to take all of those cards and give it to the one player. */
char Player::playMonoply(){

    cout<<"Which card do you want to remove from the other players?"<<endl;
    cout<<"1) Yellow"<<endl;
    cout<<"2) Light Green"<<endl;
    cout<<"3) Dark Green"<<endl;
    cout<<"4) Blue"<<endl;
    cout<<"5) Red"<<endl;
    cout<<"6) Cancel"<<endl;
    int input;
    cin>>input;

    if(input == 1)
        return 'y';
    else if(input ==2)
        return 'l';
    else if(input ==3)
        return 'd';
    else if(input ==4)
        return 'b';
    else if(input ==5)
        return 'r';

    return '0';
}

/* This public function removes all of a certain card from
a player and returns that number. This function is relevant for when a player is playing the Monopoly card, and should be called for all players. All of the integers should be returns and will be later rewarded to the player playing the card. */
int Player::removeAllOneCardFromPlayer(char color){

    int num = 0;
    if(color =='y'){
        num = yellow_;
        yellow_ = 0;
    } else if (color =='l'){
        num = lightGreen_;
        lightGreen_ = 0;
    } else if (color =='d'){
        num =darkGreen_;
        darkGreen_ = 0;
    } else if (color =='b'){
        num = blue_;
        blue_ = 0;
    }else{
        num = red_;
        red_ = 0;
    }
        return num;
        
}

/*This public function is the last call for after a player plays the monopoly card. It takes the number of cards to add, and the color to add to for inputs and then does the simple math to add it. */
void Player::gainCardsFromMonopoly(int num, char color){
    knight_--;
    if(color =='y'){
        yellow_ += num;
    } else if (color =='l'){
        lightGreen_ += num;
    } else if (color =='d'){
        darkGreen_ += num;
    } else if (color =='b'){
        blue_ += num;
    }else{
        red_ += num;
    }
}

/*This is a private function called to give the player a victoryPint */
void Player::playVictoryPoint(){
    victoryPointCard_--;
    victoryPoints_++;
}

void Player::playYearOfPlenty(){
    cout<<"You gain two resources from the bank"<<endl;
    cout<<"1) Yellow"<<endl;
    cout<<"2) Light Green"<<endl;
    cout<<"3) Dark Green"<<endl;
    cout<<"4) Blue"<<endl;
    cout<<"5) Red"<<endl;
    yearOfPlenty_--;

    int input;
    for(int i = 0; i<2; i++){
        cin>>input;
        if(input ==1 || input ==2 || input ==3 ||
            input ==4 || input ==5){
            if(input == 1){
                yellow_++;
                cout<<"Yellow";
            } else if(input == 2){
                lightGreen_++;
                cout<<"Light Green";
            } else if(input == 3){
                darkGreen_++;
                cout<<"Dark Green";
            } else if(input ==4){
                blue_++;
                cout<<"Blue";
            } else if(input ==5){
                red_++;
                cout<<"Red";        
            }
            cout<<" added";
            if(i == 0)
                cout<<"Chose next Card."<<endl;
        }
        else
           --i;
    }
}

void Player::collectOriginalCards(Node onlyNode){
    list<settlement>::iterator current = pieces.begin();

    //need to know how the city will be attached to a the color;

    for(int i = 2; i<=12; i++){
        if(onlyNode.findNode(current->top.node) == i){
            addProperColor(current->top.color, current->city);
        }
        if(onlyNode.findNode(current->left.node) == i){
            addProperColor(current->left.color, current->city);
        }
        if(onlyNode.findNode(current->right.node) == i){
            addProperColor(current->right.color, current->city);
        }

    }

}

