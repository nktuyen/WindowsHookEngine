#pragma once

#include "HookClient.h"
class CJournalRecordHookEngine : public CHookClient
{
private:
    static CJournalRecordHookEngine* s_pInstance;
    CJournalRecordHookEngine(CWnd* pOwnerWnd = nullptr, UINT nCommMsg = 0);
public:
    virtual ~CJournalRecordHookEngine();
    static CJournalRecordHookEngine* createInstance(CWnd* pWnd, UINT nMsg) {
        if (nullptr == s_pInstance) {
            s_pInstance = new CJournalRecordHookEngine(pWnd, nMsg);
        }
        return s_pInstance;
    }
};

