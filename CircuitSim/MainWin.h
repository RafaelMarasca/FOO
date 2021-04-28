#ifndef MAINWIN_H
#define MAINWIN_H

#include<QMainWindow>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include <QFileDialog>
#include <QString>
#include <QToolBar>

class mainWin : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainWin(QWidget *parent = nullptr);

signals:

private:
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
    void initializeMenu();
    QString fileName;
    QToolBar *toolbar;

    void initializeToolbar();

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void preferences();
};

#endif // MAINWIN_H
