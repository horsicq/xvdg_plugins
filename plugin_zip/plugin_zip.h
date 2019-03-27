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
#ifndef PLUGIN_ZIP_H
#define PLUGIN_ZIP_H

#include <QObject>
#include "plugin_interface.h"

class Plugin_Zip : public QObject, PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "ntinfo.XVedogon.Plugin_Zip")
    Q_INTERFACES(PluginInterface)
public:
    explicit Plugin_Zip(QObject *parent = nullptr);
    virtual bool init(DATA *pData);
    virtual INFO getInfo();
    virtual bool isValid(SpecAbstract::SCAN_RESULT *pScanResult);

signals:

public slots:
};

#endif // PLUGIN_ZIP_H
