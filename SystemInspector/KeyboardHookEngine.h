#pragma once
#include "HookClient.h"
class CKeyboardHookEngine : public CHookClient
{
private:
    static CKeyboardHookEngine* s_pInstance;
    CKeyboardHookEngine(CWnd* pWnd, UINT nMsg);
public:
    virtual ~CKeyboardHookEngine();
    static CKeyboardHookEngine* createInstance(CWnd* pWnd, UINT nMsg) {
        if (nullptr == s_pInstance) {
            s_pInstance = new CKeyboardHookEngine(pWnd, nMsg);
        }
        return s_pInstance;
    }
};

