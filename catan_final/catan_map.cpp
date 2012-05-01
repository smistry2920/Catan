#include "catan_map.h"
#include "ui_catan_map.h"

catan_map::catan_map(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::catan_map)
{
    QString image = "map_semi_final.png";
    ui->setupUi(this);
    QPixmap pix = QPixmap(image);
    ui->image_label->setPixmap(pix);

    signalMapper = new QSignalMapper(this); //signal map

    //connect buttons to signal mapper

    activate_settlements();

    activate_roads();

    activate_other();
    iter = 0;

    //activate_nodes();

    //final signal mapping connection (calls signalSorter to sort signals!)
    connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(signalSorter(const QString &)));
    //checkPlayers();
    checkPlayer();
}

catan_map::~catan_map()
{
    delete ui;
}

void catan_map::signalSorter(const QString & button)
{

    qDebug() << "made it here: " << button;

    //road button pushed
    if (button.startsWith("road")){
        qDebug() << "road button: " << button;
    }

    //view a hand!
    else if (button.startsWith("v")){
        //players[iter].seeResources();
        bool ok = true;
        QString player_hand = button.at(7);
        int p_viewHand = player_hand.toInt(&ok,10);
        p_viewHand --;
        //qDebug() << "view hand: " << button << player_hand<<"***"<<p_viewhand;
        players[p_viewHand].seeResources();

    }

    //buy a development card
    else if (button.startsWith("buy") && players[iter].affordDevelopmentCard()){
        qDebug() << "buy development card: " << button;
    }

    //roll
    else if (button.startsWith("roll")){
        int numPlayers = 4;
        int i = players[iter].roll() + players[iter].roll();
        QString out = QString::number(i);
        ui->roll_outcome->setText(out);
        qDebug() << "roll code: " << button;

        if(i==7){//roll 7 conditions
            for(int k = 0; k<numPlayers; k++)
                players[k].removeCardsOn7();


            int nodeNumber=0;
            node.placeRobber(nodeNumber);
            //int nodeNumber;



            //some sort of wait for node click command to then place robber.
            //then we get to take a card form a player on that node.
            bool onNode[4];
            for(int i = 0; i<numPlayers; i++)
                onNode[i] = 0;

            for(int i = 0; i<numPlayer; i++){
                if(i!=iter)
                    cout<<"bulloks"<<endl;

            }

        }
        for(int k = 0; k< numPlayers; k++)
            players[k].gainResources(i,node);

        iter++;

        if(iter>=numPlayers)
            iter = 0;


    }
//UNDER HERE!! all qDebugs are TEST CODE!!
//////replace city_output ->> P1 and P2 with
/////////qstrings that contain player number!!
    else{
        //////////////TEMPORARY
        ///

        qDebug() << "*************************";
        if (mapper.valid_city_check(button, "P1") && players[iter].affordCity()){
            qDebug() << "City: valid city implemented for: " << button;
            qDebug() << "-------------------------";
            city_output(button, "P3");
            players[iter].buyCity(button);
        }
        else{
            qDebug() << "City: settlment failed";
            qDebug() << "----------------------";
        }
        if (mapper.valid_settlement_check(button, "P1") && players[iter].affordSettlement()){
            qDebug() << "valid settlement input for: " << button;
            qDebug() << "-------------------------";
            settlement_output(button,"P4");
            players[iter].buySettlement(button); //add settlement to player list

        }
        else{
            qDebug() << "Settlement: settle failed";
            qDebug() << "-------------------------";
        }
    }
}

void catan_map::checkPlayer(){
/*    if (player.player_amount == 1){
        ui->handButton_4->setDisabled(false);
        ui->player3_label->setText(player.name(1));

    }
*/
}

void catan_map::settlement_output(QString button, QString player){
    QString button_out = button.section("|",0,0);
    button_out = button_out + "s";
    button_output(button_out, player);
}

void catan_map::city_output(QString button, QString player){
    QString button_out = button.section("|",0,0);
    button_out = button_out + "c";
    button_output(button_out, player);
}

void catan_map::button_output(QString button_out, QString player){
    QString button_text;
    QString button_color;
    if(button_out.endsWith("c")){
        button_text = "c";
    }
    else{
        button_text = "s";
    }
    button_out.chop(1);

    if (player == "P1"){
        button_color = "background-color: rgb(69, 139, 116)";
    }
    if (player == "P2"){
        button_color = "background-color: rgb(113, 113, 198)";
    }
    if (player == "P3"){
        button_color = "background-color: rgb(255, 140, 0)";
    }
    if (player == "P4"){
        button_color = "background-color: rgb(205, 150, 205)";
    }
    ///////////////////////////////////////////////////////

    if(button_out == "221"){
        ui->pushSettle_221->setText(button_text);
        ui->pushSettle_221->setAutoFillBackground(true);
        ui->pushSettle_221->setStyleSheet(button_color);
    }
    if (button_out == "223"){
        ui->pushSettle_223->setText(button_text);
        ui->pushSettle_223->setAutoFillBackground(true);
        ui->pushSettle_223->setStyleSheet(button_color);
    }
    if (button_out == "230"){
        ui->pushSettle_230->setText(button_text);
        ui->pushSettle_230->setAutoFillBackground(true);
        ui->pushSettle_230->setStyleSheet(button_color);
    }
    if (button_out == "281"){
        ui->pushSettle_281->setText(button_text);
        ui->pushSettle_281->setAutoFillBackground(true);
        ui->pushSettle_281->setStyleSheet(button_color);
    }
    if (button_out == "330"){
        ui->pushSettle_330->setText(button_text);
        ui->pushSettle_330->setAutoFillBackground(true);
        ui->pushSettle_330->setStyleSheet(button_color);
    }
    if (button_out == "331"){
        ui->pushSettle_331->setText(button_text);
        ui->pushSettle_331->setAutoFillBackground(true);
        ui->pushSettle_331->setStyleSheet(button_color);
    }
    if (button_out == "334"){
        ui->pushSettle_334->setText(button_text);
        ui->pushSettle_334->setAutoFillBackground(true);
        ui->pushSettle_334->setStyleSheet(button_color);
    }
    if (button_out == "171"){
        ui->pushSettle_171->setText(button_text);
        ui->pushSettle_171->setAutoFillBackground(true);
        ui->pushSettle_171->setStyleSheet(button_color);
    }
    if (button_out == "220"){
        ui->pushSettle_220->setText(button_text);
        ui->pushSettle_220->setAutoFillBackground(true);
        ui->pushSettle_220->setStyleSheet(button_color);
    }
    if (button_out == "22"){
        ui->pushSettle_22->setText(button_text);
        ui->pushSettle_22->setAutoFillBackground(true);
        ui->pushSettle_22->setStyleSheet(button_color);
    }
    if (button_out == "23"){
        ui->pushSettle_23->setText(button_text);
        ui->pushSettle_23->setAutoFillBackground(true);
        ui->pushSettle_23->setStyleSheet(button_color);
    }
    if (button_out == "30"){
        ui->pushSettle_30->setText(button_text);
        ui->pushSettle_30->setAutoFillBackground(true);
        ui->pushSettle_30->setStyleSheet(button_color);
    }
    if (button_out == "33"){
        ui->pushSettle_33->setText(button_text);
        ui->pushSettle_33->setAutoFillBackground(true);
        ui->pushSettle_33->setStyleSheet(button_color);
    }
    if (button_out == "34"){
        ui->pushSettle_34->setText(button_text);
        ui->pushSettle_34->setAutoFillBackground(true);
        ui->pushSettle_34->setStyleSheet(button_color);
    }
    if (button_out == "340"){
        ui->pushSettle_340->setText(button_text);
        ui->pushSettle_340->setAutoFillBackground(true);
        ui->pushSettle_340->setStyleSheet(button_color);
    }
    if (button_out == "391"){
        ui->pushSettle_391->setText(button_text);
        ui->pushSettle_391->setAutoFillBackground(true);
        ui->pushSettle_391->setStyleSheet(button_color);
    }
    if (button_out == "112"){
        ui->pushSettle_112->setText(button_text);
        ui->pushSettle_112->setAutoFillBackground(true);
        ui->pushSettle_112->setStyleSheet(button_color);
    }
    if (button_out == "120"){
        ui->pushSettle_120->setText(button_text);
        ui->pushSettle_120->setAutoFillBackground(true);
        ui->pushSettle_120->setStyleSheet(button_color);
    }
    if (button_out == "12"){
        ui->pushSettle_12->setText(button_text);
        ui->pushSettle_12->setAutoFillBackground(true);
        ui->pushSettle_12->setStyleSheet(button_color);
    }
    if (button_out == "20"){
        ui->pushSettle_20->setText(button_text);
        ui->pushSettle_20->setAutoFillBackground(true);
        ui->pushSettle_20->setStyleSheet(button_color);
    }
    if (button_out == "2"){
        ui->pushSettle_2->setText(button_text);
        ui->pushSettle_2->setAutoFillBackground(true);
        ui->pushSettle_2->setStyleSheet(button_color);
    }
    if (button_out == "3"){
        ui->pushSettle_3->setText(button_text);
        ui->pushSettle_3->setAutoFillBackground(true);
        ui->pushSettle_3->setStyleSheet(button_color);
    }
    if (button_out == "4"){
        ui->pushSettle_4->setText(button_text);
        ui->pushSettle_4->setAutoFillBackground(true);
        ui->pushSettle_4->setStyleSheet(button_color);
    }
    if (button_out == "40"){
        ui->pushSettle_40->setText(button_text);
        ui->pushSettle_40->setAutoFillBackground(true);
        ui->pushSettle_40->setStyleSheet(button_color);
    }
    if (button_out == "44"){
        ui->pushSettle_44->setText(button_text);
        ui->pushSettle_44->setAutoFillBackground(true);
        ui->pushSettle_44->setStyleSheet(button_color);
    }
    if (button_out == "440"){
        ui->pushSettle_440->setText(button_text);
        ui->pushSettle_440->setAutoFillBackground(true);
        ui->pushSettle_440->setStyleSheet(button_color);
    }
    if (button_out == "441"){
        ui->pushSettle_441->setText(button_text);
        ui->pushSettle_441->setAutoFillBackground(true);
        ui->pushSettle_441->setStyleSheet(button_color);
    }
    if (button_out == "111"){
        ui->pushSettle_111->setText(button_text);
        ui->pushSettle_111->setAutoFillBackground(true);
        ui->pushSettle_111->setStyleSheet(button_color);
    }
    if (button_out == "110"){
        ui->pushSettle_110->setText(button_text);
        ui->pushSettle_110->setAutoFillBackground(true);
        ui->pushSettle_110->setStyleSheet(button_color);
    }
    if (button_out == "11"){
        ui->pushSettle_11->setText(button_text);
        ui->pushSettle_11->setAutoFillBackground(true);
        ui->pushSettle_11->setStyleSheet(button_color);
    }
    if (button_out == "10"){
        ui->pushSettle_10->setText(button_text);
        ui->pushSettle_10->setAutoFillBackground(true);
        ui->pushSettle_10->setStyleSheet(button_color);
    }
    if (button_out == "1"){
        ui->pushSettle_1->setText(button_text);
        ui->pushSettle_1->setAutoFillBackground(true);
        ui->pushSettle_1->setStyleSheet(button_color);
    }
    if (button_out == "6"){
        ui->pushSettle_6->setText(button_text);
        ui->pushSettle_6->setAutoFillBackground(true);
        ui->pushSettle_6->setStyleSheet(button_color);
    }
    if (button_out == "5"){
        ui->pushSettle_5->setText(button_text);
        ui->pushSettle_5->setAutoFillBackground(true);
        ui->pushSettle_5->setStyleSheet(button_color);
    }
    if (button_out == "50"){
        ui->pushSettle_50->setText(button_text);
        ui->pushSettle_50->setAutoFillBackground(true);
        ui->pushSettle_50->setStyleSheet(button_color);
    }
    if (button_out == "45"){
        ui->pushSettle_45->setText(button_text);
        ui->pushSettle_45->setAutoFillBackground(true);
        ui->pushSettle_45->setStyleSheet(button_color);
    }
    if (button_out == "450"){
        ui->pushSettle_450->setText(button_text);
        ui->pushSettle_450->setAutoFillBackground(true);
        ui->pushSettle_450->setStyleSheet(button_color);
    }
    if (button_out == "445"){
        ui->pushSettle_445->setText(button_text);
        ui->pushSettle_445->setAutoFillBackground(true);
        ui->pushSettle_445->setStyleSheet(button_color);
    }
    if (button_out == "700"){
        ui->pushSettle_700->setText(button_text);
        ui->pushSettle_700->setAutoFillBackground(true);
        ui->pushSettle_700->setStyleSheet(button_color);
    }
    if (button_out == "610"){
        ui->pushSettle_610->setText(button_text);
        ui->pushSettle_610->setAutoFillBackground(true);
        ui->pushSettle_610->setStyleSheet(button_color);
    }
    if (button_out == "61"){
        ui->pushSettle_61->setText(button_text);
        ui->pushSettle_61->setAutoFillBackground(true);
        ui->pushSettle_61->setStyleSheet(button_color);
    }
    if (button_out == "66"){
        ui->pushSettle_66->setText(button_text);
        ui->pushSettle_66->setAutoFillBackground(true);
        ui->pushSettle_66->setStyleSheet(button_color);
    }
    if (button_out == "60"){
        ui->pushSettle_60->setText(button_text);
        ui->pushSettle_60->setAutoFillBackground(true);
        ui->pushSettle_60->setStyleSheet(button_color);
    }
    if (button_out == "56"){
        ui->pushSettle_56->setText(button_text);
        ui->pushSettle_56->setAutoFillBackground(true);
        ui->pushSettle_56->setStyleSheet(button_color);
    }
    if (button_out == "55"){
        ui->pushSettle_55->setText(button_text);
        ui->pushSettle_55->setAutoFillBackground(true);
        ui->pushSettle_55->setStyleSheet(button_color);
    }
    if (button_out == "550"){
        ui->pushSettle_550->setText(button_text);
        ui->pushSettle_550->setAutoFillBackground(true);
        ui->pushSettle_550->setStyleSheet(button_color);
    }
    if (button_out == "501"){
        ui->pushSettle_501->setText(button_text);
        ui->pushSettle_501->setAutoFillBackground(true);
        ui->pushSettle_501->setStyleSheet(button_color);
    }
    if (button_out == "661"){
        ui->pushSettle_661->setText(button_text);
        ui->pushSettle_661->setAutoFillBackground(true);
        ui->pushSettle_661->setStyleSheet(button_color);
    }
    if (button_out == "666"){
        ui->pushSettle_666->setText(button_text);
        ui->pushSettle_666->setAutoFillBackground(true);
        ui->pushSettle_666->setStyleSheet(button_color);
    }
    if (button_out == "660"){
        ui->pushSettle_660->setText(button_text);
        ui->pushSettle_660->setAutoFillBackground(true);
        ui->pushSettle_660->setStyleSheet(button_color);
    }
    if (button_out == "611"){
        ui->pushSettle_611->setText(button_text);
        ui->pushSettle_611->setAutoFillBackground(true);
        ui->pushSettle_611->setStyleSheet(button_color);
    }
    if (button_out == "560"){
        ui->pushSettle_560->setText(button_text);
        ui->pushSettle_560->setAutoFillBackground(true);
        ui->pushSettle_560->setStyleSheet(button_color);
    }
    if (button_out == "556"){
        ui->pushSettle_556->setText(button_text);
        ui->pushSettle_556->setAutoFillBackground(true);
        ui->pushSettle_556->setStyleSheet(button_color);
    }
    if (button_out == "551"){
        ui->pushSettle_551->setText(button_text);
        ui->pushSettle_551->setAutoFillBackground(true);
        ui->pushSettle_551->setStyleSheet(button_color);
    }
}

void catan_map::activate_settlements(){

    /////////////////////////////////////////////
    //START SETTLEMENT BUTTON MAPPING!!
    ///////////////////
    //Format is city ID|left Color|left node|right Color|right node|top color|top node|port
    connect(ui->pushSettle_221, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_221, "221|0|0|d|1|0|0|3");

    connect(ui->pushSettle_223, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_223, "223|0|0|0|0|d|1|3");

    connect(ui->pushSettle_230, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_230, "230|d|1|l|2|0|0|0");

    connect(ui->pushSettle_281, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_281, "281|0|0|0|0|l|2|l");

    connect(ui->pushSettle_330, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_330, "330|l|2|y|3|0|0|l");

    connect(ui->pushSettle_331, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_331, "331|0|0|0|0|y|3|0");

    connect(ui->pushSettle_334, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_334, "334|y|3|0|0|0|0|0");

    connect(ui->pushSettle_171, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_171, "171|0|0|r|4|0|0|b");

    connect(ui->pushSettle_220, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_220, "220|0|0|d|1|r|4|0");

    connect(ui->pushSettle_22, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_22, "22|r|4|b|5|d|1|0");

    connect(ui->pushSettle_23, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_23, "23|d|1|l|2|b|5|0");

    connect(ui->pushSettle_30, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_30, "30|b|5|r|6|l|2|0");

    connect(ui->pushSettle_33, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_33, "33|l|2|y|3|r|6|0");

    connect(ui->pushSettle_34, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_34, "34|r|6|l|7|y|3|0");

    connect(ui->pushSettle_340, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_340, "340|y|3|0|0|l|7|3");

    connect(ui->pushSettle_391, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_391, "391|l|7|0|0|0|0|3");

    connect(ui->pushSettle_112, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_112, "112|0|0|0|0|0|0|0");

    connect(ui->pushSettle_120, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_120, "120|0|0|r|4|0|0|b");

    connect(ui->pushSettle_12, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_12, "12|0|0|d|8|r|4|0");

    connect(ui->pushSettle_20, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_20, "20|r|4|d|5|d|8|0");

    connect(ui->pushSettle_2, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_2, "2|d|8|y|9|b|5|0");

    connect(ui->pushSettle_3, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_3, "3|b|5|r|6|y|9|0");

    connect(ui->pushSettle_4, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_4, "4|y|9|d|10|r|6|0");

    connect(ui->pushSettle_40, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_40, "40|r|6|l|7|d|10|0");

    connect(ui->pushSettle_44, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_44, "44|d|10|y|11|l|7|0");

    connect(ui->pushSettle_440, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_440, "440|l|7|0|0|y|11|0");

    connect(ui->pushSettle_441, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_441, "441|y|11|0|0|0|0|3");

    connect(ui->pushSettle_111, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_111, "111|0|0|0|0|0|0|0");

    connect(ui->pushSettle_110, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_110, "110|0|0|r|12|0|0|y");

    connect(ui->pushSettle_11, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_11, "11|0|0|d|8|r|12|0");

    connect(ui->pushSettle_10, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_10, "10|r|12|l|13|d|8|0");

    connect(ui->pushSettle_1, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_1, "1|d|8|y|9|l|13|0");

    connect(ui->pushSettle_6, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_6, "6|l|13|l|14|y|9|0");

    connect(ui->pushSettle_5, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_5, "5|l|9|d|10|l|14|0");

    connect(ui->pushSettle_50, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_50, "50|l|14|b|15|d|10|0");

    connect(ui->pushSettle_45, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_45, "45|d|10|y|11|b|15|0");

    connect(ui->pushSettle_450, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_450, "450|b|15|0|0|y|11|0");

    connect(ui->pushSettle_445, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_445, "445|y|11|0|0|0|0|3");

    connect(ui->pushSettle_700, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_700, "700|0|0|r|12|0|0|y");

    connect(ui->pushSettle_610, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_610, "610|0|0|b|16|r|12|0");

    connect(ui->pushSettle_61, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_61, "61|r|12|l|13|b|16|0");

    connect(ui->pushSettle_66, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_66, "66|b|16|y|17|l|13|0");

    connect(ui->pushSettle_60, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_60, "60|l|13|l|14|y|17|0");

    connect(ui->pushSettle_56, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_56, "56|l|17|d|18|l|14|0");

    connect(ui->pushSettle_55, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_55, "55|l|14|b|15|d|18|0");

    connect(ui->pushSettle_550, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_550, "550|d|18|0|0|b|15|r");

    connect(ui->pushSettle_501, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_501, "501|b|3|0|0|0|0|r");

    connect(ui->pushSettle_661, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_661, "661|0|0|b|16|0|0|3");

    connect(ui->pushSettle_666, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_666, "666|0|0|0|0|b|16|3");

    connect(ui->pushSettle_660, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_660, "660|b|16|y|17|0|0|0");

    connect(ui->pushSettle_611, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_611, "611|0|0|0|0|l|17|d");

    connect(ui->pushSettle_560, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_560, "560|y|17|d|18|0|0|d");

    connect(ui->pushSettle_556, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_556, "556|0|0|0|0|d|18|0");

    connect(ui->pushSettle_551, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_551, "551|d|18|0|0|0|0|0");

    //////////////////
    //END SETTLEMENT BUTTON MAPPING
    ////////////////////////////////////////////
}

void catan_map::activate_roads(){

    ////////////////////////////////////////////
    //START ROAD MAPPING
    ////////////////
   //road|top|bottom
    connect(ui->pushRoad_01, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_01, "road|223|221");

    connect(ui->pushRoad_02, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_02, "road|223|230");

    connect(ui->pushRoad_03, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_03, "road|230|281");

    connect(ui->pushRoad_04, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_04, "road|281|330");

    connect(ui->pushRoad_05, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_05, "road|331|330");

    connect(ui->pushRoad_06, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_06, "road|334|331");

    connect(ui->pushRoad_07, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_07, "road|221|220");

    connect(ui->pushRoad_08, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_08, "road|230|23");

    connect(ui->pushRoad_09, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_09, "road|330|30");

    connect(ui->pushRoad_10, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_10, "road|334|340");

    connect(ui->pushRoad_11, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_11, "road|220|171");

    connect(ui->pushRoad_12, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_12, "road|220|22");

    connect(ui->pushRoad_13, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_13, "road|23|22");

    connect(ui->pushRoad_14, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_14, "road|23|30");

    connect(ui->pushRoad_15, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_15, "road|33|30");

    connect(ui->pushRoad_16, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_16, "road|33|34");

    connect(ui->pushRoad_17, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_17, "road|340|34");

    connect(ui->pushRoad_18, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_18, "road|340|391");
\
    connect(ui->pushRoad_19, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_19, "road|171|10");

    connect(ui->pushRoad_20, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_20, "road|22|20");

    connect(ui->pushRoad_21, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_21, "road|30|3");

    connect(ui->pushRoad_22, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_22, "road|34|40");

    connect(ui->pushRoad_23, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_23, "road|391|440");

    connect(ui->pushRoad_24, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_24, "road|10|112");

    connect(ui->pushRoad_25, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_25, "road|10|12");

    connect(ui->pushRoad_26, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_26, "road|20|12");

    connect(ui->pushRoad_27, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_27, "road|20|2");

    connect(ui->pushRoad_28, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_28, "road|3|2");

    connect(ui->pushRoad_29, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_29, "road|3|4");

    connect(ui->pushRoad_30, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_30, "road|4|40");

    connect(ui->pushRoad_31, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_31, "road|40|44");

    connect(ui->pushRoad_32, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_32, "road|440|44");

    connect(ui->pushRoad_33, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_33, "road|440|441");

    connect(ui->pushRoad_34, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_34, "road|112|111");

    connect(ui->pushRoad_35, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_35, "road|12|11");

    connect(ui->pushRoad_36, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_36, "road|1|2");

    connect(ui->pushRoad_37, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_37, "road|4|5");

    connect(ui->pushRoad_38, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_38, "road|44|45");

    connect(ui->pushRoad_39, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_39, "road|441|445");

    connect(ui->pushRoad_40, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_40, "road|110|111");

    connect(ui->pushRoad_41, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_41, "road|11|110");

    connect(ui->pushRoad_42, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_42, "road|11|10");

    connect(ui->pushRoad_43, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_43, "road|1|10");

    connect(ui->pushRoad_44, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_44, "road|1|6");

    connect(ui->pushRoad_45, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_45, "road|5|6");

    connect(ui->pushRoad_46, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_46, "road|5|50");

    connect(ui->pushRoad_47, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_47, "road|45|50");

    connect(ui->pushRoad_48, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_48, "road|45|450");

    connect(ui->pushRoad_49, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_49, "road|450|445");

    connect(ui->pushRoad_50, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_50, "road|110|700");

    connect(ui->pushRoad_51, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_51, "road|10|61");

    connect(ui->pushRoad_52, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_52, "road|6|60");

    connect(ui->pushRoad_53, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_53, "road|50|55");

    connect(ui->pushRoad_54, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_54, "road|450|501");

    connect(ui->pushRoad_55, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_55, "road|700|610");

    connect(ui->pushRoad_56, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_56, "road|61|610");

    connect(ui->pushRoad_57, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_57, "road|61|66");

    connect(ui->pushRoad_58, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_58, "road|60|66");

    connect(ui->pushRoad_59, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_59, "road|60|56");

    connect(ui->pushRoad_60, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_60, "road|55|56");

    connect(ui->pushRoad_61, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_61, "road|55|550");

    connect(ui->pushRoad_62, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_62, "road|550|501");

    connect(ui->pushRoad_63, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_63, "road|610|661");

    connect(ui->pushRoad_64, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_64, "road|66|660");

    connect(ui->pushRoad_65, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_65, "road|56|560");

    connect(ui->pushRoad_66, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_66, "road|550|551");

    connect(ui->pushRoad_67, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_67, "road|661|666");

    connect(ui->pushRoad_68, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_68, "road|666|660");

    connect(ui->pushRoad_69, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_69, "road|660|611");

    connect(ui->pushRoad_70, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_70, "road|611|560");

    connect(ui->pushRoad_71, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_71, "road|560|556");

    connect(ui->pushRoad_72, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_72, "road|551|556");

    ///////////////
    //END ROAD MAPPING
    ///////////////////////////////////////////

}

void catan_map::activate_other(){

    ////////////////////////////////////////////
    //START MISCELLANEOS MAPPING
    ////////////////

    connect(ui->vhandButton_01, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->vhandButton_01, "vhand_01");

    connect(ui->vhandButton_02, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->vhandButton_02, "vhand_02");

    connect(ui->vhandButton_03, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->vhandButton_03, "vhand_03");

    connect(ui->vhandButton_04, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->vhandButton_04, "vhand_04");

    connect(ui->buyDevButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->buyDevButton, "buyDevCard");

    connect(ui->rollButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->rollButton, "roll");

    ///////////////
    //END MISCELLANEOS MAPPING
    ////////////////////////////////////////////

}

void catan_map::activate_nodes(){

    connect(ui->node_01, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->node_01, "node|1");

    connect(ui->node_02, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->node_02, "node|2");

    connect(ui->node_03, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->node_03, "node|3");

    connect(ui->node_04, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->node_04, "node|4");

    connect(ui->node_05, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->node_05, "node|5");

    connect(ui->node_06, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->node_06, "node|6");

    connect(ui->node_07, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->node_07, "node|7");

    connect(ui->node_08, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->node_08, "node|8")
            ;
    connect(ui->node_09, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->node_09, "node|9");

    connect(ui->node_10, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->node_10, "node|10");

    connect(ui->node_11, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->node_11, "node|11");

    connect(ui->node_12, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->node_12, "node|12");

    connect(ui->node_13, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->node_13, "node|13");

    connect(ui->node_14, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->node_14, "node|14");

    connect(ui->node_15, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->node_15, "node|15");

    connect(ui->node_16, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->node_16, "node|16");

    connect(ui->node_17, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->node_17, "node|17");

    connect(ui->node_18, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->node_18, "node|18");

    connect(ui->node_19, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->node_19, "node|19");
}
