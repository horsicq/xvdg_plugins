INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/plugin_interface.h

!contains(XCONFIG, specabstract) {
    XCONFIG += specabstract
    include(../SpecAbstract/specabstract.pri)
}

