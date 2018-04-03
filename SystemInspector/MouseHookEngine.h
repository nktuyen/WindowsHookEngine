#pragma once
#include "HookClient.h"
class CMouseHookEngine : public CHookClient
{
private:
    CMouseHookEngine(CWnd * pWnd, UINT nMsg);
    static CMouseHookEngine* s_pInstance;
public:
    virtual ~CMouseHookEngine();
    static CMouseHookEngine* createInstance(CWnd * pWnd, UINT nMsg) {
        if (nullptr == s_pInstance) {
            s_pInstance = new CMouseHookEngine(pWnd, nMsg);
        }
        return s_pInstance;
    }
};

