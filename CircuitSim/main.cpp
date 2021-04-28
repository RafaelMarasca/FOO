#include<QApplication>
#include "MainWin.h"
#include "Diagram.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char* argv[]){

    QApplication app(argc,argv);

    mainWin win;

    win.show();

    return app.exec();
}
