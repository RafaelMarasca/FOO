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
    vertex1 = 0;
    vertex2 = 0;
}

GraphicComponent::GraphicComponent(QPoint p, enum style s, QObject *parent) : QObject(parent)
{
    x = p.x();
    y = p.y();

    if(s == VERTICAL){
        vertexArea1 = QRect(x, y, WIDTH, HEIGHT/2);
        vertexArea2 = QRect(x, y + HEIGHT/2, WIDTH, HEIGHT/2);
        boundRect = QRect(x,y,WIDTH, HEIGHT);
    }else{
        vertexArea1 = QRect(x, y, HEIGHT/2,WIDTH);
        vertexArea2 = QRect(x+HEIGHT/2, y, HEIGHT, WIDTH);
        boundRect = QRect(x,y,HEIGHT,WIDTH);
    }

    vertex1 = 0;
    vertex2 = 0;
}


int GraphicComponent::clickedArea(int x_check, int y_check){

    if(y_check > vertexArea1.y() and y_check< (vertexArea1.y()+vertexArea1.height())){
        if(x_check > vertexArea1.x() and x_check< vertexArea1.x()+vertexArea1.width()){
            emit clicked(true);
            emit clickedVertex(1);
            return 1;
        }
    }

    if(y_check > vertexArea2.y() and y_check< vertexArea2.y()+vertexArea2.height()){
        if(x_check > vertexArea2.x() and x_check< vertexArea2.x()+vertexArea2.width()){
            emit clicked(true);
            emit clickedVertex(2);
            return 2;
        }
    }

    return 0;
}

void GraphicComponent::draw(QPainter* painter){
    painter->drawPixmap(boundRect,*map);
}

int GraphicComponent::getHeight(){return boundRect.height();}
int GraphicComponent::getWidth(){return boundRect.width();}


Resistor::Resistor(int x, int y, enum style s,QObject *parent):GraphicComponent(x,y,s,parent){

    if(s == VERTICAL){
        map = new QPixmap(":/components/resourceFile/componentFile/resistor90.png");
    }else {
        map = new QPixmap(":/components/resourceFile/componentFile/resistor180.png");
    }
}

Resistor::Resistor(QPoint p, enum style s, QObject *parent):GraphicComponent(p,s,parent){

    if(s == VERTICAL){
        map = new QPixmap(":/components/resourceFile/componentFile/resistor90.png");
    }else {
        map = new QPixmap(":/components/resourceFile/componentFile/resistor180.png");
    }
}


Vcc::Vcc(int x, int y, enum style s,QObject *parent):GraphicComponent(x,y,s,parent){

    if(s == VERTICAL){
        map = new QPixmap(":/components/resourceFile/componentFile/vcc90.png");
    }else {
        map = new QPixmap(":/components/resourceFile/componentFile/vcc180.png");
    }
}

Vcc::Vcc(QPoint p, enum style s, QObject *parent):GraphicComponent(p,s,parent){

    if(s == VERTICAL){
        map = new QPixmap(":/components/resourceFile/componentFile/vcc90.png");
    }else {
        map = new QPixmap(":/components/resourceFile/componentFile/vcc180.png");
    }
}

