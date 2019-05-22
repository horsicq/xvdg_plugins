INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

!contains(XCONFIG, plugin_interface) {
    XCONFIG += plugin_interface
    include(../plugin_interface.pri)
}

HEADERS += \
    $$PWD/plugin_elf.h

SOURCES += \
    $$PWD/plugin_elf.cpp

!contains(XCONFIG, elfwidget) {
    XCONFIG += elfwidget
    include(../../FormatWidgets/ELF/elfwidget.pri)
}
