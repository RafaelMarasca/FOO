#include "MainWin.h"
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include <QFileDialog>
#include <QString>
#include <QDebug>

mainWin::mainWin(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("CircuitSim - by Carvalho && Marasca");
    setGeometry(0,0,800,600);

    initializeMenu();
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
}


void mainWin::newFile(){

}

void mainWin::openFile(){
    fileName = QFileDialog::getOpenFileName(this,"Open file",tr("*.txt"));
}

void mainWin::saveFile(){

}

void mainWin::saveFileAs(){
    fileName = QFileDialog::getSaveFileName(this,".cct");
}

void mainWin::preferences(){

}
