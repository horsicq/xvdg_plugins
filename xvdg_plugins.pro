TEMPLATE      = subdirs

SUBDIRS       += viewers/viewer_binary
SUBDIRS       += viewers/viewer_elf
SUBDIRS       += viewers/viewer_mach
SUBDIRS       += viewers/viewer_msdos
SUBDIRS       += viewers/viewer_pe

SUBDIRS       += unpackers/unpacker_upx
contains(QT_ARCH, i386) {
    SUBDIRS       += unpackers/unpacker_pex
} 

