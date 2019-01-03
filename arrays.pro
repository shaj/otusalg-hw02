TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    DArray.h \
    BArray.h \
    IArray.h \
    OList.h \
    PQueue.h

DISTFILES += \
    README.md
