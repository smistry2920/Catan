#include "map_tracker.h"

map_tracker::map_tracker()
{
}

//////////////////////////////////////////////////////////////////////
//START OF SETTLEMENT CREATION                                      //
//CHECKS IF A SETTLEMENT IS VALID, IF SO, IT ADDS A SETTLEMTN THERE.//
//////////////////////////////////////////////////////////////////////

bool map_tracker::valid_settlement_check(QString settle_in, QString player){
    QString settlement = settle_in.section("|",0,0);
    //qDebug() << "settlement: " << settlement;
    bool ok = true;
    bool check1 = false;
    bool check2 = false;
    bool check3 = false;
    bool check4 = false;
    bool inner_road_check = false;
    bool main_check = false;
    QStringList neighbors;
    int settlement_location = settlement.toInt(&ok,10);

    neighbors = settlement_neighbors(settlement_location);

    check1 = settle_check(neighbors[0]);

    check2 = settle_check(neighbors[1]);

    check3 = settle_check(neighbors[2]);

    settlement = QString::number(settlement_location);
    check4 = settle_check(settlement);

    inner_road_check = road_neighbors(settlement, player, 1);

    if (check1 == true && check2 == true && check3 == true && check4 == true && inner_road_check == true){
        add_settlement(settlement, player);
        main_check = true;
    }

    return main_check;
}

void map_tracker::add_settlement(QString settle, QString player){
    p_settle_ownership << player + "s";
    settlements << settle;
    //qDebug() << settlements;
    //qDebug() << p_settle_ownership;
}

bool map_tracker::settle_check(QString neighbor){
    bool status = false;
    int x = settlements.indexOf(neighbor);
    //qDebug() << neighbor << " x: " << x;
    if (x == -1){
        status = true;
    }
    return status;
}

////////////////////////////////////
//END OF SETTLEMENT CREATION.     //
////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////
//START CITY CREATION!                                                                     //
//VALID CITY CHECKER! CHECKS IS A CITY IS A VALID PLACEMENT AND THEN PLACES A CITY THERE!  //
/////////////////////////////////////////////////////////////////////////////////////////////

bool map_tracker::valid_city_check(QString settlement, QString player){
    QString settle = settlement.section("|",0,0);
    bool ok = true;
    int settle_int = settle.toInt(&ok, 10);
    settle = QString::number(settle_int);
    int settle_loc = settlements.indexOf(settle);
    if (settle_loc == -1){
        //qDebug() << "settlement not found";
        return false;
    }
    QString player_check = p_settle_ownership[settle_loc];
    if (player_check.endsWith("c")){
        //qDebug() << "already a city";
        return false;
    }
    if (player_check != (player+"s")){
        //qDebug() << "player ownership is different";
        return false;
    }

    set_city(settle_loc);
    return true;
}

void map_tracker::set_city(int city_convert){
    p_settle_ownership[city_convert] = p_settle_ownership[city_convert] + "c";
    //qDebug() << settlements;
    // qDebug() << p_settle_ownership;
}
////////////////////////////////////
//END OF CITY CREATION!           //
////////////////////////////////////


///////////////////////////////////////////////////////////
//CHECKS IF THE ROAD IS A LEGAL PLACEMENT FOR THE PLAYER!//
///////////////////////////////////////////////////////////
bool map_tracker::valid_road_check(QString road, QString player){
    QStringList same_check = roads.filter(road);
    if (same_check.size() > 0){
        qDebug() << "road already owned";
        return false;
    }
    qDebug() << "not a copy road";
    QString city1_temp = road.section("|",1,1);
    QString city2_temp = road.section("|",2,2);
    bool ok = true;
    int c1 = city1_temp.toInt(&ok,10);
    int c2 = city2_temp.toInt(&ok,10);
    QString city1 = QString::number(c1);
    QString city2 = QString::number(c2);
    int c1_index = settlements.indexOf(city1);
    int c2_index = settlements.indexOf(city2);
    //road neighbors will return false if more than 1
    //road owned by player (including current one)
    qDebug() << "city 2 road check";
    bool city2_roadcheck = road_neighbors(city2_temp, player, 0);
    qDebug() << "city 1 road check";
    bool city1_roadcheck = road_neighbors(city1_temp, player, 0);

    if (c1_index != -1){
        qDebug() << "in city 1";
        QString city1_owner = p_settle_ownership[c1_index];
        if ( city1_owner.at(1) == player.at(1)){
            roads << road + "|" + player;
            return true;
        }
        if (!city1_roadcheck){
            qDebug() << "city 1(not player's) has neighbor roads of player";
            return false;
        }
    }
    if (c2_index != -1){
        qDebug() << "in city 2";
        QString city2_owner = p_settle_ownership[c2_index];
        if ( city2_owner.at(1)== player.at(1)){
            roads << road + "|" + player;
            return true;
        }
        if (!city2_roadcheck){
            qDebug() << "city 2(not player's) has neighbor roads of player";
            return false;
        }
    }

    if (c1_index == -1 &&  c2_index == -1){
        qDebug() << "both cities unoccupied";
        if (!city1_roadcheck || !city2_roadcheck){
            roads << road + "|" + player;
            return true;
        }
    }
    if (c1_index == -1){
        qDebug() << "city 1 unoccupied";
        if (!city1_roadcheck){
            roads << road + "|" + player;
            return true;
        }
    }
    if (c2_index == -1){
        qDebug() << "city2 unoccupied";
        if (!city2_roadcheck){
            roads << road + "|" + player;
            return true;
        }
    }

    return false;
}

bool map_tracker::road_neighbors(QString city, QString player, int function_switch){
    if (city.size() < 3){
        city = "0"+ city;
        if (city.size() == 2){
            city = "0" + city;
        }
    }
    QStringList settlement_roads = roads.filter(city);
    QString road1_owner, road2_owner,road3_owner;
    int count = 0;
    qDebug() << settlement_roads;
    if (settlement_roads.size() > 0){
        QString road1 = settlement_roads[0];
        road1_owner = road1.section("|",3,3);
        qDebug() << road1_owner << " -road1_owner vs " << player;
        if (road1_owner == player && function_switch == 0){
           //road1 owner match
           qDebug() << road1_owner << " matched";
           return false;
        }
        if (function_switch == 1){
            ++count;
        }
    }
    if (settlement_roads.size() > 1){
        QString road2 = settlement_roads[1];
        road2_owner = road2.section("|",3,3);
        qDebug() << road2_owner << " -road2_owner vs" << player;
        if (road2_owner == player && function_switch == 0){
            //road1 owner match
            qDebug() << road2_owner << " matched";
            return false;
        }
        if (function_switch == 1){
            ++count;
        }

    }
    if (function_switch == 1){
        if (settlement_roads.size() > 2){
            QString road3 = settlement_roads[2];
            road3_owner = road3.section("|",3,3);
            qDebug() << road3_owner << " -road3_owner vs" << player;
            if (road3_owner != player){
                    ++count;
                }
            }
        qDebug() << "count: " << count;
        if (count > 1){
            if (road1_owner == road2_owner){
                if (road1_owner != player){
                    return false;
                }
            }
        }
        if (count > 2){
            if (road3_owner == road2_owner || road3_owner == road1_owner){
                if (road3_owner != player){
                    return false;
                }
            }
        }
    }
    return true;
}

QStringList map_tracker::settlement_neighbors(int x){
    //qDebug() << "search neighbors of: " << x;
    int digit_1 = 0;
    int digit_2 = 0;
    int digit_3 = 0;
    //loop1
    //check 1-6 and +10!
    if (x<7){
        digit_1 = x + 1;
        digit_2 = x - 1;
        digit_3 = x * 10;
        //for loop back (1->6 & 6->1)
        if (digit_2 < 1){
            digit_2 = 6;
        }
        if (digit_1 > 6){
            digit_1 = 1;
        }
    }
    //loop2
    //check 10-66 and above/below
    else if (x > 6 && x < 70){
        int tens_place = x / 10;
        int ones_place = x-(tens_place*10);
        //qDebug() << "ten's place: " << tens_place << " one's place: " <<  ones_place;

        //if x%10 != 0 then x ends in 0 (10,20,30,...)
        if (x%10 == 0){
            digit_3 = tens_place;
            digit_1 = x + digit_3;
            digit_2 = (x - 10) + digit_3;
            //to account for 11->16.1
            if (digit_2 == 1){
                digit_2 = 61;
            }
        }
        //else x does not end in 0 (21,22,33,...)
        else{
            digit_3 = x * 10;
            //current # is after a whole number
            if (tens_place == ones_place){
                digit_1 = x + 1;
                digit_2 = x - ones_place;
                if (digit_1 == 67){
                    digit_1 = 61;
                }
            }
            //current # is before a whole number
            else{
                digit_1 = (x - ones_place) + 10;
                digit_2 = x - 1;
                if (digit_1 == 70){
                    digit_1 = 10;
                }
                if (digit_2 == 60){
                    digit_2 = 66;
                }
            }
        }
    }
    else if (x > 100 && x < 701) {
        int hundreds_place = x/100;
        int tens_place = ( x - (hundreds_place*100) ) /10;
        int ones_place = x - (tens_place*10) - (hundreds_place*100);

//        qDebug() << "hundred's place: " << hundreds_place;
//        qDebug() << "ten's place: " << tens_place << " one's place: " <<  ones_place;

        //if x%10 != 0 then x ends in 0 (10,20,30,...)
        if (x%10 == 0){
            digit_3 = x/10;

            //indention after "mini hump"....best description I can come up with
            if (hundreds_place == tens_place){
//                qDebug() << "after mini hump";
                digit_1 = x + 1;
                digit_2 = x-49;
                if (digit_1 == 661){
                    digit_1 = 666;
                }
                if (digit_2 == 61){
                    digit_2 = 700;
                }
            }

            //indention before "mini hump" (sorry...will explain later!)
            else{
//                qDebug() << "before mini hump";
                digit_1 = x+51;
                digit_2 = (x-10) + tens_place;
                if (digit_1 == 661){
                    digit_1 = 700;
                }
                if (digit_2 == 601){
                    digit_2 = 661;
                }
            }
            if (x == 700){
                digit_1 = 110;
                digit_2 = 610;
                digit_3 = 0;
            }
        }
        //else the number is on the "plateau"
        else{
            digit_3 = 0;
            if (tens_place == hundreds_place){
                // # is on first edge of "plateau"
                if ((ones_place == 1 || x == 666 ) && x != 661){
//                    qDebug() << "first edge of plateau";
                    digit_1 = x + tens_place;
                    digit_2 = x - 1;
                    if (digit_1 == 672){
                        digit_1 = 661;
                    }
                    if (digit_2 == 665){
                        digit_2 = 660;
                    }
                }

                // # number is on second edge of "plateau"
                else{
//                    qDebug() << "second edge of plateau";
                    digit_1 = (x - ones_place) + 10;
                    digit_2 = (x - ones_place) + 1;
                    if (digit_1 == 670){
                        digit_1 = 610;
                    }
                    if (digit_2 == 661){
                        digit_2 = 666;
                    }
                }
            }
            //# is the "mini-hump"
            else{
                digit_1 = x + 49;
                digit_2 = x - 51;
            }
        }
    }
    QString digit1 = QString::number(digit_1);
    QString digit2 = QString::number(digit_2);
    QString digit3 = QString::number(digit_3);
    QStringList neighbors;
    neighbors << digit1 << digit2 << digit3;
    return neighbors;
}

