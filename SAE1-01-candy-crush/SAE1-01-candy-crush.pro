TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        src/bombe.cpp \
        src/grille.cpp \
        src/mode-1vs1.cpp \
        src/mode-festival.cpp \
        src/mode-histoire.cpp \
        src/mode-infini.cpp \
        src/utilitaires.cpp 

HEADERS += \
    headers/bombe.h \
    headers/grille.h \
    headers/mode-1vs1.h \
    headers/mode-festival.h \
    headers/mode-histoire.h \
    headers/mode-infini.h \
    headers/utilitaires.h 
