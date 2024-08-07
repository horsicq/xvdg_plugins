// Copyright (c) 2020 hors<horsicq@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#ifndef GENERICUNPACKER_H
#define GENERICUNPACKER_H

#include <QObject>
#include "unpacker_plugin_interface.h"
#include "xunpacker.h"

class GenericUnpacker : public QObject {
    Q_OBJECT

public:
    enum MESSAGE_TYPE {
        MESSAGE_TYPE_UNKNOWN = 0,
        MESSAGE_TYPE_INFO,
        MESSAGE_TYPE_WARNING,
        MESSAGE_TYPE_ERROR
    };
    explicit GenericUnpacker(QObject *parent = nullptr);
    static MESSAGE_TYPE convertXDebuggerMessageType(XDebugger::MESSAGE_TYPE messageType);
    static XvdgUnpackerPluginInterface::OPTIONS_RECORD convertXDebuggerUnpackOption(XUnpacker::UNPACK_OPTIONS_RECORD unpackOption);
    static QList<XvdgUnpackerPluginInterface::OPTIONS_RECORD> convertXDebuggerUnpackOptions(QList<XUnpacker::UNPACK_OPTIONS_RECORD> *pListUnpackOptions);
    static QList<XUnpacker::UNPACK_OPTIONS_RECORD> convertXvdgUnpackOptions(QList<XvdgUnpackerPluginInterface::OPTIONS_RECORD> *pListUnpackOptions);
};

#endif  // GENERICUNPACKER_H
