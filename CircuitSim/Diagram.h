#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "Circuit.h"

enum sts{UNSAVED,MODIFIED,OK};

class Diagram : public QObject
{
    Q_OBJECT
public:
    explicit Diagram(QObject *parent = nullptr);
    ~Diagram();

    QWidget* getView();
    enum sts getStatus();
    void setFileName(QString file);
    QString getFileName();

signals:

public slots:
   // void insert();
   // void remove();
   // void load();
   void save();
   // void query();

private:
    QGraphicsScene* scene;
    CCT::Circuit circuit;
    QGraphicsView* view;
    std::string fileName;
    enum sts status;
};

#endif // DIAGRAM_H
