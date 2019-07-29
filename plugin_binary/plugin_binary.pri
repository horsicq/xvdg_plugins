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

contains(QT,gui) {
    !contains(XCONFIG, binarywidget) {
        XCONFIG += binarywidget
        include(../../../_mylibs/FormatWidgets/Binary/binarywidget.pri)
    }
}

