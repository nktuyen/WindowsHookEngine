// HookEngine.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "HookEngine.h"

CHookManager* CHookManager::s_pInstance = nullptr;

HOOKENGINE_API IHookManager* CALLBACK getHookManager()
{
    return CHookManager::getInstance();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {

    }
    break;
    case DLL_THREAD_ATTACH:
    {

    }
    break;
    case DLL_THREAD_DETACH:
    {

    }
    break;
    case DLL_PROCESS_DETACH:
    {
        delete CHookManager::getInstance();
    }
    break;
        break;
    }
    return TRUE;
}

HOOKENGINE_API LRESULT CALLBACK LowlevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    CHookManager* pManager = CHookManager::getInstance();
    LRESULT res = 0L;

    if (nullptr != pManager) {
        if (pManager->PreHook(WH_KEYBOARD_LL, nCode, wParam, lParam, &res)) {
            return res;
        }

        return pManager->PostHook(WH_KEYBOARD_LL, nCode, wParam, lParam);
    }

    return res;
}

HOOKENGINE_API LRESULT CALLBACK LowlevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    CHookManager* pManager = CHookManager::getInstance();
    LRESULT res = 0L;

    if (nullptr != pManager) {
        LRESULT res = 0L;
        if (pManager->PreHook(WH_MOUSE_LL, nCode, wParam, lParam, &res)) {
            return res;
        }

        return pManager->PostHook(WH_MOUSE_LL, nCode, wParam, lParam);
    }

    return res;
}

CHookManager::CHookManager()
{
    for (int n = WH_MIN; n <= WH_MAX; n++) {
        m_pEngines[n+1] = nullptr;
    }
}

CHookManager::~CHookManager()
{
    IHookEngine* pEngine = nullptr;
    for (int n = WH_MIN; n <= WH_MAX; n++) {
        m_pEngines[n + 1] = nullptr;
    }
}

bool CHookManager::PreHook(int idHook, int nCode, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    IHookEngine* pEngine = nullptr;
    if ((idHook >= WH_MIN) && (idHook <= WH_MAX)) {
        pEngine = m_pEngines[idHook + 1];
        if (nullptr != pEngine) {
            return pEngine->PreHook(nCode, wParam, lParam, pResult);
        }
    }

    return false;
}

LRESULT CHookManager::PostHook(int idHook, int nCode, WPARAM wParam, LPARAM lParam)
{
    IHookEngine* pEngine = nullptr;
    LRESULT res = 0L;
    if ((idHook >= WH_MIN) && (idHook <= WH_MAX)) {
        pEngine = m_pEngines[idHook + 1];
        if (nullptr != pEngine) {
            res = CallNextHookEx(pEngine->HookHandle(), nCode, wParam, lParam);
            pEngine->PostHook(nCode, wParam, lParam, res);
        }
    }

    return res;
}

bool CHookManager::registerEngine(int idHook, IHookEngine* pEngine)
{
    if ((idHook < WH_MIN) || (idHook > WH_MAX)) {
        return false;
    }

    IHookEngine* pCurEngine = m_pEngines[idHook + 1];
    if (nullptr != pCurEngine) {
        return false;
    }

    m_pEngines[idHook + 1] = pEngine;
    return true;
}

bool CHookManager::removeEngine(int idHook)
{
    if ((idHook < WH_MIN) || (idHook > WH_MAX)) {
        return false;
    }

    m_pEngines[idHook + 1] = nullptr;
    
    return true;
}

IHookEngine* CHookManager::findEngine(int idHook)
{
    IHookEngine* pEngine = nullptr;

    if ((idHook >= WH_MIN) && (idHook <= WH_MAX)) {
        pEngine = m_pEngines[idHook + 1];
    }

    return pEngine;
}