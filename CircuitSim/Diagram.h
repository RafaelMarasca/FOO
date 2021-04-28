#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QObject>
#include "Circuit.h"

class Diagram : public QObject
{
    Q_OBJECT
public:
    explicit Diagram(QObject *parent = nullptr);

signals:

public slots:


private:
    CCT::Circuit circuit;
    QWidget *window;

};

#endif // DIAGRAM_H
