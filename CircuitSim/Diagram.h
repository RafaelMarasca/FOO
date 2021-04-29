#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QWidget>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include "DiagramView.h"
#include "DiagramScene.h"
#include "Circuit.h"

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
    DiagramScene* scene;
    DiagramView* view;
    std::string fileName;
    enum sts status;

    CCT::Circuit circuit;

    void setStatus(enum sts newStatus);
};

#endif // DIAGRAM_H
