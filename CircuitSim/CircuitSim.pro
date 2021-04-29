TEMPLATE = app
TARGET = CircuitSim
QT = core gui widgets

SOURCES += \
    Circuit.cpp \
    Component.cpp \
    Diagram.cpp \
    Graph.cpp \
    MainWin.cpp \
    Numeric.cpp \
    main.cpp

HEADERS += \
    Circuit.h \
    Component.h \
    Diagram.h \
    Graph.h \
    MainWin.h \
    Numeric.h

RESOURCES += \
    Resources.qrc
