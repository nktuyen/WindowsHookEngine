#pragma once
#include "HookClient.h"
class CJournalPlaybackHookEngine : public CHookClient
{
private:
    static CJournalPlaybackHookEngine* s_pInstance;
    CJournalPlaybackHookEngine(CWnd* pOwner = nullptr, UINT nCommMsg = 0);
public:
    virtual ~CJournalPlaybackHookEngine();
    static CJournalPlaybackHookEngine* createInstance(CWnd* pWnd, UINT nMsg) {
        if (nullptr == s_pInstance) {
            s_pInstance = new CJournalPlaybackHookEngine(pWnd, nMsg);
        }
        return s_pInstance;
    }
};

