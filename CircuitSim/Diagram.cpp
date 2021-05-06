/********************************************************************************************
 * @file Diagram.cpp
 * @authors: Lucas Carvalho; Rafael Marasca Martins
 * @date: 30 04 2021
 * @brief Declaração da classe Numeric.
 * 
 * Este arquivo contém as implementações dos métodos e membros da classe Diagram.
 * 
 * A classe Diagram fornece as facilidades para inserir objetos da classe GraphicsComponent
 * graficamente, identificar as interações do usuário com estes objetos, bem como,
 * interligar a implementação gráfica com a parte numérica.
 *  
 ********************************************************************************************/

#include "Diagram.h"

#include <fstream>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>
#include <QScrollBar>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QInputDialog>

QColor Diagram::backgroundColor = QColor(DEFAULT_BGC);
QColor Diagram::gridColor = QColor(DEFAULT_LC);
QColor Diagram::componentColor = QColor(DEFAULT_CC);
QColor Diagram::selectedColor = QColor(DEFAULT_SC);

void Diagram::setBGColor(QColor color){
    backgroundColor = color;
}

void Diagram::setGridColor(QColor color){
    gridColor = color;
}
void Diagram::setComponentColor(QColor color){
    componentColor = color;
}
void Diagram::setSelectedColor(QColor color){
    selectedColor = color;
}

QColor Diagram::getBGColor(){
    return backgroundColor;
}

QColor Diagram::getGridColor(){
    return gridColor;
}

QColor Diagram::getComponentColor(){
    return componentColor;
}

QColor Diagram::getSelectedColor(){
    return selectedColor;
}

Diagram::Diagram(QWidget *parent) : QWidget(parent)
{
    initializeDiagram();
    status = UNSAVED;
    selectedButton = NONE;
    selectedComponent = nullptr;
    mode = EDIT;
    wireCounter = 0;
    selectedPrev = QPoint(0,0);
    cursorLocation = QPoint(0,0);
    vtxCounter = 0;
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

    if(!file.is_open()){
        throw std::string("Falha ao Salvar");
        setStatus(ERROR);
    }else
        setStatus(OK);

    unsigned int size = drawList.size();
    file.write(reinterpret_cast<char*>(&size),sizeof(unsigned int));

    unsigned int aux;

    std::vector<GraphicComponent*>::iterator it;
    for(it = drawList.begin(); it!=drawList.end(); it++){
        aux = (*it)->getBoundRect().x();
        file.write(reinterpret_cast<char*>(&aux),sizeof(unsigned int));
        aux = (*it)->getBoundRect().y();
        file.write(reinterpret_cast<char*>(&aux),sizeof(unsigned int));
        aux = (*it)->getOrientation();
        file.write(reinterpret_cast<char*>(&aux),sizeof(unsigned int));
        aux = (*it)->getType();
        file.write(reinterpret_cast<char*>(&aux),sizeof(unsigned int));
        double value = (*it)->getValue();
        file.write(reinterpret_cast<char*>(&value),sizeof(double));
    }

    size = connections.getVertexNumber();

    file.write(reinterpret_cast<char*>(&size),sizeof(unsigned int));

    for(unsigned int i = 0; i<connections.getVertexNumber();i++){
        for(unsigned int j = 0; j<connections.getVertexNumber(); j++){
            unsigned int aux = 0;
            if(connections.query(i,j)){
                aux = 1;
                file.write(reinterpret_cast<char*>(&aux), sizeof(unsigned int));
                aux = 0;
            }else
                file.write(reinterpret_cast<char*>(&aux), sizeof(unsigned int));
        }
    }

    file.close();
}

void Diagram::load(){
    std::ifstream file;

    file.open(fileName, std::ios::in|std::ios::binary);

    if(!file.is_open()){
        throw std::string("Failed to open file");
        setStatus(ERROR);
    }
    else
        setStatus(OK);

    unsigned int size;
    file.read(reinterpret_cast<char*>(&size),sizeof(unsigned int));
    qDebug()<<size;

   for(unsigned int i = 0; i < size; i++){
       unsigned int x,y,orientation,type;
       double value;
       file.read(reinterpret_cast<char*>(&x),sizeof(unsigned int));
       file.read(reinterpret_cast<char*>(&y),sizeof(unsigned int));
       file.read(reinterpret_cast<char*>(&orientation),sizeof(unsigned int));
       file.read(reinterpret_cast<char*>(&type),sizeof(unsigned int));
       file.read(reinterpret_cast<char*>(&value), sizeof(double));

       GraphicComponent* C;

       if(type==CMP::VCC){
           C = new Vcc(x,y,vtxCounter,vtxCounter+1,orien(orientation),this);
           circuit.addComponent(CMP::VCC,C->getLabel(),value,C->getVertex1(),C->getVertex2());
       }else{
           C = new Resistor(x,y,vtxCounter,vtxCounter+1,orien(orientation),this);
           circuit.addComponent(CMP::RESISTOR,C->getLabel(),value,C->getVertex1(),C->getVertex2());
       }
       drawList.push_back(C);
    }

   file.read(reinterpret_cast<char*>(&size),sizeof(unsigned int));

    connections = GRF::adjacencyMatrix(size);

    unsigned int aux =0;

    for(unsigned int i = 0; i< size; i++){
        for(unsigned int j = 0; j < size; j++){
            file.read(reinterpret_cast<char*>(&aux),sizeof(unsigned int));
            if(aux == 1){
                connections.insertEdge(i,j);
                QString str = "Aux" + QString::number(wireCounter);
                circuit.addComponent(CMP::RESISTOR,str.toStdString(),0,i,j);
                wireCounter++;
                aux = 0;
            }
        }
    }
    file.close();
    update();
}

void Diagram::setStatus(enum stats newStatus){
    if(status == newStatus or (status ==UNSAVED and newStatus != OK))
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

enum stats Diagram::getStatus(){
    return status;
}

void Diagram::paintEvent(QPaintEvent* event){
    int width = 60000;
    int height = 60000;

    QPainter painter(this);

    painter.setPen(Diagram::gridColor);
    painter.setBrush(Diagram::backgroundColor);
    painter.drawRect(rect());

    painter.setPen(gridColor);
    for(int x = 0; x<width; x+=50){
        painter.drawLine(x,0,x,height);
    }

    for(int y = 0; y<height; y+=50){
        painter.drawLine(0,y,width,y);
    }

    std::vector<GraphicComponent*>::iterator it;
    for(it = drawList.begin(); it!=drawList.end(); it++){
        if(*it == selectedComponent){
            (*it)->draw(&painter,selectedColor);
        }else
            (*it)->draw(&painter,componentColor);
    }

    QPen p;
    p.setWidth(3);
    p.setColor(componentColor);
    painter.setPen(p);

    for(unsigned int i = 0; i < connections.getVertexNumber(); i++){
        for(unsigned int j = 0; j < connections.getVertexNumber(); j++){
           if(connections.query(i,j)){
             QPoint p1,p2;
               if(i%2 == 0){
                   p1 = drawList[i/2]->getVertex1Point();
               }else{
                   p1 = drawList[i/2]->getVertex2Point();
               }

               if(j%2 == 0){
                   p2 = drawList[j/2]->getVertex1Point();
               }else{
                   p2 = drawList[j/2]->getVertex2Point();
               }
            painter.drawLine(p1,p2);
           }
        }
    }

    p.setColor(selectedColor);
    painter.setPen(p);

    if(selectedButton!=NONE){
        std::pair<QRect,QPixmap> map =  getPixMap(selectedButton);
        QRect aux(cursorLocation.x(),cursorLocation.y(),map.first.width(),
                  map.first.height());
        painter.drawPixmap(aux,map.second);
    }

    if(clickedStack.size()){
        painter.drawLine(selectedPrev,cursorLocation);
    }
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

    editButton->setEnabled(false);

    editMenu = new QMenu(this);
    QAction* editValueAct = new QAction("Editar Valor",this);
    QAction* removeAct = new QAction("Remover Componente",this);
    editMenu->addAction(editValueAct);
    editMenu->addAction(removeAct);

    connect(editValueAct,SIGNAL(triggered(bool)),this,SLOT(showEditDialog()));
    connect(removeAct,SIGNAL(triggered(bool)),this,SLOT(remove()));

    queryMenu = new QMenu(this);
    QAction* queryAct = new QAction("Consultar Dados",this);
    queryMenu->addAction(queryAct);

    connect(queryAct,SIGNAL(triggered(bool)),this,SLOT(query()));

    QWidget::setMouseTracking(true);
}

void Diagram::setSelectedButton(enum buttonType button){
    selectedButton = button;
    while(clickedStack.size())
            clickedStack.pop();
}


void Diagram::mousePressEvent(QMouseEvent* event){

    int x = event->x();
    int y = event->y();

    if(selectedButton == NONE){
        std::vector<GraphicComponent*>::iterator it;
        for(it = drawList.begin();it != drawList.end();it++){
            int cArea = (*it)->clickedArea(x,y);
            if(cArea!=-1){
                selectedComponent = *it;
                if(event->button()==Qt::LeftButton){
                    leftButtonClicked(x,y,cArea);
                }else if(event->button()==Qt::RightButton){
                    rightButtonClicked(x,y,cArea);
                }
                return;
            }
        }
    }

    selectedComponent = nullptr;

    while(clickedStack.size())
        clickedStack.pop();

    if(selectedButton != NONE){
        QRect rect;
        if(selectedButton == VCC180 or selectedButton == RES180){
            rect = QRect(x,y,HEIGHT,WIDTH);
        }else{
            rect = QRect(x,y,WIDTH,HEIGHT);
        }
        std::vector<GraphicComponent*>::iterator it;
        for(it = drawList.begin();it != drawList.end();it++){
            if(rect.intersects((*it)->getBoundRect())){
                return;
            }
        }
        insert(x,y);
    }
}

void Diagram::rightButtonClicked(int x,int y, int cArea){

    if(mode == EDIT){
        editMenu->popup(QPoint(x,y));
    }else{
        queryMenu->popup(QPoint(x,y));
    }
}
void Diagram::leftButtonClicked(int x,int y, int cArea){

    if(mode == EDIT){
        clickedControl(x,y,cArea);
    }
}

void Diagram::insert(int x, int y){

    GraphicComponent* C;

    switch(selectedButton){

        case VCC90:{
            C = new Vcc(x,y,vtxCounter,vtxCounter+1,VERTICAL,this);
            try{
                circuit.addComponent(CMP::VCC,C->getLabel(),C->getValue(),C->getVertex1(),C->getVertex2());
            }catch(char const* str){
                qDebug()<<str;
            }
        }break;

        case VCC180:{
            C = new Vcc(x,y,vtxCounter,vtxCounter+1,HORIZONTAL,this);
            circuit.addComponent(CMP::VCC,C->getLabel(),C->getValue(),C->getVertex1(),C->getVertex2());
        }break;

        case RES90:{
            C = new Resistor(x,y,vtxCounter,vtxCounter+1,VERTICAL,this);
            circuit.addComponent(CMP::RESISTOR,C->getLabel(),C->getValue(),C->getVertex1(),C->getVertex2());

            break;
        }
        case RES180:{
            C = new Resistor(x,y,vtxCounter,vtxCounter+1,HORIZONTAL,this);
            circuit.addComponent(CMP::RESISTOR,C->getLabel(),C->getValue(),C->getVertex1(),C->getVertex2());
        }break;

        default:
            return;
            break;
    }
    connections.insertVertex(vtxCounter);
    connections.insertVertex(vtxCounter+1);
    vtxCounter+=2;
    drawList.push_back(C);
    setSelectedButton(NONE);
    setStatus(MODIFIED);
    update();
}


void Diagram::queryMode(){
    circuit.initialize();
    playButton->setEnabled(false);
    editButton->setEnabled(true);
    emit statusBarText("Modo de Consulta");
    mode = QUERY;
}

void Diagram::editMode(){
    circuit.reset();
    playButton->setEnabled(true);
    editButton->setEnabled(false);
    emit statusBarText("Modo de Edição");
    mode = EDIT;
}

void Diagram::clickedControl(int x, int y, int index){

    if(clickedStack.size()==1){
        std::pair<int,GraphicComponent*> aux = clickedStack.top();

        if(connections.query(aux.first,index)||connections.query(index,aux.first)||
            aux.second == selectedComponent){
            while(clickedStack.size())
                clickedStack.pop();
            selectedComponent = nullptr;
            return;
        }

        connections.insertEdge(aux.first,index);
        QString str = "Aux" + QString::number(wireCounter);
        circuit.addComponent(CMP::RESISTOR,str.toStdString(),0,aux.first,index);
        wireCounter++;

        while(clickedStack.size())
            clickedStack.pop();

        setStatus(MODIFIED);
        selectedComponent = nullptr;

    }else{
        clickedStack.push(std::pair<int,GraphicComponent*>(index,selectedComponent));
        selectedPrev = QPoint(x,y);
    }
}

void Diagram::edit(double newValue){

    circuit.editComponent(selectedComponent->getLabel(),newValue);
    selectedComponent->setValue(newValue);
    setStatus(MODIFIED);
}

void Diagram::showEditDialog(){
    QInputDialog editDialog(this);
    editDialog.setDoubleDecimals(7);
    editDialog.setDoubleMaximum(100000);
    editDialog.setDoubleMinimum(0);
    editDialog.setInputMode(QInputDialog::DoubleInput);
    connect(&editDialog,SIGNAL(doubleValueSelected(double)),this,SLOT(edit(double)));
    editDialog.exec();
    selectedComponent = nullptr;
}


void Diagram::remove(){
    try{
        connections.removeVertex(selectedComponent->getVertex1());
        connections.removeVertex(selectedComponent->getVertex2()-1);
    }catch(std::string str){}
    try{
        std::vector<std::string>aux;
        std::vector<unsigned int> vtx1 = circuit.getEdges(selectedComponent->getVertex1());
        std::vector<unsigned int> vtx2 = circuit.getEdges(selectedComponent->getVertex2());
        circuit.print();
        qDebug()<<"-------------";
        aux.push_back(selectedComponent->getLabel());

        for(unsigned int i =0; i<vtx1.size();i++){

            //qDebug()<<vtx1[i];
            aux.push_back(circuit.getComponentLabel(vtx1[i]));
        }

        for(unsigned int i =0; i<vtx2.size();i++){
           //qDebug()<<vtx2[i];
            aux.push_back(circuit.getComponentLabel(vtx2[i]));
        }
        circuit.removeComponent(selectedComponent->getLabel());
        circuit.print();
        qDebug()<<"-------------";

        //circuit.print();

        for(unsigned i = 1; i< aux.size(); i++){
            qDebug()<<QString::fromStdString(aux[i]);
            try{
                if(aux[i]!=aux[0])
                {    circuit.removeComponent(aux[i]);
                    circuit.print();
                    qDebug()<<"-------------";
                }
            }catch(std::string str){

            }
        }

    }catch(char const* str){
        std::cout<<str;
    }

    vtxCounter-=2;

    QMessageBox rmMessage;

    QString str = QString::fromStdString(selectedComponent->getLabel());
    str += " foi removido!";

    rmMessage.setText(str);

    bool flag = 0;

    std::vector<GraphicComponent*>::iterator aux = drawList.end();
    std::vector<GraphicComponent*>::iterator it;
    for(it = drawList.begin(); it != drawList.end(); it++){
        if(flag){
            (*it)->setVertex1((*it)->getVertex1()-2);
            (*it)->setVertex2((*it)->getVertex2()-2);
            std::string aux = (*it)->getLabel();
            (*it)->updateName();
            circuit.editComponent(aux,(*it)->getLabel());
        }else if (selectedComponent == (*it)){
            aux = it;
            flag = true;
        }
    }

    drawList.erase(aux);
    delete selectedComponent;
    selectedComponent = nullptr;
    while(clickedStack.size()){

        clickedStack.pop();
    }

    rmMessage.exec();

    update();
}

void Diagram::query(){

    QString currentStr = "Corrente: ";
    QString voltageStr = "Tensão: ";
    currentStr+= QString::number(circuit.getCurrent(selectedComponent->getLabel()));
    voltageStr+= QString::number(circuit.getVoltage(selectedComponent->getLabel()));
    QMessageBox queryMessage(QMessageBox::NoIcon,"Informações do Componente",currentStr+"A"+"\n"+voltageStr+"V");

    queryMessage.exec();
    selectedComponent = nullptr;
}

void Diagram::mouseMoveEvent(QMouseEvent* event){
    cursorLocation=event->pos();
    update();
}

std::pair<QRect,QPixmap> Diagram::getPixMap(enum buttonType type){

    QRect boundRect;
    QPixmap map;

    switch(type){
        case VCC90:{
            map = QPixmap(":/components/resourceFile/componentFile/vcc90.png");
            boundRect.setHeight(HEIGHT);
            boundRect.setWidth(WIDTH);
        }break;

        case VCC180:{
            map = QPixmap(":/components/resourceFile/componentFile/vcc180.png");
            boundRect.setHeight(WIDTH);
            boundRect.setWidth(HEIGHT);
        }break;

        case RES90:{
            map = QPixmap(":/components/resourceFile/componentFile/resistor90.png");
            boundRect.setHeight(HEIGHT);
            boundRect.setWidth(WIDTH);
        }break;

        case RES180:{
            map = QPixmap(":/components/resourceFile/componentFile/resistor180.png");
            boundRect.setHeight(WIDTH);
            boundRect.setWidth(HEIGHT);
        }break;

        default:
        break;
    }
    return std::pair<QRect,QPixmap>(boundRect,map);
}

