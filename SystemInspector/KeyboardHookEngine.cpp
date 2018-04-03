#include "stdafx.h"
#include "KeyboardHookEngine.h"

CKeyboardHookEngine* CKeyboardHookEngine::s_pInstance = nullptr;

CKeyboardHookEngine::CKeyboardHookEngine(CWnd* pWnd, UINT nNotifyMsg)
    :CHookClient(WH_KEYBOARD_LL, pWnd, nNotifyMsg)
{
    
}

CKeyboardHookEngine::~CKeyboardHookEngine()
{
}