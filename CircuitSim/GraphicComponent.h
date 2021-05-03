/********************************************************************************************
 * @file GraphicComponent.h
 * @authors: Lucas Carvalho; Rafael Marasca Martins
 * @date: 30 04 2021
 * @brief Declaração da classe GraphicComponent para a inserção gráfica de componentes.
 * 
 * Este arquivo contém as delcarações necessárias para se inserir componentes graficamente
 * em um objeto da classe Diagram.
 *  
 ********************************************************************************************/

#ifndef GRAPHICCOMPONENT_H
#define GRAPHICCOMPONENT_H

#include "Graph.h"
#include "Component.h"

#include <QObject>
#include <QRect>
#include <QPoint>
#include <QPainter>

#define HEIGHT 115
#define WIDTH 50

enum orien{VERTICAL,HORIZONTAL};

class GraphicComponent : public QObject
{
    Q_OBJECT

public :
    explicit GraphicComponent(int x, int y,  unsigned int vtx1, unsigned int vtx2,
                              enum orien s, QObject *parent = nullptr);
    int clickedArea(int x, int y);
    void draw(QPainter* painter);
    int getHeight();
    int getWidth();
    QPoint getBottom();
    QPoint getTop();
    QPoint getLeft();
    QPoint getRight();
    QPixmap getMap();
    QRect getBoundRect();

    enum orien orientation;
    enum orien getOrientation();
    void setVertex1(unsigned int vtx);
    void setVertex2(unsigned int vtx);
    unsigned int getVertex1();
    unsigned int getVertex2();
    std::string getLabel();
    virtual CMP::type getType() =0;
    double getValue();
    void setValue(double newValue);
    QPoint getVertex1Point();
    QPoint getVertex2Point();

signals:
    void clickedVertex(int Area,GraphicComponent*);
    void clicked(bool checked = false);


protected:
    int x,y;

    QRect vertexArea1;
    QRect vertexArea2;

    QRect boundRect;
    QPixmap map;

    unsigned int vertex1,vertex2;

    CMP::type componentType;
    QString label;
    double value;
};

class Resistor : public GraphicComponent
{
    Q_OBJECT
    static unsigned int resCounter;
public:
    explicit Resistor(int x, int y,  unsigned int vtx1, unsigned int vtx2,
                      enum orien s = VERTICAL, QObject *parent = nullptr);
    CMP::type getType();
signals:

};

class Vcc : public GraphicComponent
{
    Q_OBJECT
    static unsigned int vccCounter;
public:
    explicit Vcc(int x, int y,  unsigned int vtx1, unsigned int vtx2,
                 enum orien s = VERTICAL,QObject *parent = nullptr);
    CMP::type getType();

signals:

};

#endif // GRAPHICCOMPONENT_H
