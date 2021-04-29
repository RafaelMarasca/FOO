#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QGraphicsScene>
#include <QObject>

#define SWIDTH 6000
#define SHEIGHT 6000

class DiagramScene : public QGraphicsScene
{
public:
    DiagramScene(QObject *parent = nullptr);

private:
    void buildBackground();
};

#endif // DIAGRAMSCENE_H
