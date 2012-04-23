#ifndef CATAN_MAP_H
#define CATAN_MAP_H

#include <QMainWindow>
#include <QtCore>

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
    Ui::catan_map *ui;
    QSignalMapper *signalMapper;

};

#endif // CATAN_MAP_H
