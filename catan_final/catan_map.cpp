#include "catan_map.h"
#include "ui_catan_map.h"

catan_map::catan_map(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::catan_map)
{
    //image were using for the board
    QString image = "map_semi_final.png";
    ui->setupUi(this);
    QPixmap pix = QPixmap(image);
    ui->image_label->setPixmap(pix);

    //way to take in button pushes
    signalMapper = new QSignalMapper(this); //signal map

    //connect buttons to signal mapper

    activate_settlements();
    activate_roads();
    activate_other();
    activate_nodes();

    iter = 0;
    reverse = false;

    //activate_nodes();
    //final signal mapping connection (calls signalSorter to sort signals!)
    connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(signalSorter(const QString &)));
    numPlayers = 4;
    robber = false;
    initial_settle = true;
    init_settle_road = true;
    ui->instruction->setText("P1, place a settlement and a road");
    afterSecondSettlementPlacement = 0;
    prev_robber = "19";
}

catan_map::~catan_map() //deconstructor
{
    delete ui;
}

void catan_map::initial_settle_place(){ //Beginning of the game.

    ui->instruction->setText("player 1, choose a settlement");
}

void catan_map::signalSorter(const QString & button)    //Know how to handle specific button pushes
{
    update_players();
    if (!initial_settle){
        qDebug() << "==============";
        qDebug() << "made it here: " << button;

        if (button.startsWith("node") && robber){
            nodeSelectedOnRobber(button);
        }

        //if robber is active, you must first place the robber!
        if (!robber){
            //road button pushed
            if (button.startsWith("road") && players[iter].affordRoad()){
                road_pushed(button);
            }
            //view a hand!
            else if (button.startsWith("v")){
                viewHand(button);
            }

            //buy a development card
            else if (button.startsWith("buy") && players[iter].affordDevelopmentCard()){
                buyDevCard(button);
            }

            //roll
            else if (button.startsWith("roll")){
                rollSelected(button);
                update_players();
            }
            //city/settlement creaton
            else if (button.endsWith("s")){
                city_settlement_create(button);
            }
            else{
                ui->instruction->setText("Error: either you don't have enough resources or invalid button press");
            }
        }
    }
    //initial game code (allow for 2 cities and 2 roads per player)
    else{
        qDebug() << "initial game start!";
        initial_game_start(button);
    }
    update_players();
}


void catan_map::settlement_output(QString button){
    QString button_out = button.section("|",0,0);
    button_out = button_out + "s";
    button_output(button_out);
}

void catan_map::city_output(QString button){
    QString button_out = button.section("|",0,0);
    button_out = button_out + "c";
    button_output(button_out);
}

void catan_map::road_output(QString road){      //Location and Display of Purchased Roads
    QString road_out = road.section("|",0,0);
    road_out.remove(0,4);
    qDebug() << road_out;
    QString button_color;

    //display color of the buyer
    if (player_name == "P1"){
        button_color = "background-color: rgb(69, 139, 116)";
    }
    if (player_name == "P2"){
        button_color = "background-color: rgb(113, 113, 198)";
    }
    if (player_name == "P3"){
        button_color = "background-color: rgb(255, 140, 0)";
    }
    if (player_name == "P4"){
        button_color = "background-color: rgb(205, 150, 205)";
    }
    ///////////////////////////////////////////////////////
    if (road_out == "01"){
        ui->pushRoad_01->setAutoFillBackground(true);
        ui->pushRoad_01->setStyleSheet(button_color);
    }
    if (road_out == "02"){
        ui->pushRoad_02->setAutoFillBackground(true);
        ui->pushRoad_02->setStyleSheet(button_color);
    }
    if (road_out == "03"){
        ui->pushRoad_03->setAutoFillBackground(true);
        ui->pushRoad_03->setStyleSheet(button_color);
    }
    if (road_out == "04"){
        ui->pushRoad_04->setAutoFillBackground(true);
        ui->pushRoad_04->setStyleSheet(button_color);
    }
    if (road_out == "05"){
        ui->pushRoad_05->setAutoFillBackground(true);
        ui->pushRoad_05->setStyleSheet(button_color);
    }
    if (road_out == "06"){
        ui->pushRoad_06->setAutoFillBackground(true);
        ui->pushRoad_06->setStyleSheet(button_color);
    }
    if (road_out == "07"){
        ui->pushRoad_07->setAutoFillBackground(true);
        ui->pushRoad_07->setStyleSheet(button_color);
    }
    if (road_out == "08"){
        ui->pushRoad_08->setAutoFillBackground(true);
        ui->pushRoad_08->setStyleSheet(button_color);
    }
    if (road_out == "09"){
        ui->pushRoad_09->setAutoFillBackground(true);
        ui->pushRoad_09->setStyleSheet(button_color);
    }
    if (road_out == "10"){
        ui->pushRoad_10->setAutoFillBackground(true);
        ui->pushRoad_10->setStyleSheet(button_color);
    }
    if (road_out == "11"){
        ui->pushRoad_11->setAutoFillBackground(true);
        ui->pushRoad_11->setStyleSheet(button_color);
    }
    if (road_out == "12"){
        ui->pushRoad_12->setAutoFillBackground(true);
        ui->pushRoad_12->setStyleSheet(button_color);
    }
    if (road_out == "13"){
        ui->pushRoad_13->setAutoFillBackground(true);
        ui->pushRoad_13->setStyleSheet(button_color);
    }
    if (road_out == "14"){
        ui->pushRoad_14->setAutoFillBackground(true);
        ui->pushRoad_14->setStyleSheet(button_color);
    }
    if (road_out == "15"){
        ui->pushRoad_15->setAutoFillBackground(true);
        ui->pushRoad_15->setStyleSheet(button_color);
    }
    if (road_out == "16"){
        ui->pushRoad_16->setAutoFillBackground(true);
        ui->pushRoad_16->setStyleSheet(button_color);
    }
    if (road_out == "17"){
        ui->pushRoad_17->setAutoFillBackground(true);
        ui->pushRoad_17->setStyleSheet(button_color);
    }
    if (road_out == "18"){
        ui->pushRoad_18->setAutoFillBackground(true);
        ui->pushRoad_18->setStyleSheet(button_color);
    }
    if (road_out == "19"){
        ui->pushRoad_19->setAutoFillBackground(true);
        ui->pushRoad_19->setStyleSheet(button_color);
    }
    if (road_out == "20"){
        ui->pushRoad_20->setAutoFillBackground(true);
        ui->pushRoad_20->setStyleSheet(button_color);
    }
    if (road_out == "21"){
        ui->pushRoad_21->setAutoFillBackground(true);
        ui->pushRoad_21->setStyleSheet(button_color);
    }
    if (road_out == "22"){
        ui->pushRoad_22->setAutoFillBackground(true);
        ui->pushRoad_22->setStyleSheet(button_color);
    }
    if (road_out == "23"){
        ui->pushRoad_23->setAutoFillBackground(true);
        ui->pushRoad_23->setStyleSheet(button_color);
    }
    if (road_out == "24"){
        ui->pushRoad_24->setAutoFillBackground(true);
        ui->pushRoad_24->setStyleSheet(button_color);
    }
    if (road_out == "25"){
        ui->pushRoad_25->setAutoFillBackground(true);
        ui->pushRoad_25->setStyleSheet(button_color);
    }
    if (road_out == "26"){
        ui->pushRoad_26->setAutoFillBackground(true);
        ui->pushRoad_26->setStyleSheet(button_color);
    }
    if (road_out == "27"){
        ui->pushRoad_27->setAutoFillBackground(true);
        ui->pushRoad_27->setStyleSheet(button_color);
    }
    if (road_out == "28"){
        ui->pushRoad_28->setAutoFillBackground(true);
        ui->pushRoad_28->setStyleSheet(button_color);
    }
    if (road_out == "29"){
        ui->pushRoad_29->setAutoFillBackground(true);
        ui->pushRoad_29->setStyleSheet(button_color);
    }
    if (road_out == "30"){
        ui->pushRoad_30->setAutoFillBackground(true);
        ui->pushRoad_30->setStyleSheet(button_color);
    }
    if (road_out == "31"){
        ui->pushRoad_31->setAutoFillBackground(true);
        ui->pushRoad_31->setStyleSheet(button_color);
    }
    if (road_out == "32"){
        ui->pushRoad_32->setAutoFillBackground(true);
        ui->pushRoad_32->setStyleSheet(button_color);
    }
    if (road_out == "33"){
        ui->pushRoad_33->setAutoFillBackground(true);
        ui->pushRoad_33->setStyleSheet(button_color);
    }
    if (road_out == "34"){
        ui->pushRoad_34->setAutoFillBackground(true);
        ui->pushRoad_34->setStyleSheet(button_color);
    }
    if (road_out == "35"){
        ui->pushRoad_35->setAutoFillBackground(true);
        ui->pushRoad_35->setStyleSheet(button_color);
    }
    if (road_out == "36"){
        ui->pushRoad_36->setAutoFillBackground(true);
        ui->pushRoad_36->setStyleSheet(button_color);
    }
    if (road_out == "37"){
        ui->pushRoad_37->setAutoFillBackground(true);
        ui->pushRoad_37->setStyleSheet(button_color);
    }
    if (road_out == "38"){
        ui->pushRoad_38->setAutoFillBackground(true);
        ui->pushRoad_38->setStyleSheet(button_color);
    }
    if (road_out == "39"){
        ui->pushRoad_39->setAutoFillBackground(true);
        ui->pushRoad_39->setStyleSheet(button_color);
    }
    if (road_out == "40"){
        ui->pushRoad_40->setAutoFillBackground(true);
        ui->pushRoad_40->setStyleSheet(button_color);
    }
    if (road_out == "41"){
        ui->pushRoad_41->setAutoFillBackground(true);
        ui->pushRoad_41->setStyleSheet(button_color);
    }
    if (road_out == "42"){
        ui->pushRoad_42->setAutoFillBackground(true);
        ui->pushRoad_42->setStyleSheet(button_color);
    }
    if (road_out == "43"){
        ui->pushRoad_43->setAutoFillBackground(true);
        ui->pushRoad_43->setStyleSheet(button_color);
    }
    if (road_out == "44"){
        ui->pushRoad_44->setAutoFillBackground(true);
        ui->pushRoad_44->setStyleSheet(button_color);
    }
    if (road_out == "45"){
        ui->pushRoad_45->setAutoFillBackground(true);
        ui->pushRoad_45->setStyleSheet(button_color);
    }
    if (road_out == "46"){
        ui->pushRoad_46->setAutoFillBackground(true);
        ui->pushRoad_46->setStyleSheet(button_color);
    }
    if (road_out == "47"){
        ui->pushRoad_47->setAutoFillBackground(true);
        ui->pushRoad_47->setStyleSheet(button_color);
    }
    if (road_out == "48"){
        ui->pushRoad_48->setAutoFillBackground(true);
        ui->pushRoad_48->setStyleSheet(button_color);
    }
    if (road_out == "49"){
        ui->pushRoad_49->setAutoFillBackground(true);
        ui->pushRoad_49->setStyleSheet(button_color);
    }
    if (road_out == "50"){
        ui->pushRoad_50->setAutoFillBackground(true);
        ui->pushRoad_50->setStyleSheet(button_color);
    }
    if (road_out == "51"){
        ui->pushRoad_51->setAutoFillBackground(true);
        ui->pushRoad_51->setStyleSheet(button_color);
    }
    if (road_out == "52"){
        ui->pushRoad_52->setAutoFillBackground(true);
        ui->pushRoad_52->setStyleSheet(button_color);
    }
    if (road_out == "53"){
        ui->pushRoad_53->setAutoFillBackground(true);
        ui->pushRoad_53->setStyleSheet(button_color);
    }
    if (road_out == "54"){
        ui->pushRoad_54->setAutoFillBackground(true);
        ui->pushRoad_54->setStyleSheet(button_color);
    }
    if (road_out == "55"){
        ui->pushRoad_55->setAutoFillBackground(true);
        ui->pushRoad_55->setStyleSheet(button_color);
    }
    if (road_out == "56"){
        ui->pushRoad_56->setAutoFillBackground(true);
        ui->pushRoad_56->setStyleSheet(button_color);
    }
    if (road_out == "57"){
        ui->pushRoad_57->setAutoFillBackground(true);
        ui->pushRoad_57->setStyleSheet(button_color);
    }
    if (road_out == "58"){
        ui->pushRoad_58->setAutoFillBackground(true);
        ui->pushRoad_58->setStyleSheet(button_color);
    }
    if (road_out == "59"){
        ui->pushRoad_59->setAutoFillBackground(true);
        ui->pushRoad_59->setStyleSheet(button_color);
    }
    if (road_out == "60"){
        ui->pushRoad_60->setAutoFillBackground(true);
        ui->pushRoad_60->setStyleSheet(button_color);
    }
    if (road_out == "61"){
        ui->pushRoad_61->setAutoFillBackground(true);
        ui->pushRoad_61->setStyleSheet(button_color);
    }
    if (road_out == "61"){
        ui->pushRoad_61->setAutoFillBackground(true);
        ui->pushRoad_61->setStyleSheet(button_color);
    }
    if (road_out == "62"){
        ui->pushRoad_62->setAutoFillBackground(true);
        ui->pushRoad_62->setStyleSheet(button_color);
    }
    if (road_out == "63"){
        ui->pushRoad_63->setAutoFillBackground(true);
        ui->pushRoad_63->setStyleSheet(button_color);
    }
    if (road_out == "64"){
        ui->pushRoad_64->setAutoFillBackground(true);
        ui->pushRoad_64->setStyleSheet(button_color);
    }
    if (road_out == "65"){
        ui->pushRoad_65->setAutoFillBackground(true);
        ui->pushRoad_65->setStyleSheet(button_color);
    }
    if (road_out == "66"){
        ui->pushRoad_66->setAutoFillBackground(true);
        ui->pushRoad_66->setStyleSheet(button_color);
    }
    if (road_out == "67"){
        ui->pushRoad_67->setAutoFillBackground(true);
        ui->pushRoad_67->setStyleSheet(button_color);
    }
    if (road_out == "68"){
        ui->pushRoad_68->setAutoFillBackground(true);
        ui->pushRoad_68->setStyleSheet(button_color);
    }
    if (road_out == "69"){
        ui->pushRoad_69->setAutoFillBackground(true);
        ui->pushRoad_69->setStyleSheet(button_color);
    }
    if (road_out == "70"){
        ui->pushRoad_70->setAutoFillBackground(true);
        ui->pushRoad_70->setStyleSheet(button_color);
    }
    if (road_out == "71"){
        ui->pushRoad_71->setAutoFillBackground(true);
        ui->pushRoad_71->setStyleSheet(button_color);
    }
    if (road_out == "72"){
        ui->pushRoad_72->setAutoFillBackground(true);
        ui->pushRoad_72->setStyleSheet(button_color);
    }
}

void catan_map::button_output(QString button_out){  //Display of settlements on the map after purchased.
    QString button_text;
    QString button_color;
    if(button_out.endsWith("c")){
        button_text = "c";
    }
    else{
        button_text = "s";
    }
    button_out.chop(1);

    //display color of the buyer
    if (player_name == "P1"){
        button_color = "background-color: rgb(69, 139, 116)";
    }
    if (player_name == "P2"){
        button_color = "background-color: rgb(113, 113, 198)";
    }
    if (player_name == "P3"){
        button_color = "background-color: rgb(255, 140, 0)";
    }
    if (player_name == "P4"){
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

    //////////////////////////////////////
    //START SETTLEMENT BUTTON MAPPING!! //
    //////////////////////////////////////////////////////////////////////////////////////////
    //Format is city ID|left Color|left node|right Color|right node|top color|top node|port //
    //////////////////////////////////////////////////////////////////////////////////////////

    connect(ui->pushSettle_221, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_221, "221|0|0|d|1|0|0|3|s");

    connect(ui->pushSettle_223, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_223, "223|0|0|0|0|d|1|3|s");

    connect(ui->pushSettle_230, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_230, "230|d|1|l|2|0|0|0|s");

    connect(ui->pushSettle_281, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_281, "281|0|0|0|0|l|2|l|s");

    connect(ui->pushSettle_330, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_330, "330|l|2|y|3|0|0|l|s");

    connect(ui->pushSettle_331, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_331, "331|0|0|0|0|y|3|0|s");

    connect(ui->pushSettle_334, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_334, "334|y|3|0|0|0|0|0|s");

    connect(ui->pushSettle_171, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_171, "171|0|0|r|4|0|0|b|s");

    connect(ui->pushSettle_220, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_220, "220|0|0|d|1|r|4|0|s");

    connect(ui->pushSettle_22, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_22, "22|r|4|b|5|d|1|0|s");

    connect(ui->pushSettle_23, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_23, "23|d|1|l|2|b|5|0|s");

    connect(ui->pushSettle_30, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_30, "30|b|5|r|6|l|2|0|s");

    connect(ui->pushSettle_33, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_33, "33|l|2|y|3|r|6|0|s");

    connect(ui->pushSettle_34, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_34, "34|r|6|l|7|y|3|0|s");

    connect(ui->pushSettle_340, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_340, "340|y|3|0|0|l|7|3|s");

    connect(ui->pushSettle_391, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_391, "391|l|7|0|0|0|0|3|s");

    connect(ui->pushSettle_112, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_112, "112|0|0|0|0|0|0|0|s");

    connect(ui->pushSettle_120, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_120, "120|0|0|r|4|0|0|b|s");

    connect(ui->pushSettle_12, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_12, "12|0|0|d|8|r|4|0|s");

    connect(ui->pushSettle_20, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_20, "20|r|4|d|5|d|8|0|s");

    connect(ui->pushSettle_2, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_2, "2|d|8|y|9|b|5|0|s");

    connect(ui->pushSettle_3, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_3, "3|b|5|r|6|y|9|0|s");

    connect(ui->pushSettle_4, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_4, "4|y|9|d|10|r|6|0|s");

    connect(ui->pushSettle_40, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_40, "40|r|6|l|7|d|10|0|s");

    connect(ui->pushSettle_44, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_44, "44|d|10|y|11|l|7|0|s");

    connect(ui->pushSettle_440, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_440, "440|l|7|0|0|y|11|0|s");

    connect(ui->pushSettle_441, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_441, "441|y|11|0|0|0|0|3|s");

    connect(ui->pushSettle_111, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_111, "111|0|0|0|0|0|0|0|s");

    connect(ui->pushSettle_110, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_110, "110|0|0|r|12|0|0|y|s");

    connect(ui->pushSettle_11, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_11, "11|0|0|d|8|r|12|0|s");

    connect(ui->pushSettle_10, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_10, "10|r|12|l|13|d|8|0|s");

    connect(ui->pushSettle_1, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_1, "1|d|8|y|9|l|13|0|s");

    connect(ui->pushSettle_6, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_6, "6|l|13|l|14|y|9|0|s");

    connect(ui->pushSettle_5, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_5, "5|l|9|d|10|l|14|0|s");

    connect(ui->pushSettle_50, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_50, "50|l|14|b|15|d|10|0|s");

    connect(ui->pushSettle_45, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_45, "45|d|10|y|11|b|15|0|s");

    connect(ui->pushSettle_450, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_450, "450|b|15|0|0|y|11|0|s");

    connect(ui->pushSettle_445, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_445, "445|y|11|0|0|0|0|3|s");

    connect(ui->pushSettle_700, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_700, "700|0|0|r|12|0|0|y|s");

    connect(ui->pushSettle_610, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_610, "610|0|0|b|16|r|12|0|s");

    connect(ui->pushSettle_61, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_61, "61|r|12|l|13|b|16|0|s");

    connect(ui->pushSettle_66, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_66, "66|b|16|y|17|l|13|0|s");

    connect(ui->pushSettle_60, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_60, "60|l|13|l|14|y|17|0|s");

    connect(ui->pushSettle_56, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_56, "56|l|17|d|18|l|14|0|s");

    connect(ui->pushSettle_55, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_55, "55|l|14|b|15|d|18|0|s");

    connect(ui->pushSettle_550, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_550, "550|d|18|0|0|b|15|r|s");

    connect(ui->pushSettle_501, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_501, "501|b|3|0|0|0|0|r|s");

    connect(ui->pushSettle_661, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_661, "661|0|0|b|16|0|0|3|s");

    connect(ui->pushSettle_666, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_666, "666|0|0|0|0|b|16|3|s");

    connect(ui->pushSettle_660, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_660, "660|b|16|y|17|0|0|0|s");

    connect(ui->pushSettle_611, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_611, "611|0|0|0|0|l|17|d|s");

    connect(ui->pushSettle_560, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_560, "560|y|17|d|18|0|0|d|s");

    connect(ui->pushSettle_556, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_556, "556|0|0|0|0|d|18|0|s");

    connect(ui->pushSettle_551, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushSettle_551, "551|d|18|0|0|0|0|0|s");

    //////////////////////////////////
    //END SETTLEMENT BUTTON MAPPING //
    //////////////////////////////////
}

void catan_map::activate_roads(){

    ///////////////////////
    //START ROAD MAPPING //
    ///////////////////////
    //road|top|bottom|//
    ////////////////////

    connect(ui->pushRoad_01, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_01, "road01|223|221");

    connect(ui->pushRoad_02, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_02, "road02|223|230");

    connect(ui->pushRoad_03, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_03, "road03|230|281");

    connect(ui->pushRoad_04, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_04, "road04|281|330");

    connect(ui->pushRoad_05, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_05, "road05|331|330");

    connect(ui->pushRoad_06, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_06, "road06|334|331");

    connect(ui->pushRoad_07, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_07, "road07|221|220");

    connect(ui->pushRoad_08, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_08, "road08|230|023");

    connect(ui->pushRoad_09, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_09, "road09|330|033");

    connect(ui->pushRoad_10, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_10, "road10|334|340");

    connect(ui->pushRoad_11, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_11, "road11|220|171");

    connect(ui->pushRoad_12, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_12, "road12|220|022");

    connect(ui->pushRoad_13, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_13, "road13|023|022");

    connect(ui->pushRoad_14, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_14, "road14|023|030");

    connect(ui->pushRoad_15, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_15, "road15|033|030");

    connect(ui->pushRoad_16, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_16, "road16|033|034");

    connect(ui->pushRoad_17, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_17, "road17|340|034");

    connect(ui->pushRoad_18, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_18, "road18|340|391");
\
    connect(ui->pushRoad_19, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_19, "road19|171|120");

    connect(ui->pushRoad_20, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_20, "road20|022|020");

    connect(ui->pushRoad_21, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_21, "road21|030|003");

    connect(ui->pushRoad_22, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_22, "road22|034|040");

    connect(ui->pushRoad_23, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_23, "road23|391|440");

    connect(ui->pushRoad_24, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_24, "road24|120|112");

    connect(ui->pushRoad_25, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_25, "road25|120|012");

    connect(ui->pushRoad_26, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_26, "road26|020|012");

    connect(ui->pushRoad_27, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_27, "road27|020|002");

    connect(ui->pushRoad_28, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_28, "road28|003|002");

    connect(ui->pushRoad_29, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_29, "road29|003|004");

    connect(ui->pushRoad_30, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_30, "road30|004|040");

    connect(ui->pushRoad_31, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_31, "road31|040|044");

    connect(ui->pushRoad_32, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_32, "road32|440|044");

    connect(ui->pushRoad_33, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_33, "road33|440|441");

    connect(ui->pushRoad_34, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_34, "road34|112|111");

    connect(ui->pushRoad_35, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_35, "road35|012|011");

    connect(ui->pushRoad_36, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_36, "road36|001|002");

    connect(ui->pushRoad_37, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_37, "road37|004|005");

    connect(ui->pushRoad_38, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_38, "road38|044|045");

    connect(ui->pushRoad_39, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_39, "road39|441|445");

    connect(ui->pushRoad_40, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_40, "road40|110|111");

    connect(ui->pushRoad_41, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_41, "road41|011|110");

    connect(ui->pushRoad_42, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_42, "road42|011|010");

    connect(ui->pushRoad_43, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_43, "road43|001|010");

    connect(ui->pushRoad_44, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_44, "road44|001|006");

    connect(ui->pushRoad_45, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_45, "road45|005|006");

    connect(ui->pushRoad_46, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_46, "road46|005|050");

    connect(ui->pushRoad_47, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_47, "road47|045|050");

    connect(ui->pushRoad_48, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_48, "road48|045|450");

    connect(ui->pushRoad_49, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_49, "road49|450|445");

    connect(ui->pushRoad_50, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_50, "road50|110|700");

    connect(ui->pushRoad_51, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_51, "road51|010|061");

    connect(ui->pushRoad_52, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_52, "road52|006|060");

    connect(ui->pushRoad_53, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_53, "road53|050|055");

    connect(ui->pushRoad_54, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_54, "road54|450|501");

    connect(ui->pushRoad_55, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_55, "road55|700|610");

    connect(ui->pushRoad_56, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_56, "road56|061|610");

    connect(ui->pushRoad_57, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_57, "road57|061|066");

    connect(ui->pushRoad_58, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_58, "road58|060|066");

    connect(ui->pushRoad_59, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_59, "road59|060|056");

    connect(ui->pushRoad_60, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_60, "road60|055|056");

    connect(ui->pushRoad_61, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_61, "road61|055|550");

    connect(ui->pushRoad_62, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_62, "road62|550|501");

    connect(ui->pushRoad_63, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_63, "road63|610|661");

    connect(ui->pushRoad_64, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_64, "road64|066|660");

    connect(ui->pushRoad_65, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_65, "road65|056|560");

    connect(ui->pushRoad_66, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_66, "road66|550|551");

    connect(ui->pushRoad_67, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_67, "road67|661|666");

    connect(ui->pushRoad_68, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_68, "road68|666|660");

    connect(ui->pushRoad_69, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_69, "road69|660|611");

    connect(ui->pushRoad_70, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_70, "road70|611|560");

    connect(ui->pushRoad_71, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_71, "road71|560|556");

    connect(ui->pushRoad_72, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushRoad_72, "road72|551|556");

    /////////////////////
    //END ROAD MAPPING //
    /////////////////////

}

void catan_map::activate_other(){

    ///////////////////////////////
    //START MISCELLANEOS MAPPING //
    ///////////////////////////////

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

    /////////////////////////////
    //END MISCELLANEOS MAPPING //
    /////////////////////////////

}

void catan_map::activate_nodes(){

    ///////////////////////
    //Start of Map Nodes //
    ///////////////////////

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
    signalMapper->setMapping(ui->node_08, "node|8");

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

    /////////////////////
    //End of Map Nodes //
    /////////////////////
}

void catan_map::changeNode(QString node_num){

    //Changes nodes to die roll
    QString cur_node = node_num;
    QString new_button_color = "background-color: rgb(69, 139, 116)";
    QString prev_button_color = "background-color: rgb(255, 255, 255)";
    QString cur_button_color = new_button_color;
    for (int i = 0; i<2; ++i){
        if (cur_node == "1"){
            ui->node_01->setAutoFillBackground(true);
            ui->node_01->setStyleSheet(cur_button_color);
        }
        if (cur_node == "2"){
            ui->node_02->setAutoFillBackground(true);
            ui->node_02->setStyleSheet(cur_button_color);
        }
        if (cur_node == "3"){
            ui->node_03->setAutoFillBackground(true);
            ui->node_03->setStyleSheet(cur_button_color);
        }
        if (cur_node == "4"){
            ui->node_04->setAutoFillBackground(true);
            ui->node_04->setStyleSheet(cur_button_color);
        }
        if (cur_node == "5"){
            ui->node_05->setAutoFillBackground(true);
            ui->node_05->setStyleSheet(cur_button_color);
        }
        if (cur_node == "6"){
            ui->node_06->setAutoFillBackground(true);
            ui->node_06->setStyleSheet(cur_button_color);
        }
        if (cur_node == "7"){
            ui->node_07->setAutoFillBackground(true);
            ui->node_07->setStyleSheet(cur_button_color);
        }
        if (cur_node == "8"){
            ui->node_08->setAutoFillBackground(true);
            ui->node_08->setStyleSheet(cur_button_color);
        }
        if (cur_node == "9"){
            ui->node_09->setAutoFillBackground(true);
            ui->node_09->setStyleSheet(cur_button_color);
        }
        if (cur_node == "10"){
            ui->node_10->setAutoFillBackground(true);
            ui->node_10->setStyleSheet(cur_button_color);
        }
        if (cur_node == "11"){
            ui->node_11->setAutoFillBackground(true);
            ui->node_11->setStyleSheet(cur_button_color);
        }
        if (cur_node == "12"){
            ui->node_12->setAutoFillBackground(true);
            ui->node_12->setStyleSheet(cur_button_color);
        }
        if (cur_node == "13"){
            ui->node_13->setAutoFillBackground(true);
            ui->node_13->setStyleSheet(cur_button_color);
        }
        if (cur_node == "14"){
            ui->node_14->setAutoFillBackground(true);
            ui->node_14->setStyleSheet(cur_button_color);
        }
        if (cur_node == "15"){
            ui->node_15->setAutoFillBackground(true);
            ui->node_15->setStyleSheet(cur_button_color);
        }
        if (cur_node == "16"){
            ui->node_16->setAutoFillBackground(true);
            ui->node_16->setStyleSheet(cur_button_color);
        }
        if (cur_node == "17"){
            ui->node_17->setAutoFillBackground(true);
            ui->node_17->setStyleSheet(cur_button_color);
        }
        if (cur_node == "18"){
            ui->node_18->setAutoFillBackground(true);
            ui->node_18->setStyleSheet(cur_button_color);
        }
        if (cur_node == "19"){
            ui->node_19->setAutoFillBackground(true);
            ui->node_19->setStyleSheet(cur_button_color);
        }
        cur_button_color = prev_button_color;
        cur_node = prev_robber;
    }
    prev_robber = node_num;
}

void catan_map::nodeSelectedOnRobber(QString button){
    QString temp_holder = button.section("|",1,1);
    int nodeNumber = temp_holder.toInt(&robber,10);
    node.placeRobber(nodeNumber);

    //then we get to take a card form a player on that node.
    bool onNode[4];
    for(int i = 0; i<numPlayers; i++)
        onNode[i] = 0;

    for(int i = 0; i<numPlayers; i++){
        onNode[i] = players[i].nodeOnRobber(nodeNumber);
        cout<<"player"<<i<<"  on node: "<<onNode[i]<<endl;
        if(onNode[i] ==1){
            char card = players[i].removeRandomCard();
            cout<<"taking: "<<card<<"  from player"<<i<<"  giving to: "<<iter<<endl;

            players[iter].addCard(card);
         //   players[iter].addCard(players[i].removeRandomCard()); //give current player other cards
        }
    }

    node.placeRobber(nodeNumber);
    changeNode(temp_holder);
    robber = false;
 }

void catan_map::rollSelected(QString button){
    iter++;             //change to next player
    if(iter>=numPlayers)
        iter = 0;

    int i = players[iter].roll() + players[iter].roll();
    cout<<i<<endl;
    QString out = QString::number(i);
    ui->roll_outcome->setText(out);
    qDebug() << "roll code: " << button;
    ui->instruction->setText(player_name + " can buy roads/settlements and trade. Next player roll when ready");
    if(i==7){//roll 7 conditions
        for(int k = 0; k<numPlayers; k++)
            players[k].removeCardsOn7();
        //some sort of wait for node click command to then place robber.
            robber = true;
            ui->instruction->setText(player_name + " has rolled a 7! Choose a node to place the robber at!");
    }
    for(int k = 0; k< numPlayers; k++)
        players[k].gainResources(i,node);

  //  return i;
}

void catan_map::viewHand(QString button){   //Lets you see whats in your hand
    bool ok = true;
    QString player = button.at(7);
    int player_num = player.toInt(&ok,10);
    QMessageBox* vhand;
    vhand = new QMessageBox;
    vhand->setText(players[player_num-1].outputHand());
    vhand->show();
}

void catan_map::update_players(){
    if (iter == 0){
        player_name = "P1";
    }
    if (iter == 1){
        player_name = "P2";
    }
    if (iter == 2){
        player_name = "P3";
    }
    if (iter == 3){
        player_name = "P4";
    }
    // int x = players[i].numberOfResources();
    QString vict_pts = "Victory Points: ";
    QString cards = "Cards Held: ";
    QString cards1 = QString::number(players[0].numberOfResources());
    ui->cardsHeld1_label->setText((cards + cards1));
    QString cards2 = QString::number(players[1].numberOfResources());
    ui->cardsHeld2_label->setText((cards + cards2));
    QString cards3 = QString::number(players[2].numberOfResources());
    ui->cardsHeld3_label->setText((cards + cards3));
    QString cards4 = QString::number(players[3].numberOfResources());
    ui->cardsHeld4_label->setText((cards + cards4));

    QString vict_pts1 = QString::number(players[0].victoryPoints_);
    ui->victoryPnts1->setText(vict_pts + vict_pts1);
    QString vict_pts2 = QString::number(players[1].victoryPoints_);
    ui->victoryPnts2->setText(vict_pts + vict_pts2);
    QString vict_pts3 = QString::number(players[2].victoryPoints_);
    ui->victoryPnts3->setText(vict_pts + vict_pts3);
    QString vict_pts4 = QString::number(players[3].victoryPoints_);
    ui->victoryPnts4->setText(vict_pts + vict_pts4);
}

void catan_map::initial_game_start(QString button){
    if (button.section("|",8,8) == "s" && init_settle_road){
        if(mapper.valid_settlement_check(button,player_name)){
            players[iter].buySettlement(button);
            settlement_output(button);
            init_settle_road = false;
        }
        else{
            ui->instruction->setText("Invalid settlement placement");
        }
    }
    else if (button.startsWith("road") && !init_settle_road){
        qDebug() << "=====================";
        if (mapper.valid_road_check(button,player_name)){
            players[iter].buyRoad();
            players[iter].seeResources();
            qDebug() << "road button: " << button;
            road_output(button);
            init_settle_road = true;
            afterSecondSettlementPlacement++;
            if(afterSecondSettlementPlacement>=5){
                players[iter].collectOriginalCards(node);
                cout<<"blehh"<<endl;
             }
        }
        else{
            ui->instruction->setText("Invalid road placement");
        }
        ++iter;
        if(reverse){
            iter = iter - 2;
            if (iter == -1){
                reverse = false;
                initial_settle = false;
            }
        }
        if(iter == 4){
            iter = 3;
            reverse = true;
        }
    }
    update_players();
    ui->instruction->setText(player_name + ", place a settlement and a road");
    if (!initial_settle){
        ui->instruction->setText("P1, roll the dice when ready!");
    }
}

void catan_map::city_settlement_create(QString button){
    qDebug() << "*************************";
    if (players[iter].affordCity()){
        if (mapper.valid_city_check(button, player_name) && players[iter].affordCity()){
            qDebug() << "City: valid city implemented for: " << button;
            qDebug() << "-------------------------";
            city_output(button);
            players[iter].buyCity(button);
        }
    }
    if (players[iter].affordSettlement()){
        if (mapper.valid_settlement_check(button, player_name)){
            qDebug() << "valid settlement input for: " << button;
            qDebug() << "-------------------------";
            settlement_output(button);
            players[iter].buySettlement(button); //add settlement to player list
        }
    }
}

void catan_map::road_pushed(QString button){
    qDebug() << "=====================";
    if (mapper.valid_road_check(button,player_name)){
        players[iter].buyRoad();
        qDebug() << "road button: " << button;
        road_output(button);
    }
    else{
        ui->instruction->setText("Invalid road placemet!");
    }
}

void catan_map::buyDevCard(QString button){
    if(players[iter].affordDevelopmentCard()){
        players[iter].buyDevelopmentCard();
    }
    else{
        ui->instruction->setText("You can not afford a development card!");
    }

}
