/********************************************************************************************
 * @file Diagram.h
 * @authors: Lucas Carvalho; Rafael Marasca Martins
 * @date: 30 04 2021
 * @brief Declaração da classe Numeric.
 * 
 * Este arquivo contém as delcarações dos métodos e membros da classe Diagram.
 * 
 * A classe Diagram fornece as facilidades para inserir objetos da classe GraphicsComponent
 * graficamente, identificar as interações do usuário com estes objetos, bem como,
 * interligar a implementação gráfica com a parte numérica.
 *  
 ********************************************************************************************/

#ifndef DIAGRAM_H
#define DIAGRAM_H

#include "Circuit.h"
#include "Graph.h"
#include "GraphicComponent.h"

#include <QWidget>
#include <QObject>
#include <QScrollBar>
#include <QPushButton>
#include <QScrollArea>
#include <QMouseEvent>
#include <stack>
#include <QMessageBox>
#include <QPropertyAnimation>

enum typeOrientation{VCC90,VCC180,RES90,RES180,NONE};
enum sts{UNSAVED,MODIFIED,OK,ERROR};
enum mode{EDIT,QUERY};

class Diagram : public QWidget
{
    Q_OBJECT
public:
    explicit Diagram(QWidget *parent = nullptr);

    void setFileName(QString file);
    QString getFileName();


    void load();
    void save();

    enum sts getStatus();

    void setSelectedButton(enum typeOrientation);

    void insert(int x, int y);
    unsigned int getComponentCounter(CMP::type t);
    unsigned int getComponentCounter();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    // void mouseReleasedEvent(QMouseEvent* event);

signals:
    void modified(bool checked = false);
    void loadError(bool checked = false);

public slots:
    void queryMode();
    void editMode();
    void rightButtonClicked(int x, int y, int cArea);
    void leftButtonClicked(int x, int y, int cArea);
    void showEditDialog();

    void edit(double newValue);
    void remove();
    void query();

private:
    QPushButton* playButton;
    QPushButton* editButton;
    std::string fileName;
    enum sts status;
    void initializeDiagram();

    CCT::Circuit circuit;

    void setStatus(enum sts newStatus);
    void paintEvent(QPaintEvent* event) override;

    enum mode mode;

    std::vector<GraphicComponent*> drawList;
    GraphicComponent* selectedComponent;
    enum typeOrientation selectedButton;

    void freeAllocatedMemory();

    std::stack<std::pair<int,GraphicComponent*>> clickedStack;

    GRF::adjacencyMatrix connections;

    unsigned int wireCounter;
    void rightButtonActions(int x, int y);
    void leftButtonActions(int x, int y);

    QMenu* editMenu;
    void clickedControl(int,int,int);
    QPoint cursorLocation;
    QPoint selectedPrev;
    std::pair<QRect,QPixmap>getPixMap(enum typeOrientation type);
    unsigned int vtxCounter;

};

#endif // DIAGRAM_H
