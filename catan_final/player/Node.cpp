#include <iostream>
#include "Node.h"
using namespace std;

Node::Node(){

    nodes[0] = 0;//case robber
    nodes[1] = 11;
    nodes[2] = 12;
    nodes[3] = 9;
    nodes[4] = 4;
    nodes[5] = 6;
    nodes[6] = 5;
    nodes[7] = 10;
    nodes[8] = 3;
    nodes[9] = 11;
    nodes[10] = 4;
    nodes[11] = 8;
    nodes[12] = 8;
    nodes[13] = 10;
    nodes[14] = 9;
    nodes[15] = 3;
    nodes[16] = 5;
    nodes[17] = 2;
    nodes[18] = 6;
    nodes[19] = 0; //desert


}


int Node::findNode(int i){
    if(i==0)
        return 0;
    else
        return nodes[i];
}

void Node::placeRobber(int rob){

    int i = 1;

    //find current robber spot
    while(nodes[i]!=0)
        i++;

    //place with old value
    nodes[i] = nodes[0];

    nodes[0] = nodes[rob];
    nodes[rob] = 0;
}
