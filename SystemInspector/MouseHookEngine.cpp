#include "stdafx.h"
#include "MouseHookEngine.h"

CMouseHookEngine* CMouseHookEngine::s_pInstance = nullptr;

CMouseHookEngine::CMouseHookEngine(CWnd * pWnd, UINT nMsg)
    :CHookClient(WH_MOUSE_LL, pWnd, nMsg)
{
    
}

CMouseHookEngine::~CMouseHookEngine()
{
}