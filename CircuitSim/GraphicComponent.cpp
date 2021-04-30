#include "GraphicComponent.h"
#include <QtDebug>
#include <QPen>

GraphicComponent::GraphicComponent(qreal x_insert, qreal y_insert,
                                       enum style s, QObject *parent) : QObject(parent)
{
    x = x_insert;
    y = y_insert;

    vertexArea1 = QRect(x, y, WIDTH, HEIGHT/2);
    vertexArea2 = QRect(x, y + HEIGHT/2, WIDTH, HEIGHT/2);
    style = s;
}

GraphicComponent::GraphicComponent(QPoint p, enum style s, QObject *parent) : QObject(parent)
{
    x = p.x();
    y = p.y();

    vertexArea1 = QRect(x, y, WIDTH, HEIGHT/2);
    vertexArea2 = QRect(x, y + HEIGHT/2, WIDTH, HEIGHT/2);
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

QRect GraphicComponent::draw(QPainter* painter){

    QPixmap resistor(":/components/resourceFile/componentFile/vcc.png");
    QPen pen= painter->pen();
    painter->setPen((QColor(Qt::green)));
    painter->drawPixmap(QRect(x,y,WIDTH,HEIGHT),resistor);
    painter->setPen(pen);
}
/*
Resistor::Resistor(qreal x, qreal y, enum style s,QObject *parent):GraphicComponent(x,y,s,parent){}
Resistor::Resistor(QPoint p, enum style s, QObject *parent):GraphicComponent(p,s,parent){}

QRect Resistor::drawQPainter* painter(){}

*/
