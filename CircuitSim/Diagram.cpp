#include "Diagram.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsWidget>
#include<QGraphicsLinearLayout>

Diagram::Diagram(QWidget *parent) : QWidget(parent)
{
    scene = new QGraphicsScene(0,0,SWIDTH,SHEIGHT,this);
    buildSceneBackGround();
    view = new DiagramView(scene,this);
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

    /*std::ofstream file;

    file.open(fileName, std::ios::out|std::ios::binary);

    if(!file.is_open())
        throw std::string("Failed to open file");
    else*/
        setStatus(OK);

    /*try {
        circuit.save(file);
    }catch (std::string log) {
        QString str;
        qDebug()<<str;
    }*/
}

void Diagram::load(){
    /*std::ifstream file;

    file.open(fileName, std::ios::in|std::ios::binary);

    if(!file.is_open()){
        throw std::string("Failed to open file");
        setStatus(ERROR)
    }
    else*/
        setStatus(OK);

    /*try {
        circuit.save(file);
    }catch (std::string log) {
        throw std::string("loadError");
        setStatus(ERROR);
    }*/
}

void Diagram::setStatus(enum sts newStatus){
    if(status == newStatus)
        return;

    switch(newStatus){
    case MODIFIED:
        status = MODIFIED;
        emit modified(true);
        break;

    case UNSAVED:
        status = UNSAVED;
        break;

    case OK:
        status = OK;
        emit modified(false);
        break;

    case ERROR:
        emit loadError(true);
    break;
    }
}

enum sts Diagram::getStatus(){
    return status;
}


void Diagram::buildSceneBackGround(){

    QColor backGroundColor(30,33,44);
    QColor penColor(148,152,164);

    QPen pen(penColor);
    QBrush brush(backGroundColor);

    scene->setBackgroundBrush(brush);

    for(unsigned int x = 0; x < SWIDTH; x+=50){
        QLineF vertical(x,0,x,SHEIGHT);
        scene->addLine(vertical,pen);
    }

    for(unsigned int y = 0; y < SHEIGHT; y+=50){
        QLineF horizontal(0,y,SWIDTH,y);
        scene->addLine(horizontal,pen);
    }
}
