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
#include "Diagram.h"

class mainWin : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainWin(QWidget *parent = nullptr);

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
    QToolBar *toolbar;

    void initializeMenu();
    void initializeToolbar();
    void initializeTabs();

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void preferences();
    void closeFile(int index);
};

#endif // MAINWIN_H
