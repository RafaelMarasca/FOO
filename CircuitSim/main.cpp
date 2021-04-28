#include<QApplication>
#include "MainWin.h"
#include <QDebug>

int main(int argc, char* argv[]){

    QApplication app(argc,argv);

    mainWin win;

    win.show();

    return app.exec();
}
