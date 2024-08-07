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
#ifndef VIEWER_BINARY_H
#define VIEWER_BINARY_H

#include <QObject>
#include "viewer_plugin_interface.h"
#include "binarywidget.h"

class Viewer_Binary : public QObject, XvdgViewerPluginInterface {
    Q_OBJECT

#ifndef STATIC_PLUGINS
    Q_PLUGIN_METADATA(IID "xvdg.viewerplugin.Binary")
#endif
    Q_INTERFACES(XvdgViewerPluginInterface)

public:
    explicit Viewer_Binary(QObject *parent = nullptr);
    virtual INFO getInfo();
    virtual bool isValid(SpecAbstract::SCAN_STRUCT *pScanStruct);
    virtual QWidget *getWidget(DATA *pData);

private:
    FW_DEF::OPTIONS options;
};

#endif  // VIEWER_BINARY_H
