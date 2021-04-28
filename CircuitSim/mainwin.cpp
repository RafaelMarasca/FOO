#include "mainwin.h"
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include <QGraphicsScene>
#include <QGraphicsView>

mainWin::mainWin(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("CircuitSim - by Carvalho && Marasca");
    setGeometry(0,0,800,600);

    QMenuBar *bar = new QMenuBar(this);
    bar->setGeometry(0,0,300,30);

    QMenu *fileMenu = new QMenu("File",this);
    bar->addMenu(fileMenu);

    QAction *openAction = new QAction("Open",this);
    fileMenu->addAction(openAction);

    QAction *saveAction = new QAction("Save",this);
    fileMenu->addAction(saveAction);

    QAction *saveAsAction = new QAction("Save as",this);
    fileMenu->addAction(saveAsAction);

    QMenu *prefMenu = new QMenu("Preferences",this);
    bar->addMenu(prefMenu);

    QMenu *helpMenu = new QMenu("Help",this);
    bar->addMenu(helpMenu);

    QAction *tutorialAction = new QAction("Tutorial",this);
    helpMenu->addAction(tutorialAction);
}
