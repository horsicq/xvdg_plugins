INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

!contains(XCONFIG, plugin_interface) {
    XCONFIG += plugin_interface
    include(../plugin_interface.pri)
}

HEADERS += \
    $$PWD/plugin_binary.h

SOURCES += \
    $$PWD/plugin_binary.cpp

!contains(XCONFIG, binarywidget) {
    XCONFIG += binarywidget
    include(../../FormatWidgets/Binary/binarywidget.pri)
}
