#ifndef PLAYER_H
#define PLAYER_H

#include <QtCore>
#include<iostream>
#include<string>
#include<list>
#include "Node.h"

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
        int node;
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



    //Trading cards
    void whichCardsToTrade();       //trade withself
    int findBestTrade(char);

    //gaining resource
    void addProperColor(char, int);

    //checking to see if things can be planted
    bool roadOffOwnCity(int, int);
    int checkRoad();

    //removing card on 7

    
    //playing dev card
    void playVictoryPoint();
    void playYearOfPlenty();

    public:
    int roll();

    void checkStats();
    void seeResources();
    void seeDevelopments();
    void changeName(string&);
    void changeColor(char&);
    void convertResources(); //try to switch out cards

    void gainResources(int, Node );

    bool areRoadsBlockingSettlement(int);
    bool isSettlementBlockingRoad(int);

    //For Dev Cards
    int playDevCard();
    //For monopoly cards:
    char playMonoply();
    int removeAllOneCardFromPlayer(char);
    void gainCardsFromMonopoly(int, char);

    //robber's and 7
    bool nodeOnRobber(int);
    void addCard(char);
    char removeRandomCard();
    void removeCardsOn7();


    //buying:
    void buyRoad();
    void buySettlement(QString);
    void buyCity(QString);
    void buyDevelopmentCard();

    //affording:
    bool affordRoad();
    bool affordSettlement();
    bool affordCity();
    bool affordDevelopmentCard();

    //constructor
    Player();
    ~Player();
};
#endif
