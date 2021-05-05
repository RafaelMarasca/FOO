/********************************************************************************************
 * @file MainWindow.h
 * @authors: Lucas Carvalho; Rafael Marasca Martins
 * @date: 28 04 2021
 * @brief Declaração da classe MainWindow.
 * 
 * Este arquivo contém as delcarações dos métodos e membros da classe MainWindow, que 
 * representa a janela principal do programa. 
 * 
 * A classe MainWindow controla o fluxo de execução com base nas interações do usuário.
 *  
 ********************************************************************************************/

#ifndef MAINWIN_H
#define MAINWIN_H

#include "Diagram.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QString>
#include <QToolBar>
#include <list>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    explicit MainWindow(QWidget *parent = nullptr);
    MainWindow(const MainWindow&);
    MainWindow operator=(MainWindow&);
    static MainWindow* instance;

    std::list<Diagram*> diagrams;
    QTabWidget* tabs;
    QMenuBar *mainBar;
    QMenu *fileMenu;
    QMenu *prefMenu;
    QMenu *helpMenu;
    QAction *openFileAct;
    QAction *saveFileAct;
    QAction *saveFileAsAct;
    QAction *newFileAct;
    QAction *tutorialAct;
    QToolBar* toolbar;
    QStatusBar* statusBar;
    QWidget* initialTab;

    QAction* setBGColorAct;

    QAction* setLinesColorAct;
    QAction* setComponentColorAct;

    QAction* setSelectedColorAct;
    QAction* resetConfigAct;

    void initializeMenu();
    void initializeToolbar();
    void initializeTabs();
    void openFile(QString fileName);
    void initializeStatusBar();   

public:
    static MainWindow* getMainWindow();
    void loadConfig();
    void saveConfig();

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void setBGColor();
    void setLinesColor();
    void setComponentColor();
    void setSelectedColor();
    void resetConfig();
    void setTabStatus(bool modified);
    void closeFile(int index);
    void drawRes90();
    void drawRes180();
    void drawVcc90();
    void drawVcc180();
};

#endif // MAINWIN_H
