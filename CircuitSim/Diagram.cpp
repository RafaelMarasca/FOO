#include "Diagram.h"

Diagram::Diagram(QObject *parent) : QObject(parent)
{
    scene = new QGraphicsScene;
}

Diagram::~Diagram()
{
    delete scene;
}


void Diagram::print(){
    scene->addText("hello circuit");
    QGraphicsView view(scene);
    view.show();
}


