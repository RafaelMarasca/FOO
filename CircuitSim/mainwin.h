#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>

class mainWin : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainWin(QWidget *parent = nullptr);

signals:

public slots:
    void openFile();
    void saveFile();
    void saveFileAs();
    void preferences();
};

#endif // MAINWIN_H
