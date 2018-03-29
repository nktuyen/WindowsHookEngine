#include "stdafx.h"
#include "HookEngine.h"


CHookEngine::CHookEngine(int idHook)
{
    m_hHook = nullptr;
    m_idHook = idHook;
}

CHookEngine::~CHookEngine()
{
    if (nullptr != m_hHook) {
        this->Unhook();
    }
}

bool CHookEngine::Hook(HOOKPROC fn, HINSTANCE hInst, DWORD dwThreadId)
{
    if (nullptr == m_hHook) {
        m_hHook = SetWindowsHookEx(m_idHook, fn, hInst, dwThreadId);
    }

    return ((nullptr != m_hHook) ? true : false);
}

bool CHookEngine::Unhook()
{
    if (nullptr != m_hHook) {
        if(UnhookWindowsHookEx(m_hHook)){
            m_hHook = nullptr;
        }
    }

    return (nullptr == m_hHook);
}