#ifndef GRAPHICCOMPONENT_H
#define GRAPHICCOMPONENT_H

#include <QObject>
#include <QRect>
#include <QPoint>
#include <QPainter>

#define HEIGHT 115
#define WIDTH 50

enum style{VERTICAL,HORIZONTAL};

class GraphicComponent : public QObject
{
    Q_OBJECT
public :
    explicit GraphicComponent(qreal x, qreal y, enum style s = VERTICAL,QObject *parent = nullptr);
    explicit GraphicComponent(QPoint p, enum style s  = VERTICAL,QObject *parent = nullptr);
    int clicked(qreal x, qreal y);
    virtual void draw(QPainter* painter);

signals:


protected:
    qreal x,y;

    QRect vertexArea1;
    QRect vertexArea2;
    QRect boundRect;
    QPixmap* map;
    enum style style;
};

/*
class Resistor : public GraphicComponent
{
    Q_OBJECT
public:
    explicit Resistor(qreal x, qreal y,  enum style s = VERTICAL, QObject *parent = nullptr);
    explicit Resistor(QPoint p, enum style s, QObject *parent = nullptr);
    QRect draw(QPainter* painter);

signals:

};


class Vcc : public GraphicComponent
{
    Q_OBJECT
public:
    explicit Vcc(qreal x, qreal y, enum style s = VERTICAL,QObject *parent = nullptr);
    explicit Vcc(QPoint p, enum style s, QObject *parent = nullptr);
    QRect draw(QPainter* painter);

signals:

};
*/

#endif // GRAPHICCOMPONENT_H
