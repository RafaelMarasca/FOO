#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QWidget>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
//#include "Circuit.h"
#include "DiagramView.h"
#include <QPushButton>

#define SWIDTH 6000
#define SHEIGHT 6000

enum sts{UNSAVED,MODIFIED,OK,ERROR};

class Diagram : public QWidget
{
    Q_OBJECT
public:
    explicit Diagram(QWidget *parent = nullptr);

    QWidget* getView();
    void setFileName(QString file);
    QString getFileName();
    void load();
    void save();
    enum sts getStatus();

signals:
    void modified(bool checked = false);
    void loadError(bool checked = false);


public slots:
   // void insert();
   // void remove();
   // void query();

private:
    QPushButton* zoomIn;
    QGraphicsScene* scene;
    //CCT::Circuit circuit;
    DiagramView* view;
    std::string fileName;
    enum sts status;
    void setStatus(enum sts newStatus);

    void buildSceneBackGround();

};

#endif // DIAGRAM_H
