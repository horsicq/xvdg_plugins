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
#include "genericunpacker.h"

GenericUnpacker::GenericUnpacker(QObject *parent) : QObject(parent)
{

}

GenericUnpacker::MESSAGE_TYPE GenericUnpacker::convertXDebuggerMessageType(XDebugger::MESSAGE_TYPE messageType)
{
    GenericUnpacker::MESSAGE_TYPE result=GenericUnpacker::MESSAGE_TYPE_UNKNOWN;

    switch(messageType)
    {
        case XDebugger::MESSAGE_TYPE_UNKNOWN:   result=GenericUnpacker::MESSAGE_TYPE_UNKNOWN;           break;
        case XDebugger::MESSAGE_TYPE_ERROR:     result=GenericUnpacker::MESSAGE_TYPE_ERROR;             break;
        case XDebugger::MESSAGE_TYPE_INFO:      result=GenericUnpacker::MESSAGE_TYPE_INFO;              break;
        case XDebugger::MESSAGE_TYPE_WARNING:   result=GenericUnpacker::MESSAGE_TYPE_WARNING;           break;
    }

    return result;
}

XvdgUnpackerPluginInterface::OPTIONS_RECORD GenericUnpacker::convertXDebuggerUnpackOption(XUnpacker::UNPACK_OPTIONS_RECORD unpackOption)
{
    XvdgUnpackerPluginInterface::OPTIONS_RECORD result={};

    result.nID=unpackOption.nID;
    result.sName=unpackOption.sName;
    result.sDescription=unpackOption.sDescription;
    result.var=unpackOption.var;

    if      (unpackOption.varType==XUnpacker::UNPACK_OPTIONS_VAR_TYPE_UNKNOWN)     result.varType=XvdgUnpackerPluginInterface::OPTIONS_VAR_TYPE_UNKNOWN;
    else if (unpackOption.varType==XUnpacker::UNPACK_OPTIONS_VAR_TYPE_BOOL)        result.varType=XvdgUnpackerPluginInterface::OPTIONS_VAR_TYPE_BOOL;

    return result;
}

QList<XvdgUnpackerPluginInterface::OPTIONS_RECORD> GenericUnpacker::convertXDebuggerUnpackOptions(QList<XUnpacker::UNPACK_OPTIONS_RECORD> *pListUnpackOptions)
{
    QList<XvdgUnpackerPluginInterface::OPTIONS_RECORD> listResult;

    int nCount=pListUnpackOptions->count();

    for(int i=0;i<nCount;i++)
    {
        listResult.append(convertXDebuggerUnpackOption(pListUnpackOptions->at(i)));
    }

    return listResult;
}

QList<XUnpacker::UNPACK_OPTIONS_RECORD> GenericUnpacker::convertXvdgUnpackOptions(QList<XvdgUnpackerPluginInterface::OPTIONS_RECORD> *pListUnpackOptions)
{
    QList<XUnpacker::UNPACK_OPTIONS_RECORD> listResult;

    int nCount=pListUnpackOptions->count();

    for(int i=0;i<nCount;i++)
    {
        XUnpacker::UNPACK_OPTIONS_RECORD record={};

        record.nID=pListUnpackOptions->at(i).nID;
        record.sName=pListUnpackOptions->at(i).sName;
        record.sDescription=pListUnpackOptions->at(i).sDescription;
        record.var=pListUnpackOptions->at(i).var;

        if      (pListUnpackOptions->at(i).varType==XvdgUnpackerPluginInterface::OPTIONS_VAR_TYPE_UNKNOWN)      record.varType=XUnpacker::UNPACK_OPTIONS_VAR_TYPE_UNKNOWN;
        else if (pListUnpackOptions->at(i).varType==XvdgUnpackerPluginInterface::OPTIONS_VAR_TYPE_BOOL)         record.varType=XUnpacker::UNPACK_OPTIONS_VAR_TYPE_BOOL;

        listResult.append(record);
    }

    return listResult;
}
