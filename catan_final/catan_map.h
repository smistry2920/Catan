#ifndef CATAN_MAP_H
#define CATAN_MAP_H

#include <QMainWindow>
#include <QtCore>
#include "map_tracker/map_tracker.h"
#include "player/Player.h"
//#include "player/Noder.h"

namespace Ui {
    class catan_map;
}

class catan_map : public QMainWindow
{
    Q_OBJECT

public:
    explicit catan_map(QWidget *parent = 0);
    ~catan_map();
    void checkPlayer();

private slots:
    void signalSorter(const QString &); //sorts signals

private:
    ///temporary test code (DELETE WHEN FINISHED!)
    int temp_iterator;

    Ui::catan_map *ui;
    QSignalMapper *signalMapper;
    map_tracker mapper;

    Player players[4];
    int iter;

    Node node;

    void activate_settlements();
    void activate_roads();
    void activate_other();
//<<<<<<< HEAD
    void button_output(QString,QString);
    void settlement_output(QString,QString);
    void city_output(QString,QString);
    void road_output(QString,QString);
//=======
    void activate_nodes();
//>>>>>>> upstream/master

};

#endif // CATAN_MAP_H
