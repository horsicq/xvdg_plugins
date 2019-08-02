INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/unpacker_plugin_interface.h \
    $$PWD/genericunpacker.h

SOURCES += \
    $$PWD/genericunpacker.cpp

!contains(XCONFIG, specabstract) {
    XCONFIG += specabstract
    include(../../../_mylibs/SpecAbstract/specabstract.pri)
}

!contains(XCONFIG, xdebugger) {
    XCONFIG += xdebugger
    include(../../../_mylibs/XDebugger/xdebugger.pri)
}
