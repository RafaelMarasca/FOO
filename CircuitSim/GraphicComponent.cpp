#include "GraphicComponent.h"
#include <QtDebug>
#include <QPen>
#include <QPoint>


unsigned int GraphicComponent::vertexNum = 0;

GraphicComponent::GraphicComponent(int x_ins, int y_ins, enum orien s, QObject *parent) : QObject(parent)
{
    x = x_ins;
    y = y_ins;

    if(s == VERTICAL){
        vertexArea1 = QRect(x, y, WIDTH, HEIGHT/2);
        vertexArea2 = QRect(x, y + HEIGHT/2, WIDTH, HEIGHT/2);
        boundRect = QRect(x,y,WIDTH, HEIGHT);
    }else{
        vertexArea1 = QRect(x, y, HEIGHT/2,WIDTH);
        vertexArea2 = QRect(x+HEIGHT/2, y, HEIGHT, WIDTH);
        boundRect = QRect(x,y,HEIGHT,WIDTH);
    }
    vertex1 = vertexNum++;
    vertex2 = vertexNum++;
    orientation = s;
    negative = -1;
    positive = -1;

}

int GraphicComponent::clickedArea(int x_check, int y_check){

    if(y_check > vertexArea1.y() and y_check< (vertexArea1.y()+vertexArea1.height())){
        if(x_check > vertexArea1.x() and x_check< vertexArea1.x()+vertexArea1.width()){
            emit clicked(true);
            emit clickedVertex(vertex1,this);
            return 1;
        }
    }

    if(y_check > vertexArea2.y() and y_check< vertexArea2.y()+vertexArea2.height()){
        if(x_check > vertexArea2.x() and x_check< vertexArea2.x()+vertexArea2.width()){
            emit clicked(true);
            emit clickedVertex(vertex2,this);
            return 2;
        }
    }

    return 0;
}

void  GraphicComponent::addLine(QLine line){
    lines.push_back(line);
}

void GraphicComponent::draw(QPainter* painter){
    painter->drawPixmap(boundRect,*map);

    QPen p= painter->pen();
    painter->setPen(QColor(Qt::green));
    std::list<QLine>::iterator it;
    for(it = lines.begin(); it != lines.end(); it++){
        painter->drawLine((*it));
    }
    painter->setPen(p);

}

int GraphicComponent::getHeight(){return boundRect.height();}
int GraphicComponent::getWidth(){return boundRect.width();}
QPoint GraphicComponent::getTop(){
    QPoint p = boundRect.topLeft();
    int x = p.x();
    p.setX(x+(boundRect.width()/2));

    return p;
}
QPoint GraphicComponent::getBottom(){

    QPoint p = boundRect.bottomLeft();
    int x = p.x();
    p.setX(x+(boundRect.width()/2));

    return p;
}

QPoint GraphicComponent::getRight(){

    QPoint p = boundRect.topRight();
    int y = p.y();
    p.setY(y+(boundRect.height()/2));

    return p;
}

QPoint GraphicComponent::getLeft(){

    QPoint p = boundRect.topLeft();
    int y = p.y();
    p.setY(y+(boundRect.height()/2));

    return p;
}

enum orien GraphicComponent::getOrientation(){return orientation;}

Resistor::Resistor(int x, int y, enum orien s,QObject *parent):GraphicComponent(x,y,s,parent){

    if(s == VERTICAL){
        map = new QPixmap(":/components/resourceFile/componentFile/resistor90.png");
    }else {
        map = new QPixmap(":/components/resourceFile/componentFile/resistor180.png");
    }
}

Vcc::Vcc(int x, int y, enum orien s,QObject *parent):GraphicComponent(x,y,s,parent){

    if(s == VERTICAL){
        map = new QPixmap(":/components/resourceFile/componentFile/vcc90.png");
    }else {
        map = new QPixmap(":/components/resourceFile/componentFile/vcc180.png");
    }
}

void GraphicComponent::setNegative(int vtx){
    negative = vtx;
}

void GraphicComponent::setPositive(int vtx){
    positive = vtx;
}


int GraphicComponent::getPositive(){
    return positive;
}
int GraphicComponent::getNegative(){
    return negative;
}
