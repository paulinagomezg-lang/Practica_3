TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        ENCRIPTACION.cpp \
        LZ78.cpp \
        RLE.cpp \
        main.cpp

HEADERS += \
    ENCRIPTACION.h \
    LZ78.h \
    RLE.h
