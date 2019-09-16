TEMPLATE      = subdirs

SUBDIRS       += viewers/viewer_binary
SUBDIRS       += viewers/viewer_elf
SUBDIRS       += viewers/viewer_mach
SUBDIRS       += viewers/viewer_msdos
SUBDIRS       += viewers/viewer_pe

SUBDIRS       += unpackers/unpacker_upx
SUBDIRS       += unpackers/unpacker_mpress
contains(QT_ARCH, i386) {
    SUBDIRS       += unpackers/unpacker_pex
    SUBDIRS       += unpackers/unpacker_aspack
    SUBDIRS       += unpackers/unpacker_ahpacker
    SUBDIRS       += unpackers/unpacker_kkrunchy
} 

