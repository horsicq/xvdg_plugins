#include "upx_pe_rt_unpacker.h"

UPX_PE_RT_Unpacker::UPX_PE_RT_Unpacker(QObject *parent) : XUnpacker(parent)
{

}

void UPX_PE_RT_Unpacker::_clear()
{
    XUnpacker::_clear();
    lastRecord={};
}

void UPX_PE_RT_Unpacker::onFileLoad(XPE *pPE)
{
    if(pPE->isTLSPresent())
    {
        listTLSRelocs=pPE->getRelocsAsRVAList();
    }
}

void UPX_PE_RT_Unpacker::onTargetEntryPoint(XDebugger::ENTRYPOINT_INFO *pEntryPointInfo)
{
    Q_UNUSED(pEntryPointInfo)

    addAPIHook("KERNEL32.DLL#LoadLibraryA");
}

void UPX_PE_RT_Unpacker::onFunctionEnter(XDebugger::FUNCTION_INFO *pFunctionInfo)
{
    // TODO 32/64
    if(pFunctionInfo->sName=="KERNEL32.DLL#LoadLibraryA")
    {
        //    89 03                   mov    DWORD PTR [ebx],eax
        //    83 c3 04                add    ebx,0x4
        qint64 nImportAddress=findSignature(pFunctionInfo->nRetAddress,0x1000,"890383C304");
        if(nImportAddress!=-1)
        {
            addAPIHook("KERNEL32.DLL#GetProcAddress");
            setBP(nImportAddress,BP_TYPE_CC,BP_INFO_UNKNOWN,-1,"IMPORT");
        }
        //    86 c4                   xchg   ah,al
        //    01 f0                   add    eax,esi
        //    89 03                   mov    DWORD PTR [ebx],eax
        qint64 nRelocsAddress=findSignature(pFunctionInfo->nRetAddress,0x1000,"86C401F08903");
        if(nRelocsAddress!=-1)
        {
            setBP(nRelocsAddress+4,BP_TYPE_CC,BP_INFO_UNKNOWN,-1,"RELOCS");
        }
        //    83 ec 80                sub    esp,0xffffff80
        //    e9 .. .. .. ..          jmp    ........
        qint64 nOEPAddress=findSignature(pFunctionInfo->nRetAddress,0x1000,"83EC80E9");
        if(nOEPAddress!=-1)
        {
            setBP(nOEPAddress+3,BP_TYPE_CC,BP_INFO_UNKNOWN,1,"JMP_TO_OEP");
        }

        if(nImportAddress==-1)
        {
            _messageString(MESSAGE_TYPE_ERROR,tr("Cannot find import signature"));
            stop();
        }
        if(nOEPAddress==-1)
        {
            _messageString(MESSAGE_TYPE_ERROR,tr("Cannop find OEP signature"));
            stop();
        }
        if(nRelocsAddress==-1)
        {
            _messageString(MESSAGE_TYPE_WARNING,tr("Cannop find relocs signature"));
        }

        if(getFileInfo()->bIsTLSPresent)
        {
            if(listTLSRelocs.count())
            {
                int nCount=listTLSRelocs.count();

                for(int i=0;i<nCount;i++)
                {
                    RELOC_BUILD_RECORD rbr={};
                    rbr.nPatchAddress=listTLSRelocs.at(i)+getTargetInfo()->nImageBase;
                    rbr.nValue=read_uint32(rbr.nPatchAddress);

                    addRelocBuildRecord(rbr);

                    QString sDebugString=QString("TLS Reloc [%1] <- %2").arg(rbr.nPatchAddress,0,16).arg(rbr.nValue,0,16);
                    _messageString(MESSAGE_TYPE_INFO,sDebugString);
                }
            }
        }
    }
}

void UPX_PE_RT_Unpacker::onFunctionLeave(XDebugger::FUNCTION_INFO *pFunctionInfo)
{
    if(pFunctionInfo->sName=="KERNEL32.DLL#GetProcAddress")
    {
        lastRecord=XWinAPI().handle_Kernel32_GetProcAddress(this,pFunctionInfo);
    }
    else if(pFunctionInfo->sName=="KERNEL32.DLL#LoadLibraryA")
    {
        removeAPIHook("KERNEL32.DLL#LoadLibraryA");
    }
}

void UPX_PE_RT_Unpacker::onBreakPoint(XDebugger::BREAKPOINT *pBp)
{
    if(pBp->vInfo.toString()=="IMPORT")
    {
        quint64 nEAX=getRegister(pBp->hThread,REG_NAME_EAX);
        quint64 nEBX=getRegister(pBp->hThread,REG_NAME_EBX);

        if(lastRecord.nResult==nEAX)
        {
            IMPORT_BUILD_RECORD ibr={};
            ibr.nPatchAddress=nEBX;
            ibr.bIsOrdinal=lastRecord.bIsOrdinal;
            ibr.nOrdinal=lastRecord.nOrdinal;
            ibr.sFunction=lastRecord.sFunction;
            ibr.sLibrary=lastRecord.sLibrary;

            addImportBuildRecord(ibr);

            QString sDebugString=QString("Import [%1] <- %2 : %3 : %4").arg(nEBX,0,16).arg(nEAX,0,16).arg(ibr.sLibrary).arg(ibr.sFunction);
            _messageString(MESSAGE_TYPE_INFO,sDebugString);
        }
    }
    else if(pBp->vInfo.toString()=="RELOCS")
    {
        quint64 nEAX=getRegister(pBp->hThread,REG_NAME_EAX);
        quint64 nEBX=getRegister(pBp->hThread,REG_NAME_EBX);

        RELOC_BUILD_RECORD rbr={};
        rbr.nPatchAddress=nEBX;
        rbr.nValue=nEAX;

        addRelocBuildRecord(rbr);

        QString sDebugString=QString("Reloc [%1] <- %2").arg(rbr.nPatchAddress,0,16).arg(rbr.nValue,0,16);
        _messageString(MESSAGE_TYPE_INFO,sDebugString);
    }
    else if(pBp->vInfo.toString()=="JMP_TO_OEP")
    {
        stepInto(pBp->hThread,"OEP");
    }
}

void UPX_PE_RT_Unpacker::onStep(XDebugger::STEP *pStep)
{
    if(pStep->vInfo.toString()=="OEP")
    {
        DUMP_OPTIONS dumpOptions={};
        dumpOptions.nAddressOfEntryPoint=(pStep->nAddress)-(getTargetInfo()->nImageBase);

        if(dumpToFile(getResultFileName(),&dumpOptions))
        {
            stop();
        }
    }
}
