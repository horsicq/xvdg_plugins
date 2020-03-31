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
#include "unpacker_upx.h"

Unpacker_UPX::Unpacker_UPX(QObject *parent) : QObject(parent)
{
    pUnpacker=0;
}

XvdgUnpackerPluginInterface::INFO Unpacker_UPX::getInfo()
{
    INFO info= {};

    info.sName="upx";
    info.sVersion="1.00";
    info.sDescription="UPX";
    info.bIsRunTime=true;

    return info;
}

bool Unpacker_UPX::isValid(SpecAbstract::SCAN_STRUCT *pScanStruct)
{
    bool bResult=false;

    // TODO os defs
    // TODO copy to tmp path and run if it is in overlay
    if(pScanStruct->parentId.filepart==SpecAbstract::RECORD_FILEPART_HEADER)
    {
        if((pScanStruct->id.filetype==SpecAbstract::RECORD_FILETYPE_PE32)||(pScanStruct->id.filetype==SpecAbstract::RECORD_FILETYPE_PE64))
        {
            if((pScanStruct->name==SpecAbstract::RECORD_NAME_UPX)&&(pScanStruct->type==SpecAbstract::RECORD_TYPE_PACKER))
            {
                bResult=true;
            }
        }
    }

    return bResult;
}

QList<XvdgUnpackerPluginInterface::OPTIONS_RECORD> Unpacker_UPX::getDefaultOptions()
{
    QList<XUnpacker::UNPACK_OPTIONS_RECORD> listOptions=UPX_PE_RT_Unpacker().getDefaultUnpackOptions();

    return GenericUnpacker::convertXDebuggerUnpackOptions(&listOptions);
}

bool Unpacker_UPX::rtUnpack(QString sFileName, QString sResultFileName,QList<OPTIONS_RECORD> *pListOptions)
{
    if(pUnpacker)
    {
        delete pUnpacker;

        pUnpacker=0;
    }

    pUnpacker=new UPX_PE_RT_Unpacker;

    connect(pUnpacker,SIGNAL(messageString(quint32,QString)),this,SLOT(messageSlot(quint32,QString)));

    QList<XUnpacker::UNPACK_OPTIONS_RECORD> listUnpackOptions=GenericUnpacker::convertXvdgUnpackOptions(pListOptions);

    return pUnpacker->unpack(sFileName,sResultFileName,&listUnpackOptions);
}

void Unpacker_UPX::rtStop()
{
    if(pUnpacker)
    {
        pUnpacker->stop();
    }
}

bool Unpacker_UPX::stringToOption(QString sString, XvdgUnpackerPluginInterface::OPTIONS_RECORD *pRecord)
{
    return false;
}

void Unpacker_UPX::messageSlot(quint32 nType, QString sText)
{
    emit messageString(GenericUnpacker::convertXDebuggerMessageType((XDebugger::MESSAGE_TYPE)nType),sText);
}
