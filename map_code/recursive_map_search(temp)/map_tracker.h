#ifndef MAP_TRACKER_H
#define MAP_TRACKER_H

#include <QtCore>

class map_tracker
{

public:
    map_tracker();
    //for adding the settlement!
    bool valid_settlement_check(QString);
    bool valid_road_check(QString);

    bool set_settlement(QString);
    bool set_road(QString);

private:
    //add the settlement or road to respective QString

    void add_road(QString);
    void add_settlement(int);
    //find neighbors of respective settlement/road
    QStringList settlement_neighbors(int);
    QStringList road_neighbors(QString);
    bool settle_check(QString);

    QStringList settlements;
    QStringList roads;
};

#endif // MAP_TRACKER_H
