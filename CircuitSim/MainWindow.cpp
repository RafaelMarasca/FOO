#include "MainWindow.h"
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
#include <QFileInfo>
#include <QPixmap>
#include <QIcon>
#include "ComponentBar.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("CircuitSim - by Carvalho && Marasca");
    setGeometry(0,0,800,600);

    initializeMenu();
    initializeToolbar();
    initializeTabs();
    setCentralWidget(tabs);

}

void MainWindow::initializeMenu(){
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

    connect(saveFileAct,SIGNAL(triggered(bool)),this, SLOT(saveFile()));

    saveFileAsAct = new QAction("Save as",this);
    fileMenu->addAction(saveFileAsAct);

     connect(saveFileAsAct,SIGNAL(triggered(bool)),this, SLOT(saveFileAs()));

    prefMenu = new QMenu("Preferences",this);
    mainBar->addMenu(prefMenu);

    helpMenu = new QMenu("Help",this);
    mainBar->addMenu(helpMenu);

    tutorialAct = new QAction("Tutorial",this);
    helpMenu->addAction(tutorialAct);

    setMenuBar(mainBar);
}

void MainWindow::initializeToolbar() {
    toolbar = new ComponentBar(this);
    addToolBar(Qt::RightToolBarArea, toolbar);

    connect(toolbar,SIGNAL(selected(int)),this,SLOT(draw(int)));
}

void MainWindow::initializeTabs(){
    tabs = new QTabWidget(this);
    tabs->setTabsClosable(true);
    connect(tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(int)));
    tabs->show();
}

void MainWindow::newFile(){

    Diagram* D = new Diagram(this);
    diagrams.push_back(D);

    QString untitled = "*untitled ";
    untitled.append(QString::number(tabs->count()));

    tabs->addTab(D,untitled);

    connect(D,SIGNAL(modified(bool)),this,SLOT(setTabStatus(bool)));
}

void MainWindow::openFile(){
    QString fileName = QFileDialog::getOpenFileName(this,"Open file",tr("*.cct"));

    if(fileName.isNull())
         return;

    QFileInfo info(fileName);
    fileName = info.fileName();

    Diagram* D = new Diagram(this);
    D->setFileName(fileName);

    try {
        D->load();
    }  catch (std::string()) {
        delete D;
        return;
    }

    diagrams.push_back(D);
    tabs->addTab(D,fileName);
}

void MainWindow::openFile(QString fileName){

    if(fileName.isNull())
         return;

    Diagram* D = new Diagram(this);
    D->setFileName(fileName);

    try {
        D->load();
    }  catch (std::string()) {
        delete D;
        return;
    }

    diagrams.push_back(D);
    tabs->addTab(D,fileName);
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
}

void MainWindow::saveFileAs(){

    if(tabs->count()==0)
        return;

    QString fileName = QFileDialog::getSaveFileName(this,"*.cct");

    if(fileName.isNull())
        return;

    QFileInfo info(fileName);
    fileName = info.fileName();

    int index = tabs->currentIndex();
    std::list<Diagram*>::iterator it = diagrams.begin();
    advance(it,index);

    if((*it)->getStatus()==OK){
        openFile(fileName);
        return;
    }

    tabs->setTabText(index,fileName.prepend('*'));

    (*it)->setFileName(fileName);
    (*it)->save();
}

void MainWindow::preferences(){

}

void MainWindow::setTabStatus(bool modified){
    int index = tabs->currentIndex();
    QString fileName = tabs->tabText(index);

    if(modified){
        fileName.prepend('*');
    }else{
        fileName.remove(0,1);
    }
    tabs->setTabText(index, fileName);
}

void MainWindow::closeFile(int index){

    std::list<Diagram*>::iterator it = diagrams.begin();
    std::advance(it,index);

    if((*it)->getStatus() == UNSAVED or (*it)->getStatus() == MODIFIED){
        //dialog
    }

    diagrams.erase(it);
    tabs->removeTab(index);
}

void MainWindow::draw(int t){
    if(tabs->count() == 0)
        return;

    enum type type = static_cast<enum type>(t);

    int index = tabs->currentIndex();
    std::list<Diagram*>::iterator it = diagrams.begin();
    advance(it,index);
    qDebug()<<"certo";

    (*it)->setSelectedObject(type);
}

