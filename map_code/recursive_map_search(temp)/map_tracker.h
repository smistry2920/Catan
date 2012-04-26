#ifndef MAP_TRACKER_H
#define MAP_TRACKER_H

#include <QtCore>

class map_tracker
{

public:
    map_tracker();
    //for adding the settlement!
    bool clicked_settlement(QString);
    bool clicked_road(QString);

private:
    //check if valid settlement or road
    bool valid_settlement_check(QString);
    bool valid_road_check(QString);
    //add the settlement or road to respective QString
    QString add_settlement();
    QString add_road();
    //find neighbors of respective settlement/road
    QString settlement_neighbors(QString);
    QString road_neighbors(QString);

    QStringList settlements;
    QStringList roads;
};

#endif // MAP_TRACKER_H
