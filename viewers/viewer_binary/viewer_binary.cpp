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
#include "viewer_binary.h"

Viewer_Binary::Viewer_Binary(QObject *parent) : QObject(parent)
{
    options= {};
    options.nImageBase=-1;
}
QWidget *Viewer_Binary::getWidget(XvdgViewerPluginInterface::DATA *pData)
{
    return new BinaryWidget(pData->pDevice,&options,pData->pParent);
}
XvdgViewerPluginInterface::INFO Viewer_Binary::getInfo()
{
    INFO info= {};

    info.sName="binary";
    info.sVersion="1.00";
    info.sDescription="Binary";
    info.bIsReadOnly=false;

    return info;
}

bool Viewer_Binary::isValid(SpecAbstract::SCAN_STRUCT *pScanStruct)
{
    bool bResult=false;

    if((pScanStruct->id.filetype==SpecAbstract::RECORD_FILETYPE_BINARY)&&(!pScanStruct->id.bVirtual))
    {
        if((pScanStruct->name==SpecAbstract::RECORD_NAME_GENERIC)&&(pScanStruct->type==SpecAbstract::RECORD_TYPE_GENERIC))
        {
            bResult=true;
        }
    }

    return bResult;
}
