#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "Circuit.h"

class Diagram : public QObject
{
    Q_OBJECT
public:
    explicit Diagram(QObject *parent = nullptr);
    ~Diagram();

signals:

public slots:
   // void insert();
   // void remove();
   // void load();
   // void save();
   // void query();
    void print();

private:
    QGraphicsScene* scene;
    CCT::Circuit circuit;
};

#endif // DIAGRAM_H
