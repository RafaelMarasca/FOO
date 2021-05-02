TEMPLATE = app
TARGET = CircuitSim
QT = core gui widgets

SOURCES += \
    Circuit.cpp \
    Component.cpp \
    Diagram.cpp \
    EditDialog.cpp \
    File.cpp \
    Graph.cpp \
    GraphicComponent.cpp \
    MainWindow.cpp \
    Numeric.cpp \
    main.cpp

HEADERS += \
    Circuit.h \
    Component.h \
    Diagram.h \
    EditDialog.h \
    File.h \
    Graph.h \
    GraphicComponent.h \
    MainWindow.h \
    Numeric.h

RESOURCES += \
    Resources.qrc
