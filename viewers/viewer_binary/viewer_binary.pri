INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

!contains(XCONFIG, viewer_plugin_interface) {
    XCONFIG += viewer_plugin_interface
    include(../viewer_plugin_interface.pri)
}

HEADERS += \
    $$PWD/viewer_binary.h

SOURCES += \
    $$PWD/viewer_binary.cpp

contains(QT,gui) {
    !contains(XCONFIG, binarywidget) {
        XCONFIG += binarywidget
        include(../../../../_mylibs/FormatWidgets/Binary/binarywidget.pri)
    }
}

