#ifndef DIAGRAMVIEW_H
#define DIAGRAMVIEW_H

#include <QGraphicsView>
#include<QMouseEvent>
#include<QDebug>
#include<QPushButton>

class DiagramView : public QGraphicsView
{
    Q_OBJECT
public:
    DiagramView(QGraphicsScene *scene, QWidget *parent = nullptr);

 //protected:
     //void mousePressEvent(QMouseEvent* event) override;
     //void mouseReleaseEvent(QMouseEvent* event) override;
     //void mouseMoveEvent(QMouseEvent* event) override;
     //void resizeEvent(QResizeEvent* event) override;

 public slots:
     void upScale();
     void downScale();

 private:
     QPushButton* zoomIn;
     QPushButton* zoomOut;
     void initializeButtons();
     //int x,y;
     //bool ok;

};

#endif // DIAGRAMVIEW_H
