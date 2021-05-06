/********************************************************************************************
 * @file MainWindow.cpp
 * @authors: Lucas Carvalho; Rafael Marasca Martins
 * @date: 28 04 2021
 * @brief Implementação da classe MainWindow.
 * 
 * Este arquivo contém as implementações dos métodos e membros da classe MainWindow.
 * 
 * A classe MainWindow controla o fluxo de execução com base nas interações do usuário.
 *  
 ********************************************************************************************/


#include "MainWindow.h"
#include "Diagram.h"

#include <iostream>
#include <fstream>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QPushButton>
#include <QTabWidget>
#include <QTabBar>
#include <QFileInfo>
#include <QPixmap>
#include <QIcon>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QLabel>
#include <QColorDialog>

MainWindow* MainWindow::instance = nullptr;

MainWindow* MainWindow::getMainWindow(){
    if(instance == nullptr){
        instance = new MainWindow;
    }
    return instance;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Simulador de Circuitos Resistivos");
    setGeometry(0,0,800,600);
    loadConfig();

    initializeMenu();
    initializeToolbar();
    initializeTabs();
    initializeStatusBar();
}

void MainWindow::initializeMenu(){
    mainBar = new QMenuBar(this);
    mainBar->setGeometry(0,0,300,30);

    fileMenu = new QMenu("Arquivo",this);
    mainBar->addMenu(fileMenu);

    newFileAct = new QAction("Novo Arquivo",this);
    fileMenu->addAction(newFileAct);

    connect(newFileAct,SIGNAL(triggered(bool)),this,SLOT(newFile()));

    openFileAct = new QAction("Abrir",this);
    fileMenu->addAction(openFileAct);

    connect(openFileAct,SIGNAL(triggered(bool)),this, SLOT(openFile()));

    saveFileAct = new QAction("Salvar",this);
    fileMenu->addAction(saveFileAct);

    connect(saveFileAct,SIGNAL(triggered(bool)),this, SLOT(saveFile()));

    saveFileAsAct = new QAction("Salvar como",this);
    fileMenu->addAction(saveFileAsAct);

     connect(saveFileAsAct,SIGNAL(triggered(bool)),this, SLOT(saveFileAs()));

    prefMenu = new QMenu("Preferências",this);
    mainBar->addMenu(prefMenu);

    setBGColorAct = new QAction("Mudar Plano de Fundo");
    prefMenu->addAction(setBGColorAct);

    connect(setBGColorAct, SIGNAL(triggered(bool)),this,SLOT(setBGColor()));

    setGridColorAct = new QAction("Mudar Cor da Grade");
    prefMenu->addAction(setGridColorAct);

    connect(setGridColorAct, SIGNAL(triggered(bool)),this,SLOT(setGridColor()));

    setComponentColorAct = new QAction("Mudar Cor dos Componentes");
    prefMenu->addAction(setComponentColorAct);

    connect(setComponentColorAct, SIGNAL(triggered(bool)),this,SLOT(setComponentColor()));

    setSelectedColorAct = new QAction("Mudar Cor da Seleção");
    prefMenu->addAction(setSelectedColorAct);

    connect(setSelectedColorAct, SIGNAL(triggered(bool)),this,SLOT(setSelectedColor()));

    resetConfigAct = new QAction("Restaurar Configurações Padrão");
    prefMenu->addAction(resetConfigAct);

    connect(resetConfigAct, SIGNAL(triggered(bool)),this,SLOT(resetConfig()));

    helpMenu = new QMenu("Ajuda",this);
    mainBar->addMenu(helpMenu);

    tutorialAct = new QAction("Tutorial",this);
    helpMenu->addAction(tutorialAct);

    setMenuBar(mainBar);
}

void MainWindow::initializeToolbar() {

    toolbar = new QToolBar(this);

    QPushButton* vcc90Button = new QPushButton(toolbar);
    connect(vcc90Button,SIGNAL(clicked(bool)), this, SLOT(drawVcc90()));
    QPixmap vcc90Pixmap(":/icons/resourceFile/iconFile/vcc90.png");
    QIcon vcc90ButtonIcon(vcc90Pixmap.scaled(65, 65));
    vcc90Button->setIcon(vcc90ButtonIcon);
    vcc90Button->setIconSize(QSize(65, 65));
    toolbar->addWidget(vcc90Button);


    QPushButton* vcc180Button = new QPushButton(toolbar);
    connect(vcc180Button,SIGNAL(clicked(bool)), this, SLOT(drawVcc180()));
    QPixmap vcc180Pixmap(":/icons/resourceFile/iconFile/vcc180.png");
    QIcon vcc180ButtonIcon(vcc180Pixmap.scaled(65, 65));
    vcc180Button->setIcon(vcc180ButtonIcon);
    vcc180Button->setIconSize(QSize(65, 65));
    toolbar->addWidget(vcc180Button);


    QPushButton* res90Button = new QPushButton(toolbar);
    connect(res90Button,SIGNAL(clicked(bool)),this, SLOT(drawRes90()));
    QPixmap res90Pixmap(":/icons/resourceFile/iconFile/resistor90.png");
    QIcon res90ButtonIcon(res90Pixmap.scaled(65, 65));
    res90Button->setIcon(res90ButtonIcon);
    res90Button->setIconSize(QSize(65, 65));
    toolbar->addWidget(res90Button);

    QPushButton* res180Button = new QPushButton(toolbar);
    connect(res180Button,SIGNAL(clicked(bool)), this, SLOT(drawRes180()));
    QPixmap res180Pixmap(":/icons/resourceFile/iconFile/resistor180.png");
    QIcon res180ButtonIcon(res180Pixmap.scaled(65, 65));
    res180Button->setIcon(res180ButtonIcon);
    res180Button->setIconSize(QSize(65, 65));
    toolbar->addWidget(res180Button);

    toolbar->setMovable(false);

    addToolBar(Qt::RightToolBarArea, toolbar);
}

void MainWindow::initializeStatusBar(){
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
}

void MainWindow::initializeTabs(){
    tabs = new QTabWidget(this);
    tabs->setTabsClosable(true);
    connect(tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(int)));
    setCentralWidget(tabs);
}

void MainWindow::newFile(){

    Diagram* D = new Diagram(this);
    diagrams.push_back(D);

    QString untitled = "*untitled ";
    untitled.append(QString::number(tabs->count()));

    tabs->addTab(D,untitled);

    connect(D,SIGNAL(modified(bool)),this,SLOT(setTabStatus(bool)));
    connect(D,SIGNAL(statusBarText(QString)),statusBar,SLOT(showMessage(QString)));
}

void MainWindow::openFile(){
    QString fileName = QFileDialog::getOpenFileName(this,"Abrir arquivo", "*.cct");

    if(fileName.isNull())
         return;

    Diagram* D = new Diagram(this);
    D->setFileName(fileName);

    try {
        D->load();
    }  catch (std::string s) {
        QMessageBox::warning(this, "CUIDADO", "Não foi possível abrir o arquivo.");
        return;
    }
    QFileInfo info(fileName);

    diagrams.push_back(D);
    tabs->addTab(D,info.fileName());
    statusBar->showMessage("\""+fileName+"\" Aberto com sucesso!");
    connect(D,SIGNAL(statusBarText(QString)),statusBar,SLOT(showMessage(QString)));
    connect(D,SIGNAL(modified(bool)),this,SLOT(setTabStatus(bool)));
}

void MainWindow::saveFile(){

    if(tabs->count() == 0)
        return;

    int index = tabs->currentIndex();
    std::list<Diagram*>::iterator it = diagrams.begin();
    advance(it,index);

    if((*it)->getStatus()==UNSAVED){
        saveFileAs();
        return;
    }

    (*it)->save();
    statusBar->showMessage("\""+(*it)->getFileName()+"\" Salvo com sucesso!");
}

void MainWindow::saveFileAs(){

    if(tabs->count()==0)
        return;

    QString fileName = QFileDialog::getSaveFileName(this, "*.cct");

    if(fileName.isNull())
        return;

    int index = tabs->currentIndex();
    std::list<Diagram*>::iterator it = diagrams.begin();
    advance(it,index);

    QFileInfo info(fileName);

    tabs->setTabText(index,info.fileName());
    (*it)->setFileName(fileName);
    (*it)->save();
    statusBar->showMessage("\""+(*it)->getFileName()+"\" Salvo com sucesso!");
}

void MainWindow::setTabStatus(bool modified){
    int index = tabs->currentIndex();
    QString fileName = tabs->tabText(index);

    if(modified){
        fileName.prepend('*');
    }else if(fileName.at(0)=='*'){
        fileName.remove(0,1);
    }
    tabs->setTabText(index, fileName);
}

void MainWindow::closeFile(int index){

    std::list<Diagram*>::iterator it = diagrams.begin();
    std::advance(it,index);

    if((*it)->getStatus() == UNSAVED or (*it)->getStatus() == MODIFIED){
        QMessageBox::StandardButton b = QMessageBox::question(this, "CUIDADO", "Sair sem salvar?");
        if(b != QMessageBox::StandardButton::Yes)
            return;
    }

    diagrams.erase(it);
    delete (*it);
    tabs->removeTab(index);
}

void MainWindow::drawVcc90(){
    if(tabs->count() == 0)
        return;

    int index = tabs->currentIndex();
    std::list<Diagram*>::iterator it = diagrams.begin();
    advance(it,index);

    (*it)->setSelectedButton(VCC90);
}

void MainWindow::drawVcc180(){
    if(tabs->count() == 0)
        return;

    int index = tabs->currentIndex();
    std::list<Diagram*>::iterator it = diagrams.begin();
    advance(it,index);

    (*it)->setSelectedButton(VCC180);
}

void MainWindow::drawRes90(){
    if(tabs->count() == 0)
        return;

    int index = tabs->currentIndex();
    std::list<Diagram*>::iterator it = diagrams.begin();
    advance(it,index);

    (*it)->setSelectedButton(RES90);
}


void MainWindow::drawRes180(){
    if(tabs->count() == 0)
        return;

    int index = tabs->currentIndex();
    std::list<Diagram*>::iterator it = diagrams.begin();
    advance(it,index);

    (*it)->setSelectedButton(RES180);
}


void MainWindow::loadConfig(){
    std::ifstream config;
    config.open("config.txt",std::ios::in);

    if(not config.is_open()){
        saveConfig();
        return;
    }

    std::string hexCode;

    getline(config,hexCode);
    Diagram::setBGColor(QColor(hexCode.c_str()));

    getline(config,hexCode);
    Diagram::setGridColor(QColor(hexCode.c_str()));

    getline(config,hexCode);
    Diagram::setComponentColor(QColor(hexCode.c_str()));

    getline(config,hexCode);
    Diagram::setSelectedColor(QColor(hexCode.c_str()));

    config.close();
}

void MainWindow::saveConfig(){
    std::ofstream config;
    config.open("config.txt",std::ios::out);

    if(not config.is_open()){
        return;
    }

    QString hexCode;

    hexCode = Diagram::getBGColor().name();
    config<<hexCode.toStdString();
    config<<std::endl;

    hexCode = Diagram::getGridColor().name();
    config<<hexCode.toStdString();
    config<<std::endl;

    hexCode = Diagram::getComponentColor().name();
    config<<hexCode.toStdString();
    config<<std::endl;

    hexCode = Diagram::getSelectedColor().name();
    config<<hexCode.toStdString();
    config<<std::endl;

    config.close();
}


void MainWindow::setBGColor(){
    QColor color =QColorDialog::getColor(QColor(DEFAULT_BGC),this,"Selecione a cor para o plano de fundo");
    try{
        Diagram::setBGColor(color);
        saveConfig();
    }catch(std::string){

    }
}

void MainWindow::setGridColor(){
    QColor color =QColorDialog::getColor(QColor(DEFAULT_LC),this,"Selecione a cor para a grade");
    try{
        Diagram::setGridColor(color);
        saveConfig();
    }catch(std::string){

    }

}
void MainWindow::setComponentColor(){

    QColor color =QColorDialog::getColor(QColor(DEFAULT_CC),this,"Selecione a cor para os componentes");
    try{
        Diagram::setComponentColor(color);
        saveConfig();
    }catch(std::string){

    }

}

void MainWindow::setSelectedColor(){

    QColor color =QColorDialog::getColor(QColor(DEFAULT_SC),this,"Selecione a cor para a seleção");
    try{
        Diagram::setSelectedColor(color);
        saveConfig();
    }catch(std::string){

    }
}

void MainWindow::resetConfig(){

    try{
        Diagram::setSelectedColor(DEFAULT_SC);
        Diagram::setComponentColor(DEFAULT_CC);
        Diagram::setGridColor(DEFAULT_LC);
        Diagram::setBGColor(DEFAULT_BGC);
        saveConfig();
    }catch(std::string){

    }
}

