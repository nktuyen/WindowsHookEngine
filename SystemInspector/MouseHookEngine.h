#pragma once
#include "HookEngine.h"
class CMouseHookEngine : public CHookEngine
{
private:
    CWnd* m_pWnd;
    UINT m_nNotifyMsg;
    SHookData m_Data;
public:
    CMouseHookEngine(CWnd * pWnd, UINT nMsg);
    virtual ~CMouseHookEngine();
    void PostHook(int nCode, WPARAM wParam, LPARAM lParam, LRESULT res);
};

