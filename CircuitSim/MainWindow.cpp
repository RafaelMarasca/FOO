#include "MainWindow.h"
#include "Diagram.h"
#include<QMenuBar>
#include<QMenu>
#include<QAction>
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

    Diagram* D = new Diagram(this);
    D->setFileName(fileName);

    try {
        D->load();
    }  catch (std::string s) {
        qDebug("%s\n", s.c_str());
        QMessageBox::warning(this, "Warning!", "Cannot load file.");

        delete D;
        return;
    }
    QFileInfo info(fileName);

    diagrams.push_back(D);
    tabs->addTab(D,info.fileName());
}

void MainWindow::openFile(QString fileName){

    if(fileName.isNull())
         return;

    Diagram* D = new Diagram(this);
    D->setFileName(fileName);

    try {
        D->load();
    }  catch (std::string s) {
        qDebug("%s\n", s.c_str());
        QMessageBox::warning(this, "Warning!", "Cannot load file.");

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

    int index = tabs->currentIndex();
    std::list<Diagram*>::iterator it = diagrams.begin();
    advance(it,index);

    if((*it)->getStatus()==OK){
        openFile(fileName);
        return;
    }
    QFileInfo info(fileName);

    tabs->setTabText(index,'*'+info.fileName());
    qDebug()<<fileName;
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
        QMessageBox::StandardButton b = QMessageBox::question(this, "Save Changes", "Quit without saving?");
        if(b != QMessageBox::StandardButton::Yes)
            return;
    }

    diagrams.erase(it);
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
