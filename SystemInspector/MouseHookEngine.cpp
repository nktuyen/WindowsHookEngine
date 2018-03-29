#include "stdafx.h"
#include "MouseHookEngine.h"


CMouseHookEngine::CMouseHookEngine(CWnd * pWnd, UINT nMsg)
    :CHookEngine(WH_MOUSE_LL)
{
    m_pWnd = pWnd;
    m_nNotifyMsg = nMsg;
    ZeroMemory(&m_Data, sizeof(SHookData));
}


CMouseHookEngine::~CMouseHookEngine()
{
}

void CMouseHookEngine::PostHook(int nCode, WPARAM wParam, LPARAM lParam, LRESULT res)
{
    m_Data.nCode = nCode;
    m_Data.wParam = wParam;
    m_Data.lParam = lParam;

    if ((nullptr != m_pWnd) && (m_pWnd->GetSafeHwnd())) {
        if (0 != m_nNotifyMsg) {
            m_pWnd->PostMessage(m_nNotifyMsg, (WPARAM)HookId(), (LPARAM)&m_Data);
        }
    }
}