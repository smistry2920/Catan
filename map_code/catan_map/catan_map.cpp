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

    /////////////////////////////////////////////
    //START CITY BUTTON MAPPING!!
    ///////////////////
    connect(ui->pushButton_01, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_01, "01");

    connect(ui->pushButton_02, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_02, "02");

    connect(ui->pushButton_03, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_03, "03");

    connect(ui->pushButton_04, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_04, "04");

    connect(ui->pushButton_05, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_05, "05");

    connect(ui->pushButton_06, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_06, "06");

    connect(ui->pushButton_07, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_07, "07");

    connect(ui->pushButton_08, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_08, "08");

    connect(ui->pushButton_09, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_09, "09");

    connect(ui->pushButton_10, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_10, "10");

    connect(ui->pushButton_11, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_11, "11");

    connect(ui->pushButton_12, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_12, "12");

    connect(ui->pushButton_13, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_13, "13");

    connect(ui->pushButton_14, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_14, "14");

    connect(ui->pushButton_15, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_15, "15");

    connect(ui->pushButton_16, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_16, "16");

    connect(ui->pushButton_17, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_17, "17");

    connect(ui->pushButton_18, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_18, "18");

    connect(ui->pushButton_19, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_19, "19");

    connect(ui->pushButton_20, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_20, "20");

    connect(ui->pushButton_21, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_21, "21");

    connect(ui->pushButton_22, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_22, "22");

    connect(ui->pushButton_23, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_23, "23");

    connect(ui->pushButton_24, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_24, "24");

    connect(ui->pushButton_25, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_25, "25");

    connect(ui->pushButton_26, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_26, "26");

    connect(ui->pushButton_27, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_27, "27");

    connect(ui->pushButton_28, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_28, "28");

    connect(ui->pushButton_29, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_29, "29");

    connect(ui->pushButton_30, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_30, "30");

    connect(ui->pushButton_31, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_31, "31");

    connect(ui->pushButton_32, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_32, "32");

    connect(ui->pushButton_33, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_33, "33");

    connect(ui->pushButton_34, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_34, "34");

    connect(ui->pushButton_35, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_35, "35");

    connect(ui->pushButton_36, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_36, "36");

    connect(ui->pushButton_37, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_37, "37");

    connect(ui->pushButton_38, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_38, "38");

    connect(ui->pushButton_39, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_39, "39");

    connect(ui->pushButton_40, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_40, "40");

    connect(ui->pushButton_41, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_41, "41");

    connect(ui->pushButton_42, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_42, "42");

    connect(ui->pushButton_43, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_43, "43");

    connect(ui->pushButton_44, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_44, "44");

    connect(ui->pushButton_45, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_45, "45");

    connect(ui->pushButton_46, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_46, "46");

    connect(ui->pushButton_47, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_47, "47");

    connect(ui->pushButton_48, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_48, "48");

    connect(ui->pushButton_49, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_49, "49");

    connect(ui->pushButton_50, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_50, "50");

    connect(ui->pushButton_51, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_51, "51");

    connect(ui->pushButton_52, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_52, "52");

    connect(ui->pushButton_53, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_53, "53");

    connect(ui->pushButton_54, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(ui->pushButton_54, "54");

    //////////////////
    //END CITY BUTTON MAPPING
    ////////////////////////////////////////////

    /*---------------------------------------------------------------*/
    /*===============================================================*/
    /*--------------------------------------------------------------*/

    ////////////////////////////////////////////
    //START ROAD MAPPING
    ////////////////



    ///////////////
    //END ROAD MAPPING
    ///////////////////////////////////////////

    /*---------------------------------------------------------------*/
    /*===============================================================*/
    /*--------------------------------------------------------------*/

    ////////////////////////////////////////////
    //START MISCELLANEOS MAPPING
    ////////////////



    ///////////////
    //END MISCELLANEOS MAPPING
    ////////////////////////////////////////////

    //final signal mapping connection (calls signalSorter to sort signals!)
    connect(signalMapper, SIGNAL(mapped(const QString &)), this, SLOT(signalSorter(const QString &)));

}

catan_map::~catan_map()
{
    delete ui;
}

void catan_map::signalSorter(const QString & button)
{
    qDebug() << "made it with " << button;

}
