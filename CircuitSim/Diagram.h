#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "Circuit.h"

enum sts{UNSAVED,MODIFIED,OK,ERROR};

class Diagram : public QObject
{
    Q_OBJECT
public:
    explicit Diagram(QObject *parent = nullptr);

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
    QWidget aux;
    QGraphicsScene* scene;
    CCT::Circuit circuit;
    QGraphicsView* view;
    std::string fileName;
    enum sts status;
    void setStatus(enum sts newStatus);
};

#endif // DIAGRAM_H
