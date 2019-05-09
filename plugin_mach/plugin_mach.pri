INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

!contains(XCONFIG, plugin_interface) {
    XCONFIG += plugin_interface
    include(../plugin_interface.pri)
}

HEADERS += \
    $$PWD/plugin_mach.h

SOURCES += \
    $$PWD/plugin_mach.cpp

!contains(XCONFIG, machwidget) {
    XCONFIG += machwidget
    include(../../FormatWidgets/MACH/machwidget.pri)
}
