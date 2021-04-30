#include "GraphicComponent.h"
#include <QtDebug>
#include <QPen>

GraphicComponent::GraphicComponent(qreal x_insert, qreal y_insert,
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

    map = new QPixmap(":/components/resourceFile/componentFile/vcc180.png");
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
    style = s;

}


int GraphicComponent::clicked(qreal x_check, qreal y_check){

    if(y_check > vertexArea1.y() and y_check< (vertexArea1.y()+vertexArea1.height())){
        if(x_check > vertexArea1.x() and x_check< vertexArea1.x()+vertexArea1.width()){
            return 0;
        }
    }

    if(y_check > vertexArea2.y() and y_check< vertexArea2.y()+vertexArea2.height()){
        if(x_check > vertexArea2.x() and x_check< vertexArea2.x()+vertexArea2.width()){
            return 1;
        }
    }

    return -1;
}

void GraphicComponent::draw(QPainter* painter){

    QPen pen= painter->pen();
    painter->setPen((QColor(Qt::green)));
    painter->drawPixmap(boundRect,*map);
    painter->setPen(pen);
}
/*
Resistor::Resistor(qreal x, qreal y, enum style s,QObject *parent):GraphicComponent(x,y,s,parent){}
Resistor::Resistor(QPoint p, enum style s, QObject *parent):GraphicComponent(p,s,parent){}

QRect Resistor::drawQPainter* painter(){}

*/
