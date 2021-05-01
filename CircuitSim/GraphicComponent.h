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
    static unsigned int getVertexNum(){return vertexNum;};
    QPoint getBottom();
    QPoint getTop();
    QPoint getLeft();
    QPoint getRight();

    enum orien orientation;
    enum orien getOrientation();
    unsigned int getVertex1();
    unsigned int getVertex2();
    std::string getLabel();

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

    CMP::type componentType();
    QString label;
};

class Resistor : public GraphicComponent
{
    Q_OBJECT
    static unsigned int resCounter;
public:
    explicit Resistor(int x, int y,  enum orien s = VERTICAL, QObject *parent = nullptr);

signals:

};

class Vcc : public GraphicComponent
{
    Q_OBJECT
    static unsigned int vccCounter;
public:
    explicit Vcc(int x, int y, enum orien s = VERTICAL,QObject *parent = nullptr);

signals:

};

#endif // GRAPHICCOMPONENT_H
