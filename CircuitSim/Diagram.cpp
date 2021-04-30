#include "Diagram.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>
#include <QScrollBar>
#include <QDebug>


Diagram::Diagram(QWidget *parent) : QWidget(parent)
{
    initializeDiagram();
    status = UNSAVED;
    scale = 1;
    selected = NONE;
    GraphicComponent* comp = new GraphicComponent(220,200,HORIZONTAL,this);
    drawList.push_back(comp);
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

void Diagram::paintEvent(QPaintEvent* event){
    int width = 60000;
    int height = 60000;

    QPainter painter(this);
    QColor backGroundColor(30,33,44);
    QColor penColor(148,152,164);

    painter.setPen(penColor);
    painter.setBrush(backGroundColor);
    painter.drawRect(rect());

    std::list<GraphicComponent*>::iterator it;
    for(it = drawList.begin(); it!=drawList.end(); it++){
            (*drawList.begin())->draw(&painter);
    }

    for(int x = 0; x<width; x+=50){
        painter.drawLine(x,0,x,height);
    }

    for(int y = 0; y<height; y+=50){
        painter.drawLine(0,y,width,y);
    }
    setSelectedObject(NONE);
}

void Diagram::initializeDiagram(){

        zoomIn = new QPushButton(this);
        zoomIn->setFixedSize(50,50);
        zoomOut = new QPushButton(this);
        zoomOut->setFixedSize(50,50);
        this->resize(9000, this->height());

        QVBoxLayout *vbox = new QVBoxLayout(this);
        vbox->setAlignment(Qt::AlignBottom|Qt::AlignRight);
        vbox->addWidget(zoomIn);
        vbox->addWidget(zoomOut);
        vbox->setContentsMargins(0,0,50,50);
        setLayout(vbox);

        connect(zoomIn,SIGNAL(clicked(bool)), this, SLOT(upScale()));
        connect(zoomOut,SIGNAL(clicked(bool)), this, SLOT(downScale()));
    }

    void Diagram::editMode(){
        scale*=1.25;
        update();
    }

    void Diagram::queryMode(){
        scale*=0.75;
        update();
    }

    void Diagram::setSelectedObject(enum type obj){
        selected = obj;
    }


void Diagram::mousePressEvent(QMouseEvent* event){
    int x = event->x();
    int y = event->y();

    if((*drawList.begin())->clicked(x,y) == 0){
        qDebug()<<"clicado cima";
    }else if((*drawList.begin())->clicked(x,y) == 1){
        qDebug()<<"clicado baixo";
    }

    update();
}
    /*void Diagram::mouseMoveEvent(QMouseEvent* event){
        qDebug()<<event->x();
        qDebug()<<event->y();
        event->accept();
    }*/

    /*void mouseReleasedEvent(QMouseEvent* event){

    }*/
