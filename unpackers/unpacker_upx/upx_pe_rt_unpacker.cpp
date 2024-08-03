#include "upx_pe_rt_unpacker.h"

UPX_PE_RT_Unpacker::UPX_PE_RT_Unpacker(QObject *parent) : XUnpacker(parent)
{
}

void UPX_PE_RT_Unpacker::_clear()
{
    XUnpacker::_clear();
    data_GetProcAddress = {};
}

void UPX_PE_RT_Unpacker::onFileLoad(XBinary *pBinary)
{
    XPE *pPE = qobject_cast<XPE *>(pBinary);

    if (pPE->isTLSPresent()) {
        listTLSRelocs = pPE->getRelocsAsRVAList();
    }
}

void UPX_PE_RT_Unpacker::onTargetEntryPoint(XDebugger::ENTRYPOINT_INFO *pEntryPointInfo)
{
    Q_UNUSED(pEntryPointInfo)

    addAPIHook(pEntryPointInfo->hThread, "KERNEL32.DLL#LoadLibraryA");
}

void UPX_PE_RT_Unpacker::onFunctionEnter(XDebugger::FUNCTION_INFO *pFunctionInfo)
{
    // TODO 32/64
    if (pFunctionInfo->sName == "KERNEL32.DLL#LoadLibraryA") {
        int nDelta = 0;
#ifndef Q_OS_WIN64
        //    89 03                   mov    DWORD PTR [ebx],eax
        //    83 c3 04                add    ebx,0x4
        qint64 nImportAddress = findSignature(pFunctionInfo->nRetAddress, 0x1000, "890383C304");
#else
        //    48 89 03                mov    QWORD PTR [rbx],rax
        //    48 83 c3 08             add    rbx,0x8
        qint64 nImportAddress = findSignature(pFunctionInfo->nRetAddress, 0x1000, "4889034883C308");
#endif
        if (nImportAddress != -1) {
            addAPIHook(pFunctionInfo->hThread, "KERNEL32.DLL#GetProcAddress");
            setBP(pFunctionInfo->hThread, nImportAddress, BP_TYPE_CC, BP_INFO_UNKNOWN, -1, "IMPORT");
        }
#ifndef Q_OS_WIN64
        //    86 c4                   xchg   ah,al
        //    01 f0                   add    eax,esi
        //    89 03                   mov    DWORD PTR [ebx],eax
        qint64 nRelocsAddress = findSignature(pFunctionInfo->nRetAddress, 0x1000, "86C401F08903");
        nDelta = 4;
#else
        //    48 0f c8                bswap  rax
        //    48 01 f0                add    rax,rsi
        //    48 89 03                mov    QWORD PTR [rbx],rax
        qint64 nRelocsAddress = findSignature(pFunctionInfo->nRetAddress, 0x1000, "480FC84801F0488903");
        nDelta = 6;
#endif
        if (nRelocsAddress != -1) {
            setBP(pFunctionInfo->hThread, nRelocsAddress + nDelta, BP_TYPE_CC, BP_INFO_UNKNOWN, -1, "RELOCS");
        }
#ifndef Q_OS_WIN64
        //    83 ec 80                sub    esp,0xffffff80
        //    e9 .. .. .. ..          jmp    ........
        qint64 nOEPAddress = findSignature(pFunctionInfo->nRetAddress, 0x1000, "83EC80E9");
        nDelta = 3;
#else
        //    48 83 ec 80             sub    rsp,0xffffffffffffff80
        //    e9 .. .. .. ..          jmp    .. .. .. ..
        qint64 nOEPAddress = findSignature(pFunctionInfo->nRetAddress, 0x1000, "4883EC80E9");
        nDelta = 4;

        if (nOEPAddress == -1) {
            // DLL
            //  48 83 ec 80             sub    rsp,0xffffffffffffff80
            //  4c 8b 44 24 18          mov    r8,QWORD PTR [rsp+0x18]
            //  48 8b 54 24 10          mov    rdx,QWORD PTR [rsp+0x10]
            //  48 8b 4c 24 08          mov    rcx,QWORD PTR [rsp+0x8]
            //  e9 .. .. .. ..          jmp    .. .. .. ..
            nOEPAddress = findSignature(pFunctionInfo->nRetAddress, 0x1000, "4883EC804C8B442418488B542410488B4C2408E9");
            nDelta = 19;
        }
#endif
        if (nOEPAddress != -1) {
            setBP(pFunctionInfo->hThread, nOEPAddress + nDelta, BP_TYPE_CC, BP_INFO_UNKNOWN, 1, "JMP_TO_OEP");
        }

        if (nImportAddress == -1) {
            _messageString(MESSAGE_TYPE_ERROR, tr("Cannot find import signature"));
            stop();
        }
        if (nOEPAddress == -1) {
            _messageString(MESSAGE_TYPE_ERROR, tr("Cannot find OEP signature"));
            stop();
        }
        if (nRelocsAddress == -1) {
            _messageString(MESSAGE_TYPE_WARNING, tr("Cannot find relocs signature"));
        }

        if (getFileInfo()->bIsTLSPresent) {
            if (listTLSRelocs.count()) {
                int nCount = listTLSRelocs.count();

                for (int i = 0; i < nCount; i++) {
                    RELOC_BUILD_RECORD rbr = {};
                    rbr.nPatchAddress = listTLSRelocs.at(i) + getTargetInfo()->nImageBase;
                    rbr.nValue = read_uint32(rbr.nPatchAddress);

                    addRelocBuildRecord(rbr);
                }
            }
        }
    } else if (pFunctionInfo->sName == "KERNEL32.DLL#GetProcAddress") {
        XWinAPI().handle_Kernel32_GetProcAddress(this, pFunctionInfo, XWinAPI::HANDLE_TYPE_ENTER, &data_GetProcAddress);
    }
}

void UPX_PE_RT_Unpacker::onFunctionLeave(XDebugger::FUNCTION_INFO *pFunctionInfo)
{
    if (pFunctionInfo->sName == "KERNEL32.DLL#GetProcAddress") {
        XWinAPI().handle_Kernel32_GetProcAddress(this, pFunctionInfo, XWinAPI::HANDLE_TYPE_LEAVE, &data_GetProcAddress);
    } else if (pFunctionInfo->sName == "KERNEL32.DLL#LoadLibraryA") {
        removeAPIHook("KERNEL32.DLL#LoadLibraryA");
    }
}

void UPX_PE_RT_Unpacker::onBreakPoint(BREAKPOINT_INFO *pBreakPointInfo)
{
    if (pBreakPointInfo->vInfo.toString() == "IMPORT") {
#ifndef Q_OS_WIN64
        quint64 nValue = getRegister(pBreakPointInfo->hThread, REG_NAME_EAX);
        quint64 nPatchAddress = getRegister(pBreakPointInfo->hThread, REG_NAME_EBX);
#else
        quint64 nValue = getRegister(pBreakPointInfo->hThread, REG_NAME_RAX);
        quint64 nPatchAddress = getRegister(pBreakPointInfo->hThread, REG_NAME_RBX);
#endif
        if (data_GetProcAddress.nResult == nValue) {
            IMPORT_BUILD_RECORD ibr = {};
            ibr.nPatchAddress = nPatchAddress;
            ibr.bIsOrdinal = data_GetProcAddress.bIsOrdinal;
            ibr.nOrdinal = data_GetProcAddress.nOrdinal;
            ibr.sFunction = data_GetProcAddress.sFunction;
            ibr.sLibrary = data_GetProcAddress.sLibrary;
            ibr.nValue = data_GetProcAddress.nResult;

            addImportBuildRecord(ibr);
        }
    } else if (pBreakPointInfo->vInfo.toString() == "RELOCS") {
#ifndef Q_OS_WIN64
        quint64 nValue = getRegister(pBreakPointInfo->hThread, REG_NAME_EAX);
        quint64 nPatchAddress = getRegister(pBreakPointInfo->hThread, REG_NAME_EBX);
#else
        quint64 nValue = getRegister(pBreakPointInfo->hThread, REG_NAME_RAX);
        quint64 nPatchAddress = getRegister(pBreakPointInfo->hThread, REG_NAME_RBX);
#endif
        RELOC_BUILD_RECORD rbr = {};
        rbr.nPatchAddress = nPatchAddress;
        rbr.nValue = nValue;

        addRelocBuildRecord(rbr);
    } else if (pBreakPointInfo->vInfo.toString() == "JMP_TO_OEP") {
        removeAPIHook("KERNEL32.DLL#GetProcAddress");

        stepInto(pBreakPointInfo->hThread, "STEP_TO_OEP");
    }
}

void UPX_PE_RT_Unpacker::onStep(STEP_INFO *pStepInfo)
{
    if (pStepInfo->vInfo.toString() == "STEP_TO_OEP") {
        DUMP_OPTIONS dumpOptions = {};
        dumpOptions.nAddressOfEntryPoint = (pStepInfo->nAddress) - (getTargetInfo()->nImageBase);

        dumpOptions.bFixChecksum = getUnpackOptionValue(UNPACK_OPTIONS_ID_FIXCHECKSUM).toBool();
        dumpOptions.bPatchNWError6002 = getUnpackOptionValue(UNPACK_OPTIONS_ID_PATCHNW).toBool();

        if (dumpToFile(getResultFileName(), &dumpOptions)) {
            stop();
        }
    }
}
