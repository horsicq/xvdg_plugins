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

contains(QT,gui) {
    !contains(XCONFIG, pewidget) {
        XCONFIG += pewidget
        include(../../../_mylibs/FormatWidgets/PE/pewidget.pri)
    }
}
