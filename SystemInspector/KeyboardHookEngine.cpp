#include "stdafx.h"
#include "KeyboardHookEngine.h"


CKeyboardHookEngine::CKeyboardHookEngine(CWnd* pWnd, UINT nNotifyMsg)
    :CHookEngine(WH_KEYBOARD_LL)
{
    m_pWnd = pWnd;
    m_nNotifyMsg = nNotifyMsg;
    ZeroMemory(&m_Data, sizeof(SHookData));
}


CKeyboardHookEngine::~CKeyboardHookEngine()
{
}

bool CKeyboardHookEngine::PreHook(int nCode, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    m_Data.nCode = nCode;
    m_Data.wParam = wParam;
    m_Data.lParam = lParam;

    return false;
}

void CKeyboardHookEngine::PostHook(int nCode, WPARAM wParam, LPARAM lParam, LRESULT res)
{
    if ((nullptr != m_pWnd) && (m_pWnd->GetSafeHwnd())) {
        if (0 != m_nNotifyMsg) {
            m_pWnd->PostMessage(m_nNotifyMsg, (WPARAM)HookId(), (LPARAM)&m_Data);
        }
    }
}