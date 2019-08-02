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
#ifndef UNPACKER_PLUGIN_INTERFACE_H
#define UNPACKER_PLUGIN_INTERFACE_H

#include "specabstract.h"

class XvdgUnpackerPluginInterface
{
public:
    struct INFO
    {
        QString sName;
        QString sVersion;
        QString sDescription;
        bool bIsRunTime;
    };
    virtual ~XvdgUnpackerPluginInterface() {}

    virtual INFO getInfo()=0;
    virtual bool isValid(SpecAbstract::SCAN_STRUCT *pScanStruct)=0;
    virtual bool rtUnpack(QString sFileName,QString sResultFileName)=0;
    virtual void rtStop()=0;
};

QT_BEGIN_NAMESPACE
Q_DECLARE_INTERFACE(XvdgUnpackerPluginInterface,"xvdg.unpackerplugininterface/1.0")
QT_END_NAMESPACE

#endif // UNPACKER_PLUGIN_INTERFACE_H
