INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

!contains(XCONFIG, plugin_interface) {
    XCONFIG += plugin_interface
    include(../plugin_interface.pri)
}

HEADERS += \
    $$PWD/plugin_msdos.h

SOURCES += \
    $$PWD/plugin_msdos.cpp

contains(QT,gui) {
    !contains(XCONFIG, msdoswidget) {
        XCONFIG += msdoswidget
        include(../../FormatWidgets/MSDOS/msdoswidget.pri)
    }
}

