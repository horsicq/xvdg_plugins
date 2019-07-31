INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/viewer_plugin_interface.h

!contains(XCONFIG, specabstract) {
    XCONFIG += specabstract
    include(../../../_mylibs/SpecAbstract/specabstract.pri)
}

