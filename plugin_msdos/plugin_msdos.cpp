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
#include "plugin_msdos.h"

Plugin_MSDOS::Plugin_MSDOS(QObject *parent) : QObject(parent)
{
    options= {};
    options.nImageBase=-1;
}

QWidget *Plugin_MSDOS::getViewerWidget(XvdgPluginInterface::DATA *pData)
{
    return new MSDOSWidget(pData->pDevice,&options);
}

XvdgPluginInterface::INFO Plugin_MSDOS::getInfo()
{
    INFO info= {};

    info.sName="MSDOS v1.0";
    info.bIsViewer=true;
    info.bIsReadOnly=false;

    return info;
}

bool Plugin_MSDOS::isValid(SpecAbstract::SCAN_STRUCT *pScanStruct)
{
    bool bResult=false;

    if(pScanStruct->id.filetype==SpecAbstract::RECORD_FILETYPE_MSDOS)
    {
        if((pScanStruct->name==SpecAbstract::RECORD_NAME_GENERIC)&&(pScanStruct->type==SpecAbstract::RECORD_TYPE_GENERIC))
        {
            bResult=true;
        }
    }

    return bResult;
}

bool Plugin_MSDOS::rtUnpack(QString sFileName)
{
    Q_UNUSED(sFileName)
    return false;
}
