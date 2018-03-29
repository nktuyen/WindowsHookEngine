#pragma once
#include "HookEngine.h"
class CKeyboardHookEngine : public CHookEngine
{
private:
    CWnd    * m_pWnd;
    UINT    m_nNotifyMsg;
    SHookData m_Data;
public:
    CKeyboardHookEngine(CWnd* pWnd, UINT nMsg);
    virtual ~CKeyboardHookEngine();

    bool PreHook(int nCode, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    void PostHook(int nCode, WPARAM wParam, LPARAM lParam, LRESULT res);
};

