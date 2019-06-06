// Copyright (c) 2019 hors<horsicq@gmail.com>
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
#ifndef PLUGIN_INTERFACE_H
#define PLUGIN_INTERFACE_H

#ifdef QT_GUI_LIB
#include <QDialog>
#endif
#include "specabstract.h"

class XvdgPluginInterface
{
public:
    struct DATA
    {
        QWidget *pParent;
        QIODevice *pDevice;
    };
    struct INFO
    {
        QString sName;
        QString sVersion;
        QString sDescription;
        bool bIsViewer;
        bool bIsReadOnly;
        bool bIsUnpacker;
        bool bIsRunTime;
        bool bIsResultAsDirectory;
    };
#ifdef QT_GUI_LIB
    virtual QWidget *getViewerWidget(DATA *pData)=0;
#endif
    virtual INFO getInfo()=0;
    virtual bool isValid(SpecAbstract::SCAN_STRUCT *pScanStruct)=0;
    virtual bool rtUnpack(QString sFileName)=0; // TODO options
    // TODO Static unpack
};

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(XvdgPluginInterface,"xvdg.plugininterface/1.0")
QT_END_NAMESPACE

#endif // PLUGIN_INTERFACE_H
