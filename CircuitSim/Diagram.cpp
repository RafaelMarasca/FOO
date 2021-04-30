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
    selected = NONE;
    mode = EDIT;
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

    for(int x = 0; x<width; x+=50){
        painter.drawLine(x,0,x,height);
    }

    for(int y = 0; y<height; y+=50){
        painter.drawLine(0,y,width,y);
    }

    int i = 0;
    std::list<GraphicComponent*>::iterator it;
    for(it = drawList.begin(); it!=drawList.end(); it++){
            (*it)->draw(&painter);
        qDebug()<<i;
        i++;
    }

    setSelectedObject(NONE);
}

void Diagram::initializeDiagram(){

    editButton = new QPushButton(this);
    editButton->setFixedSize(51,51);

    QPixmap editPixmap(":/icons/resourceFile/iconFile/pencilIcon.png");
    QIcon editIcon(editPixmap.scaled(51, 51));

    editButton->setIcon(editIcon);
    editButton->setIconSize(QSize(51, 51));

    playButton = new QPushButton(this);
    playButton->setFixedSize(51,51);

    QPixmap playPixmap(":/icons/resourceFile/iconFile/playIcon.png");
    QIcon playIcon(playPixmap.scaled(51, 51));

    playButton->setIcon(playIcon);
    playButton->setIconSize(QSize(51, 51));


    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setAlignment(Qt::AlignBottom|Qt::AlignRight);
    vbox->addWidget(editButton);
    vbox->addWidget(playButton);
    vbox->setContentsMargins(0,0,51,51);

    setLayout(vbox);

    connect(editButton,SIGNAL(clicked(bool)), this, SLOT(editMode()));
    connect(playButton,SIGNAL(clicked(bool)), this, SLOT(queryMode()));
}

void Diagram::setSelectedObject(enum type obj){
    selected = obj;
}


void Diagram::mousePressEvent(QMouseEvent* event){
    int x = event->x();
    int y = event->y();

    GraphicComponent* C;

    switch(selected){

        case VCC90:
            C = new Vcc(x,y,VERTICAL,this);
            break;

        case VCC180:
            C = new Vcc(x,y,HORIZONTAL,this);
            break;

        case RES90:
            C = new Resistor(x,y,VERTICAL,this);
            break;

        case RES180:
            C = new Resistor(x,y,HORIZONTAL,this);
            break;

        default:
            C = new Resistor(x,y,HORIZONTAL,this);
            break;
    }

    drawList.push_back(C);

    /*if((*drawList.begin())->clickedArea(x,y) == 1){
        qDebug()<<"clicado cima";
    }else if((*drawList.begin())->clickedArea(x,y) == 2){
        qDebug()<<"clicado baixo";
    }*/

    update();
}

void Diagram::queryMode(){
    mode = QUERY;
}

void Diagram::editMode(){
    mode = EDIT;
}
    /*void Diagram::mouseMoveEvent(QMouseEvent* event){
        qDebug()<<event->x();
        qDebug()<<event->y();
        event->accept();
    }*/

    /*void mouseReleasedEvent(QMouseEvent* event){

    }*/
