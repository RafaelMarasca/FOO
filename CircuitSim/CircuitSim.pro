TEMPLATE = app
TARGET = CircuitSim
QT = core gui widgets

SOURCES += \
    Circuit.cpp \
    Component.cpp \
    Diagram.cpp \
    DiagramView.cpp \
    Graph.cpp \
    MainWindow.cpp \
    Numeric.cpp \
    main.cpp

HEADERS += \
    Circuit.h \
    Component.h \
    Diagram.h \
    DiagramView.h \
    Graph.h \
    MainWindow.h \
    Numeric.h

RESOURCES += \
    Resources.qrc
