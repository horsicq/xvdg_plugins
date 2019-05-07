INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

!contains(XCONFIG, plugin_interface) {
    XCONFIG += plugin_interface
    include(../plugin_interface.pri)
}

HEADERS += \
    $$PWD/plugin_pe.h

SOURCES += \
    $$PWD/plugin_pe.cpp

!contains(XCONFIG, pewidget) {
    XCONFIG += pewidget
    include(../../FormatWidgets/PE/pewidget.pri)
}
