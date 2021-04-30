#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QString>
#include <QToolBar>
#include <list>
#include <QPushButton>
#include "Diagram.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

private:
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
    QAction *prefAct;
    QAction *tutorialAct;
    QToolBar* toolbar;

    void initializeMenu();
    void initializeToolbar();
    void initializeTabs();
    void openFile(QString fileName);

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void preferences();
    void setTabStatus(bool modified);
    void closeFile(int index);
    void drawRes90();
    void drawRes180();
    void drawVcc90();
    void drawVcc180();
};

#endif // MAINWIN_H
