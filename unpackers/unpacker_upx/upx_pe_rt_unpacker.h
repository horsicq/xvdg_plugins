#ifndef UPX_PE_RT_UNPACKER_H
#define UPX_PE_RT_UNPACKER_H

#include <QObject>
#include "xunpacker.h"

class UPX_PE_RT_Unpacker : public XUnpacker
{
    Q_OBJECT
public:
    explicit UPX_PE_RT_Unpacker(QObject *parent=nullptr);

protected:
    virtual void _clear();
    virtual void onEntryPoint(ENTRYPOINT_INFO *pEntryPointInfo);
    virtual void onFunctionEnter(FUNCTION_INFO *pFunctionInfo);
    virtual void onFunctionLeave(FUNCTION_INFO *pFunctionInfo);
    virtual void onBreakPoint(BREAKPOINT *pBp);
    virtual void onStep(STEP *pStep);

private:
    XWinAPI::KERNEL32_GETPROCADDRESS lastRecord;
};

#endif // UPX_PE_RT_UNPACKER_H