TEMPLATE = app
TARGET = CircuitSim
QT = core gui widgets

SOURCES += \
    Circuit.cpp \
    Component.cpp \
    Diagram.cpp \
    DiagramScene.cpp \
    DiagramView.cpp \
    Graph.cpp \
    MainWindow.cpp \
    Numeric.cpp \
    main.cpp

HEADERS += \
    Circuit.h \
    Component.h \
    Diagram.h \
    DiagramScene.h \
    DiagramView.h \
    Graph.h \
    MainWindow.h \
    Numeric.h

RESOURCES += \
    Resources.qrc
