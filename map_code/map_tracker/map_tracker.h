#ifndef MAP_TRACKER_H
#define MAP_TRACKER_H

#include <QtCore>

class map_tracker
{

public:
    map_tracker();
    //for adding the settlement!
    bool valid_settlement_check(QString);
    bool valid_city_check(QString, QString);
    bool valid_road_check(QString, QString);

    void set_settlement(QString, QString);
    void set_city(QString, QString);
    void set_road(QString, QString);

private:
    //add the settlement or road to respective QString

    void add_road(QString);
    void add_settlement(int);
    void add_city(int);
    //find neighbors of respective settlement/road
    QStringList settlement_neighbors(int);
    QStringList road_neighbors(QString);
    bool settle_check(QString);

    QStringList settlements;
    QStringList roads;
    QStringList p_settle_ownership;
    QStringList p_road_ownership;
};

#endif // MAP_TRACKER_H
