#include "GraphicComponent.h"
#include <QtDebug>
#include <QPen>

GraphicComponent::GraphicComponent(int x_insert, int y_insert,
                                       enum style s, QObject *parent) : QObject(parent)
{
    x = x_insert;
    y = y_insert;

    if(s == VERTICAL){
        vertexArea1 = QRect(x, y, WIDTH, HEIGHT/2);
        vertexArea2 = QRect(x, y + HEIGHT/2, WIDTH, HEIGHT/2);
        boundRect = QRect(x,y,WIDTH, HEIGHT);
    }else{
        vertexArea1 = QRect(x, y, HEIGHT/2,WIDTH);
        vertexArea2 = QRect(x+HEIGHT/2, y, HEIGHT, WIDTH);
        boundRect = QRect(x,y,HEIGHT,WIDTH);
    }

<<<<<<< HEAD
    vertex1 = 0;
    vertex2 = 0;
=======
    map = new QPixmap(":/components/resourceFile/componentFile/vcc180.png");
>>>>>>> fc064f6c755408ab65966ed828d79b727ee2ec09
}

GraphicComponent::GraphicComponent(QPoint p, enum style s, QObject *parent) : QObject(parent)
{
    x = p.x();
    y = p.y();

    if(s == VERTICAL){
        vertexArea1 = QRect(x, y, WIDTH, HEIGHT/2);
        vertexArea2 = QRect(x, y + HEIGHT/2, WIDTH, HEIGHT/2);
    }else{
        vertexArea1 = QRect(x, y, HEIGHT/2,WIDTH);
        vertexArea2 = QRect(x+HEIGHT/2, y, HEIGHT, WIDTH);
    }
}


int GraphicComponent::clicked(int x_check, int y_check){

    if(y_check > vertexArea1.y() and y_check< (vertexArea1.y()+vertexArea1.height())){
        if(x_check > vertexArea1.x() and x_check< vertexArea1.x()+vertexArea1.width()){
            return 1;
        }
    }

    if(y_check > vertexArea2.y() and y_check< vertexArea2.y()+vertexArea2.height()){
        if(x_check > vertexArea2.x() and x_check< vertexArea2.x()+vertexArea2.width()){
            return 2;
        }
    }

    return 0;
}

void GraphicComponent::draw(QPainter* painter){
    painter->drawPixmap(boundRect,*map);
}


Resistor::Resistor(int x, int y, enum style s,QObject *parent):GraphicComponent(x,y,s,parent){

    if(s == VERTICAL){
        map = new QPixmap(":/components/resourceFile/componentFile/resistor.png");
    }else {
        map = new QPixmap(":/components/resourceFile/componentFile/resistor.png");
    }
}

Resistor::Resistor(QPoint p, enum style s, QObject *parent):GraphicComponent(p,s,parent){

    if(s == VERTICAL){
        map = new QPixmap(":/components/resourceFile/componentFile/resistor.png");
    }else {
        map = new QPixmap(":/components/resourceFile/componentFile/resistor.png");
    }
}


Vcc::Vcc(int x, int y, enum style s,QObject *parent):GraphicComponent(x,y,s,parent){

    if(s == VERTICAL){
        map = new QPixmap(":/components/resourceFile/componentFile/resistor.png");
    }else {
        map = new QPixmap(":/components/resourceFile/componentFile/resistor.png");
    }
}

Vcc::Vcc(QPoint p, enum style s, QObject *parent):GraphicComponent(p,s,parent){

    if(s == VERTICAL){
        map = new QPixmap(":/components/resourceFile/componentFile/vcc.png");
    }else {
        map = new QPixmap(":/components/resourceFile/componentFile/vcc.png");
    }
}

