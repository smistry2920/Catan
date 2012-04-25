#include<iostream>
#include<string>
#include<list>

using namespace std;

class Player{

    private:
    string name_;
    int victoryPoints_;
    int roadLength_;
    int armySize_;
    char playerColor_;

    //resources
    int yellow_;     //y
    int lightGreen_; //l
    int darkGreen_;  //d
    int blue_;       //b
    int red_;        //r

    //developmentCards
    int knight_;
    int victoryPointCard_;
    int roadBuilder_;
    int monopoly_;
    int yearOfPlenty_;

    struct roads{
        int top;
        int bottom;
    };

    struct component{
        int number;
        char color; //y, l, d, b, or r 
    };
 
    struct settlement{
        int city; //1 if settlement, 2 if city.
        component top;
        component left;
        component right;
        int cityNumber;
        char port; //port will be the same as color y, l, d, b, r, or of course '3' for the 3:1 port
    };

    list<settlement> pieces;
    list<roads> pavement;

    void checkLongestRoad();
    void checkLargestArmy();

    //called from checkStats()
    int  numberOfResources();
    int  numberOfDevelopments();

    //called from buyItem()
    void buyRoad();
    void buySettlement();
    void buyCity();
    void buyDevelopmentCard();

    //Trading cards
    void whichCardsToTrade();       //trade withself
    void tradeResources(Player &);  //trade with another player
    int findBestTrade(char);

    //gaining resources
    void addProperColor(char&, int&);
    //checking to see if things can be planted
    bool roadOffOwnCity(int &, int &);
    int checkRoad();

    //removing card on 7
    char removeRandomCard();
    
    //playing dev card
    void playVictoryPoint();
    void playYearOfPlenty();

    public:
    int roll();

    void checkStats();
    void seeResources();
    void seeDevelopments();
    void buyItem();
    void changeName(string&);
    void changeColor(char&);
    void convertResources(); //try to switch out cards

    void gainResources(int& );
    void removeCardsOn7();

    bool areRoadsBlockingSettlement(int &);
    bool isSettlementBlockingRoad(int &);

    //For Dev Cards
    int playDevCar();
    //For monopoly cards:
    char playMonoply();
    int removeCardFromPlayer(char &);
    void gainCardsFromMonopoly(int&, char&);

    //constructor
    Player();
    ~Player();
};
