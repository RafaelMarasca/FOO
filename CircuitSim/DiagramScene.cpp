#include "DiagramScene.h"

DiagramScene::DiagramScene(QObject *parent):QGraphicsScene(0, 0, SWIDTH, SHEIGHT, parent)
{
    buildBackground();
}

void DiagramScene::buildBackground(){

    QColor backGroundColor(30,33,44);
    QColor penColor(148,152,164);

    QPen pen(penColor);
    QBrush brush(backGroundColor);

    setBackgroundBrush(brush);

    for(unsigned int x = 0; x < SWIDTH; x+=50){
        QLineF vertical(x,0,x,SHEIGHT);
        addLine(vertical,pen);
    }

    for(unsigned int y = 0; y < SHEIGHT; y+=50){
        QLineF horizontal(0,y,SWIDTH,y);
        addLine(horizontal,pen);
    }
}
