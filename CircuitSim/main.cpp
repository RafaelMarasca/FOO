#include<QApplication>
#include "mainwin.h"


int main(int argc, char* argv[]){

    QApplication app(argc,argv);

    mainWin win;

    win.show();

    return app.exec();
}
