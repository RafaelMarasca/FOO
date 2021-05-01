#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QWidget>
#include <QObject>
#include <QScrollBar>
#include <QPushButton>
#include "Circuit.h"
#include <QScrollArea>
#include <QMouseEvent>
#include <stack>
#include "GraphicComponent.h"
#include "Graph.h"

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

protected:
    void mousePressEvent(QMouseEvent* event) override;
    //void mouseMoveEvent(QMouseEvent* event) override;
    // void mouseReleasedEvent(QMouseEvent* event);

signals:
    void modified(bool checked = false);
    void loadError(bool checked = false);


public slots:
    void queryMode();
    void editMode();
    void clickedControl(int,GraphicComponent*);
   // void insert();
   // void remove();
   // void query();

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

    std::list<GraphicComponent*> drawList;
    GraphicComponent* selectedComponent;
    enum typeOrientation selectedButton;

    void freeAllocatedMemory();

    std::stack<std::pair<int,GraphicComponent*>> clickedStack;

    GRF::adjacencyMatrix connections;

    unsigned int wireCounter;
};

#endif // DIAGRAM_H
