#include "ComponentBar.h"
#include <QPushButton>

ComponentBar::ComponentBar(QWidget* parent):QToolBar(parent)
{
    initializeBar();
}

void ComponentBar::initializeBar(){

    mapper = new QSignalMapper(this);

    QPushButton* vcc90Button = new QPushButton(this);
    connect(vcc90Button,SIGNAL(clicked(bool)), mapper,SLOT(map()));
    mapper->setMapping(vcc90Button, 0);
    QPixmap vcc90Pixmap(":/icons/resourceFile/iconFile/vcc90.png");
    QIcon vcc90ButtonIcon(vcc90Pixmap.scaled(65, 65));
    vcc90Button->setIcon(vcc90ButtonIcon);
    vcc90Button->setIconSize(QSize(65, 65));
    this->addWidget(vcc90Button);


    QPushButton* vcc180Button = new QPushButton(this);
    connect(vcc180Button,SIGNAL(clicked(bool)), mapper,SLOT(map()));
    mapper->setMapping(vcc180Button, 1);
    QPixmap vcc180Pixmap(":/icons/resourceFile/iconFile/vcc180.png");
    QIcon vcc180ButtonIcon(vcc180Pixmap.scaled(65, 65));
    vcc180Button->setIcon(vcc180ButtonIcon);
    vcc180Button->setIconSize(QSize(65, 65));
    this->addWidget(vcc180Button);


    QPushButton* res90Button = new QPushButton(this);
    connect(res90Button,SIGNAL(clicked(bool)),mapper,SLOT(map()));
    mapper->setMapping(res90Button, 2);
    QPixmap res90Pixmap(":/icons/resourceFile/iconFile/resistor90.png");
    QIcon res90ButtonIcon(res90Pixmap.scaled(65, 65));
    res90Button->setIcon(res90ButtonIcon);
    res90Button->setIconSize(QSize(65, 65));
    this->addWidget(res90Button);

    QPushButton* res180Button = new QPushButton(this);
    connect(res180Button,SIGNAL(clicked(bool)), mapper,SLOT(map()));
    mapper->setMapping(res180Button, 3);
    QPixmap res180Pixmap(":/icons/resourceFile/iconFile/resistor180.png");
    QIcon res180ButtonIcon(res180Pixmap.scaled(65, 65));
    res180Button->setIcon(res180ButtonIcon);
    res180Button->setIconSize(QSize(65, 65));
    this->addWidget(res180Button);

    connect(mapper, SIGNAL(mappedInt(int)),this, SIGNAL(selected(int)));

    this->setMovable(false);
}
