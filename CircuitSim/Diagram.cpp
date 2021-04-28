#include "Diagram.h"

Diagram::Diagram(QObject *parent) : QObject(parent)
{
    scene = new QGraphicsScene(0,0,300,300);
    scene->addText("hello circuit");
    view.setScene(scene);
}

Diagram::~Diagram()
{
    //delete scene;
}


void Diagram::print(){
    view.show();
}


