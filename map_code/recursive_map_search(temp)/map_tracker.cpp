#include "map_tracker.h"

map_tracker::map_tracker()
{
    QStringList settlements;
}


bool map_tracker::clicked_settlement(QString settlement){
    return false;
}

bool map_tracker::clicked_road(QString road){
    return false;
}

bool map_tracker::valid_settlement_check(QString settlement){
    return false;
}

bool map_tracker::valid_road_check(QString road){
    return false;
}

QString map_tracker::add_settlement(){
    return "null";
}

QString map_tracker::add_road(){
    return "null";
}

QString map_tracker::settlement_neighbors(QString settlement){
    settlement.chop(5);
    bool ok = true;
    int x = settlement.toInt(&ok, 10);
    qDebug() << x;
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
        qDebug() << "ten's place: " << tens_place << " one's place: " <<  ones_place;

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

        qDebug() << "hundred's place: " << hundreds_place;
        qDebug() << "ten's place: " << tens_place << " one's place: " <<  ones_place;

        //if x%10 != 0 then x ends in 0 (10,20,30,...)
        if (x%10 == 0){
            digit_3 = x/10;

            //indention after "mini hump"....best description I can come up with
            if (hundreds_place == tens_place){
                qDebug() << "after mini hump";
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
                qDebug() << "before mini hump";
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
                    qDebug() << "first edge of plateau";
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
                    qDebug() << "second edge of plateau";
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
    QString return_value = digit1 + digit2 + digit3;
    return return_value;
}

