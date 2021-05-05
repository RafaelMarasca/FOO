/********************************************************************************************
 * @file main.cpp
 * @authors: Lucas Carvalho; Rafael Marasca Martins
 * @date: 28 04 2021
 * @brief Implementação do arquivo main.cpp.
 * 
 * \mainpage Descrição
 * Este projeto consiste em um simulador de circuitos compostos por resistores e 
 * fontes de tensão contínua com interface gráfica.
 *  
 ********************************************************************************************/

#include "MainWindow.h"

#include<QApplication>


/*************************************************************************
 * Implementação da função main.
 *
 * Controla o fluxo inicial e final do programa.
 *
 *************************************************************************/
int main(int argc, char* argv[]){

    QApplication app(argc,argv);

    //Obtenção da MainWindow
    MainWindow* win = MainWindow::getMainWindow();

    //Altera o ícone do programa.
    win->setWindowIcon(QIcon(":/icons/resourceFile/iconFile/appIcon.png"));

    //Mostra a janela principal do programa
    win->show();


    return app.exec();
}
