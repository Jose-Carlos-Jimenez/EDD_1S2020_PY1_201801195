TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
LIBS += -lncurses
QT += core

SOURCES += \
        main.cpp \

HEADERS += \
    Casilla.h \
    Ficha.h \
    ListaSimple.h \
    arbol.h \
    cola.h \
    jugador.h \
    lista.h \
    listacirculardoble.h \
    listadoblementeenlazada.h \
    matrizdispersa.h
