#include "MainWin.h"
#include "Diagram.h"
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QPushButton>
#include <QTabWidget>
#include <QTabBar>
#include <QPixmap>
#include <QIcon>

mainWin::mainWin(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("CircuitSim - by Carvalho && Marasca");
    setGeometry(0,0,800,600);

    initializeMenu();
    initializeToolbar();
    initializeTabs();
    setCentralWidget(tabs);

}

void mainWin::initializeMenu(){
    mainBar = new QMenuBar(this);
    mainBar->setGeometry(0,0,300,30);

    fileMenu = new QMenu("File",this);
    mainBar->addMenu(fileMenu);

    newFileAct = new QAction("New File",this);
    fileMenu->addAction(newFileAct);

    connect(newFileAct,SIGNAL(triggered(bool)),this,SLOT(newFile()));

    openFileAct = new QAction("Open",this);
    fileMenu->addAction(openFileAct);

    connect(openFileAct,SIGNAL(triggered(bool)),this, SLOT(openFile()));

    saveFileAct = new QAction("Save",this);
    fileMenu->addAction(saveFileAct);

    saveFileAsAct = new QAction("Save as",this);
    fileMenu->addAction(saveFileAsAct);

    prefMenu = new QMenu("Preferences",this);
    mainBar->addMenu(prefMenu);

    helpMenu = new QMenu("Help",this);
    mainBar->addMenu(helpMenu);

    tutorialAct = new QAction("Tutorial",this);
    helpMenu->addAction(tutorialAct);

    setMenuBar(mainBar);
}

void mainWin::initializeToolbar() {
    toolbar = new QToolBar(this);
    resButton = new QPushButton(this);
    vccButton = new QPushButton(this);

    QPixmap vccPixmap(QDir::currentPath() + "/images/vcc.png");
    QIcon vccButtonIcon(vccPixmap.scaled(65, 65));
    vccButton->setIcon(vccButtonIcon);
    vccButton->setIconSize(QSize(65, 65));

    QPixmap resPixmap(QDir::currentPath() + "/images/resistor.png");
    QIcon resButtonIcon(resPixmap.scaled(65, 65));
    resButton->setIcon(resButtonIcon);
    resButton->setIconSize(QSize(65, 65));

    toolbar->addWidget(vccButton);
    toolbar->addWidget(resButton);

    toolbar->setMovable(false);

    addToolBar(Qt::RightToolBarArea, toolbar);
}

void mainWin::initializeTabs(){
    tabs = new QTabWidget();
    tabs->setTabsClosable(true);
    connect(tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(int)));
    tabs->show();
}

void mainWin::newFile(){

    Diagram* D = new Diagram(this);
    diagrams.push_back(D);

    QString untitled = "*untitled ";
    untitled.append(QString::number(tabs->count()));

    tabs->addTab(D->getView(),untitled);
}

void mainWin::openFile(){
    QString fileName = QFileDialog::getOpenFileName(this,"Open file",tr("*.ctt"));
    int index = tabs->currentIndex();
    std::list<Diagram*>::iterator it = diagrams.begin();
    advance(it,index);
    (*it)->setFileName(fileName);
}

void mainWin::saveFile(){
    int index = tabs->currentIndex();
    std::list<Diagram*>::iterator it = diagrams.begin();
    advance(it,index);

    if((*it)->getStatus()==UNSAVED){
        saveFileAs();
        return;
    }
}

void mainWin::saveFileAs(){
    //fileName = QFileDialog::getSaveFileName(this,".cct");
    //tabs->setTabText(index);
}

void mainWin::preferences(){

}

void mainWin::closeFile(int index){
    std::list<Diagram*>::iterator it = diagrams.begin();
    std::advance(it,index);
    diagrams.erase(it);
    tabs->removeTab(index);
}
