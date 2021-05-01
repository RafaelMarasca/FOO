#ifndef GRAPHICCOMPONENT_H
#define GRAPHICCOMPONENT_H

#include <QObject>
#include <QRect>
#include <QPoint>
#include <QPainter>
#include "Graph.h"
#include "Component.h"

#define HEIGHT 115
#define WIDTH 50

enum orien{VERTICAL,HORIZONTAL};

class GraphicComponent : public QObject
{
    Q_OBJECT

    static unsigned int vertexNum;
public :
    explicit GraphicComponent(int x, int y,enum orien s, QObject *parent = nullptr);
    int clickedArea(int x, int y);
    void draw(QPainter* painter);
    int getHeight();
    int getWidth();
    void makeCon(int vtx1, int vtx2, GraphicComponent* C);
    static unsigned int getVertexNum(){return vertexNum;};
    QPoint getBottom();
    QPoint getTop();
    QPoint getLeft();
    QPoint getRight();

    enum orien orientation;
    enum orien getOrientation();
    void addLine(QLine);
    void setNegative(int vtx);
    void setPositive(int vtx);
    int getPositive();
    int getNegative();

    //void removeLine();

signals:
    void clickedVertex(int Area,GraphicComponent*);
    void clicked(bool checked = false);


protected:
    int x,y;

    QRect vertexArea1;
    QRect vertexArea2;

    QRect boundRect;
    QPixmap* map;

    unsigned int vertex1,vertex2;
    int negative, positive;
    std::list<QLine> lines;

    CMP::type componentType();
};

class Resistor : public GraphicComponent
{
    Q_OBJECT
public:
    explicit Resistor(int x, int y,  enum orien s = VERTICAL, QObject *parent = nullptr);

signals:

};

class Vcc : public GraphicComponent
{
    Q_OBJECT
public:
    explicit Vcc(int x, int y, enum orien s = VERTICAL,QObject *parent = nullptr);

signals:

};

#endif // GRAPHICCOMPONENT_H
