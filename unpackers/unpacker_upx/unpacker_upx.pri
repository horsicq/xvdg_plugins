INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

!contains(XCONFIG, unpacker_plugin_interface) {
    XCONFIG += unpacker_plugin_interface
    include(../unpacker_plugin_interface.pri)
}

HEADERS += \
    $$PWD/unpacker_upx.h \
    $$PWD/upx_pe_rt_unpacker.h

SOURCES += \
    $$PWD/unpacker_upx.cpp \
    $$PWD/upx_pe_rt_unpacker.cpp

!contains(XCONFIG, xdebugger) {
    XCONFIG += xdebugger
    include(../../../../_mylibs/XDebugger/xdebugger.pri)
}
