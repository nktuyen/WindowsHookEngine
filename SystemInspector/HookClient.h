#pragma once
#include "HookEngine.h"

class CHookClient : public CHookEngine
{
protected:
    CWnd    * m_pWnd;
    UINT    m_nNotifyMsg;
    SHookData m_Data;
protected:
    CHookClient(int idHook, CWnd * pWnd, UINT nMsg);
    virtual ~CHookClient();
public:
   virtual void PostHook(int nCode, WPARAM wParam, LPARAM lParam, LRESULT res);
};

