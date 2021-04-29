#include "Diagram.h"
#include <QDebug>
#include <iostream>
#include <fstream>
#include <QString>

Diagram::Diagram(QObject *parent) :QObject(parent)
{
    scene = new QGraphicsScene(this);
    scene->addText("hello circuit");
    view = new QGraphicsView(scene);
    status = UNSAVED;
}

Diagram::~Diagram(){
    delete view;
}

QWidget* Diagram::getView(){
    return view;
}

void Diagram::setFileName(QString file){
    fileName = file.toStdString();
}

QString Diagram::getFileName(){
    return QString::fromStdString(fileName);
}

void Diagram::save(){

    std::ofstream file;

    file.open(fileName, std::ios::out|std::ios::binary);

    if(!file.is_open())
        throw std::string("Failed to open file");

    try {
        circuit.save(file);
    }catch (std::string log) {
        QString str;
        qDebug()<<str;
    }

    status = OK;
}

enum sts Diagram::getStatus(){return status;}

