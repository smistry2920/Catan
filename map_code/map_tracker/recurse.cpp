#include <QtCore>
#include "map_tracker.h"
void get_digits(int x);

int main(int argc, char *argv[]){
        map_tracker map;
        map.valid_settlement_check("settle_01");
        map.valid_settlement_check("settle_101");
        map.valid_settlement_check("settle_02");
        map.valid_settlement_check("settle_402");
        map.valid_settlement_check("settle_60");
        map.valid_settlement_check("settle_01");
    /*
        if (argc == 2){
            QString word = argv[1];
            bool ok = true;
            int value = word.toInt(&ok,10);
            get_digits(value);
	}
        else{
            qDebug() << "You didn't enter the right amount of letters!";
        }
        */
    return 0;
}

//digit 1 is always the next number (unless >6, >16.1, or 26.11; then loop back)
//digit 2 is always the number before it (unless <1, <11, or <21.1; then loop back)
//digit 3 is always the number +10 or -10 from the digit (depending on number)
void get_digits(int x){
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
    qDebug() << "digit_1: " << digit_1;
    qDebug() << "digit_2: " << digit_2;
    qDebug() << "digit_3: " << digit_3;
}
