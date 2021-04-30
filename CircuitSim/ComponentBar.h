#ifndef COMPONENTBAR_H
#define COMPONENTBAR_H

#include <QToolBar>
#include <QSignalMapper>
#include <GraphicComponent.h>

class ComponentBar : public QToolBar
{
    Q_OBJECT
public:
    ComponentBar(QWidget* parent);

signals:
    void selected(int id);

private:
    QSignalMapper *mapper;
    void initializeBar();
};

#endif // COMPONENTBAR_H
