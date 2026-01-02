TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        src/affichage.cpp \
        src/bombe.cpp \
        src/mode-1vs1.cpp \
        src/mode-festival.cpp \
        src/mode-histoire.cpp \
        src/mode-infini.cpp

HEADERS += \
    headers/affichage.h \
    headers/bombe.h \
    headers/mode-1vs1.h \
    headers/mode-festival.h \
    headers/mode-histoire.h \
    headers/mode-infini.h
