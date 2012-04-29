#ifndef MAP_TRACKER_H
#define MAP_TRACKER_H

#include <QtCore>

class map_tracker
{

public:
    map_tracker();
    //for adding the settlement!
    bool valid_settlement_check(QString, QString);
    bool valid_city_check(QString, QString);
    bool valid_road_check(QString, QString);

private:
    //add the settlement/city or road to respective QString
    void set_city(int);
    void add_road(QString);
    void add_settlement(QString,QString);

    //find neighbors of respective settlement/road
    QStringList settlement_neighbors(int);
    QStringList road_neighbors(QString);

    //check settlements for existing settlements
    bool settle_check(QString);

    QStringList settlements;
    QStringList roads;
    QStringList p_settle_ownership;
    QStringList p_road_ownership;
};

#endif // MAP_TRACKER_H
