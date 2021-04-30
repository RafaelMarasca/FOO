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
    explicit GraphicComponent(int x, int y, enum style s = VERTICAL,QObject *parent = nullptr);
    explicit GraphicComponent(QPoint p, enum style s  = VERTICAL,QObject *parent = nullptr);
    int clickedArea(int x, int y);
    void draw(QPainter* painter);
    int getHeight();
    int getWidth();

signals:
    void clickedVertex(int Area);
    void clicked(bool checked = false);


protected:
    int x,y;

    QRect vertexArea1;
    QRect vertexArea2;

    QRect boundRect;
    QPixmap* map;

    int vertex1;
    int vertex2;
};

class Resistor : public GraphicComponent
{
    Q_OBJECT
public:
    explicit Resistor(int x, int y,  enum style s = VERTICAL, QObject *parent = nullptr);
    explicit Resistor(QPoint p, enum style s, QObject *parent = nullptr);

signals:

};

class Vcc : public GraphicComponent
{
    Q_OBJECT
public:
    explicit Vcc(int x, int y, enum style s = VERTICAL,QObject *parent = nullptr);
    explicit Vcc(QPoint p, enum style s, QObject *parent = nullptr);

signals:

};

#endif // GRAPHICCOMPONENT_H
