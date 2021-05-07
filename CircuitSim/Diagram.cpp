/********************************************************************************************
 * @file Diagram.cpp
 * @authors: Lucas Carvalho; Rafael Marasca Martins
 * @date: 30 04 2021
 * @brief Implementação da classe Diagram.
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

//Inicialização das variáveis estáticas que representam as cores do tema do diagrama.
QColor Diagram::backgroundColor = QColor(DEFAULT_BGC);
QColor Diagram::gridColor = QColor(DEFAULT_LC);
QColor Diagram::componentColor = QColor(DEFAULT_CC);
QColor Diagram::selectedColor = QColor(DEFAULT_SC);


void Diagram::setBGColor(QColor color){
    if(not color.isValid())
        throw std::string("Cor inválida");

    backgroundColor = color;
}

void Diagram::setGridColor(QColor color){
    if(not color.isValid())
        throw std::string("Cor inválida");

    gridColor = color;
}

void Diagram::setComponentColor(QColor color){
    if(not color.isValid())
        throw std::string("Cor inválida");

    componentColor = color;
}

void Diagram::setSelectedColor(QColor color){
    if(not color.isValid())
        throw std::string("Cor inválida");

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

//Constrói o diagrama.
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


//Inicializa os botões e layout do Widget.
void Diagram::initializeDiagram(){

    //Botões de edição e play.
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

    //Layout do Diagrama
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setAlignment(Qt::AlignBottom|Qt::AlignRight);
    vbox->addWidget(editButton);
    vbox->addWidget(playButton);
    vbox->setContentsMargins(0,0,51,51);

    setLayout(vbox);

    //Conecta os sinais do botão aos métodos do diagrama.
    connect(editButton,SIGNAL(clicked(bool)), this, SLOT(editMode()));
    connect(playButton,SIGNAL(clicked(bool)), this, SLOT(queryMode()));

    //Desativa o botão de edição, pois o diagrama se inicia no modo de edição
    editButton->setEnabled(false);

    //Menus popup de edição.
    editMenu = new QMenu(this);
    QAction* editValueAct = new QAction("Editar Valor",this);
    QAction* removeAct = new QAction("Remover Componente",this);
    editMenu->addAction(editValueAct);
    editMenu->addAction(removeAct);

    //Conecta os sinais do menu popup de edição aos métodos do diagrama.
    connect(editValueAct,SIGNAL(triggered(bool)),this,SLOT(showEditDialog()));
    connect(removeAct,SIGNAL(triggered(bool)),this,SLOT(remove()));

    //Menus popup de consulta.
    queryMenu = new QMenu(this);
    QAction* queryAct = new QAction("Consultar Dados",this);
    queryMenu->addAction(queryAct);

    //Conecta os sinais do menu popup de consulta aos métodos do diagrama.
    connect(queryAct,SIGNAL(triggered(bool)),this,SLOT(query()));

    //Ativa o rastreamento do cursor do mouse.
    QWidget::setMouseTracking(true);
}

//Altera o nome do arquivo que contém o diagrama.
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
        setStatus(ERROR); //Altera o status do arquivo para erro de carregamento.
    }else{
        setStatus(OK);//Altera o status do arquivo para Ok.
    }

    //Escreve no arquivo os dados necessários para se construir o mesmo circuito
    //ao abrir este arquivo com o método load.
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
        throw std::string("Falha ao abrir arquivo");
        setStatus(ERROR);//Altera o status do arquivo para erro de carregamento.
    }
    else{
        setStatus(OK);//Altera o status do arquivo para OK.
    }

    //Lê do arquivo os dados necessários para se recriar o circuito salvo anteriormente.
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

    //Adiciona os componente e suas conexões.
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

    //Chama o paintEvent para Atualizar os gráficos do progrma.
    update();
}

void Diagram::setStatus(enum stats newStatus){
    if(status == newStatus or (status ==UNSAVED and newStatus != OK))
        return;

    //Emite os sinais necessários para se comunicar com a MainWindow.
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

    //Tamanho do diagrama (Grande o suficiente para se completar
    //a tela toda com a grade do plano de fundo
    int width = 60000;
    int height = 60000;

    QPainter painter(this);

    //Desenha o plano de fundo
    painter.setBrush(Diagram::backgroundColor);
    painter.drawRect(rect());

    //Desenha a grade do plano de fundo.
    painter.setPen(gridColor);

    for(int x = 0; x<width; x+=50){
        painter.drawLine(x,0,x,height);
    }

    for(int y = 0; y<height; y+=50){
        painter.drawLine(0,y,width,y);
    }

    //Chama o método de desenho de cada componente,
    //se o componente estiver selecionado, o destaca com a cor de seleção.
    std::vector<GraphicComponent*>::iterator it;
    for(it = drawList.begin(); it!=drawList.end(); it++){
        if(*it == selectedComponent){
            (*it)->draw(&painter,selectedColor);
        }else
            (*it)->draw(&painter,componentColor);
    }

    //Altera a caneta para que se desenhem as conexões entre os componentes.
    QPen p;
    p.setWidth(3);
    p.setColor(componentColor);
    painter.setPen(p);

    //Procura as conexões no grafo de conexões e em cada componente.
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

    //Faz o componente selecionado através do botão acompanhar o cursor do mouse.
    if(selectedButton!=NONE){
        std::pair<QRect,QPixmap> map =  getPixMap(selectedButton);
        QRect aux(cursorLocation.x(),cursorLocation.y(),map.first.width(),
                  map.first.height());
        painter.drawPixmap(aux,map.second);
    }

    //Altera a cor da caneta para que a conexão que esta a se desenhar
    //fique com a cor destacada.
    p.setColor(selectedColor);
    painter.setPen(p);

    //Faz uma conexão acompanhar o cursor do mouse enquanto está sendo desenhada.
    if(clickedStack.size()){
        painter.drawLine(selectedPrev,cursorLocation);
    }
}


void Diagram::setSelectedButton(enum cmpStyle button){
    selectedButton = button;
    while(clickedStack.size())
            clickedStack.pop();
}


void Diagram::mousePressEvent(QMouseEvent* event){

    //Coordenadas do ponto clicado pelo mouse.
    int x = event->x();
    int y = event->y();

    //Ações do mouse quando nenhum botão de inserção foi pressionado.
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

    //remove os componentes da pilha de objetos clicados anteriormente
    while(clickedStack.size())
        clickedStack.pop();

    //Ações a se tomar quando um botão de inserção for pressionado antes do evento
    //de clique do mouse.
    if(selectedButton != NONE){
        QRect rect;

        if(selectedButton == VCC180 or selectedButton == RES180){
            rect = QRect(x,y,HEIGHT,WIDTH);
        }else{
            rect = QRect(x,y,WIDTH,HEIGHT);
        }

        //Verifica colisão entre os componentes já inseridos e o componente que está se inserindo.
        std::vector<GraphicComponent*>::iterator it;
        for(it = drawList.begin();it != drawList.end();it++){
            if(rect.intersects((*it)->getBoundRect())){
                QMessageBox insertionFail;
                insertionFail.setText("Não é permitido inserir um componente sobre o outro");
                insertionFail.exec();
                return;
            }
        }
        //Se não houver colisão, insere na tela e no circuito.
        insert(x,y);
    }
}

//Método auxiliar para as ações do botão direito do mouse.
void Diagram::rightButtonClicked(int x,int y, int cArea){

    if(mode == EDIT){
        editMenu->popup(QPoint(x,y));
    }else{
        queryMenu->popup(QPoint(x,y));
    }
}

//Método auxiliar para as ações do botão esquerdo do mouse do mouse.
void Diagram::leftButtonClicked(int x,int y, int cArea){

    if(mode == EDIT){
        clickedControl(x,y,cArea);
    }
}

void Diagram::insert(int x, int y){

    GraphicComponent* C;

    //Verifica qual botão foi pressionado antes de se inserir.
    switch(selectedButton){

        case VCC90:{
            C = new Vcc(x,y,vtxCounter,vtxCounter+1,VERTICAL,this);
            circuit.addComponent(CMP::VCC,C->getLabel(),C->getValue(),C->getVertex1(),C->getVertex2());
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

    //Insere os vértices do componente no grafo de conexões.
    connections.insertVertex(vtxCounter);
    connections.insertVertex(vtxCounter+1);
    vtxCounter+=2;

    //Adiciona o componente ao vector de desenhos.
    drawList.push_back(C);

    setSelectedButton(NONE);
    setStatus(MODIFIED);

    update();
}

//Modo de Consulta.
void Diagram::queryMode(){

    //Inicializa o circuito.
    circuit.initialize();

    //Destativa o botão play.
    playButton->setEnabled(false);

    //Ativa o botão de edição.
    editButton->setEnabled(true);

    emit statusBarText("Modo de Consulta");
    mode = QUERY;
}

void Diagram::editMode(){
    //Reseta o circuito.
    circuit.reset();

    //Ativa o botão de play.
    playButton->setEnabled(true);

    //Desativa o botão de edição.
    editButton->setEnabled(false);

    emit statusBarText("Modo de Edição");
    mode = EDIT;
}

void Diagram::clickedControl(int x, int y, int index){

    //Se houver um componente na pilha de componentes clicados anteriormente
    if(clickedStack.size()==1){
        std::pair<int,GraphicComponent*> aux = clickedStack.top();

        //Verifica se a a tentativa de conexão é entre os vértices de um mesmo
        //componente, ou se a conexão já existe e impede a conexão.
        if(connections.query(aux.first,index)||connections.query(index,aux.first)||
            aux.second == selectedComponent){

            while(clickedStack.size())
                clickedStack.pop();

            selectedComponent = nullptr;
            return;
        }

        //Insere uma conexão entre os componentes.
        connections.insertEdge(aux.first,index);
        QString str = "Aux" + QString::number(wireCounter);
        circuit.addComponent(CMP::RESISTOR,str.toStdString(),0,aux.first,index);
        wireCounter++;

        while(clickedStack.size())
            clickedStack.pop();

        setStatus(MODIFIED);
        selectedComponent = nullptr;

    }else{
        //Se nenhum componente foi clicado anteriormente, adiciona na pilha de clicados.
        clickedStack.push(std::pair<int,GraphicComponent*>(index,selectedComponent));
        //Seta o ponto clicado do componente como ponto clicado anteriormente.
        selectedPrev = QPoint(x,y);
    }
}

void Diagram::edit(double newValue){

    circuit.editComponent(selectedComponent->getLabel(),newValue);
    selectedComponent->setValue(newValue);
    setStatus(MODIFIED);
}


//Mostra a janela de edição de componente.
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
        //Remove as conexões do grafo de conexões
        connections.removeVertex(selectedComponent->getVertex1());
        connections.removeVertex(selectedComponent->getVertex2()-1);


        //Obtém os nomes dos componentes que devem ser removidos junto
        //com o componente que se deseja excluir.
        std::vector<std::string>aux;
        std::vector<unsigned int> vtx1 = circuit.getEdges(selectedComponent->getVertex1());
        std::vector<unsigned int> vtx2 = circuit.getEdges(selectedComponent->getVertex2());
        aux.push_back(selectedComponent->getLabel());

        for(unsigned int i =0; i<vtx1.size();i++){
            aux.push_back(circuit.getComponentLabel(vtx1[i]));
        }

        for(unsigned int i =0; i<vtx2.size();i++){
            aux.push_back(circuit.getComponentLabel(vtx2[i]));
        }

        //Remove o componente do circuito.
        circuit.removeComponent(selectedComponent->getLabel());

        //Remove os componentes que devem ser excluídos em conjunto.
        for(unsigned i = 1; i< aux.size(); i++){
            if(aux[i]!=aux[0])
                circuit.removeComponent(aux[i]);
        }

    vtxCounter-=2;

    QMessageBox rmMessage;

    rmMessage.setText("O componente foi removido");

    bool flag = 0;

    //Atualiza o vector de desenho.
    std::vector<GraphicComponent*>::iterator auxIt = drawList.end();
    std::vector<GraphicComponent*>::iterator it;
    for(it = drawList.begin(); it != drawList.end(); it++){
        if(flag){
            (*it)->setVertex1((*it)->getVertex1()-2);
            (*it)->setVertex2((*it)->getVertex2()-2);
            std::string aux = (*it)->getLabel();
            (*it)->updateName();
            circuit.editComponent(aux,(*it)->getLabel());
        }else if (selectedComponent == (*it)){
            auxIt = it;
            flag = true;
        }
    }

    drawList.erase(auxIt);

    delete selectedComponent;
    selectedComponent = nullptr;


    while(clickedStack.size())
        clickedStack.pop();

    rmMessage.exec();

    update();
}

//Exibe a dialog de consulta.
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
   //Retorna a localização do cursor do mouse.
    cursorLocation=event->pos();
    update();
}

std::pair<QRect,QPixmap> Diagram::getPixMap(enum cmpStyle type){

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

