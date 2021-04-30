#include "DiagramView.h"
#include<QScrollBar>
#include<QVBoxLayout>
#include<QGraphicsView>
#include<QMouseEvent>
#include<QDebug>
#include<QPushButton>

DiagramView::DiagramView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene,parent){
    setDragMode(ScrollHandDrag);
    initializeButtons();
}

void DiagramView::initializeButtons(){
    zoomIn = new QPushButton(this);
    zoomIn->setFixedSize(51,51);

    QPixmap inPixmap(":/icons/resourceFile/iconFile/plusIcon.png");
    QIcon zoomInIcon(inPixmap.scaled(51, 51));

    zoomIn->setIcon(zoomInIcon);
    zoomIn->setIconSize(QSize(51, 51));

    zoomOut = new QPushButton(this);
    zoomOut->setFixedSize(51,51);

    QPixmap outPixmap(":/icons/resourceFile/iconFile/minusIcon.png");
    QIcon zoomOutIcon(outPixmap.scaled(51, 51));

    zoomOut->setIcon(zoomOutIcon);
    zoomOut->setIconSize(QSize(51, 51));


    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setAlignment(Qt::AlignBottom|Qt::AlignRight);
    vbox->addWidget(zoomIn);
    vbox->addWidget(zoomOut);
    vbox->setContentsMargins(0,0,51,51);
    setLayout(vbox);

    connect(zoomIn,SIGNAL(clicked(bool)), this, SLOT(upScale()));
    connect(zoomOut,SIGNAL(clicked(bool)), this, SLOT(downScale()));
}

void DiagramView::upScale(){
    this->scale(1.25,1.25);
}

void DiagramView::downScale(){
    qDebug()<<"zoom";
    this->scale(0.75,0.75);
}

/*void DiagramView::resizeEvent(QResizeEvent* event){

    updateButtonsPosition();
}

updateButtonsPosition(){

}*/

/*void DiagramView::mousePressEvent(QMouseEvent* event){

    if(event->button() == Qt::LeftButton){
        qDebug()<<"vc clicou, parabéns";
    }

    setDragMode(QGraphicsView::ScrollHandDrag);
    x = event->x();
    y = event->y();
    ok = true;
}

void DiagramView::mouseReleaseEvent(QMouseEvent* event){

    if(event->button() == Qt::LeftButton){
        qDebug()<<"putzgrila";
    }
    ok = false;

    //scrollContentsBy(x-tempx,y-tempy);
}

void DiagramView::mouseMoveEvent(QMouseEvent* event){

    qDebug()<<"movendoo";
    if(ok){
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() -(event->x() -x));
        verticalScrollBar()->setValue(verticalScrollBar()->value()- (event->y() -y));
        x = event->x();
        y = event->y();
        qDebug()<<x<<" "<<y;
        event->accept();
        return;
    }

  event->ignore();
}*/
