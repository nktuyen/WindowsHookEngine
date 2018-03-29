#pragma once

#include "..\inc\HookInterfaces.h"

typedef struct SHookData_
{
    int nCode;
    WPARAM wParam;
    LPARAM lParam;
}SHookData;

class CHookEngine : public IHookEngine
{
private:
    HHOOK m_hHook;
    int m_idHook;
public:
    inline HHOOK HookHandle() { return m_hHook; }
    inline int HookId() { return m_idHook; }
public:
    CHookEngine(int idHook);
    virtual ~CHookEngine();
    virtual bool PreHook(int nCode, WPARAM, LPARAM lParam, LRESULT* pResult) { return false; };
    virtual void PostHook(int nCode, WPARAM, LPARAM lParam, LRESULT res) { ; }
    bool Hook(HOOKPROC fn, HINSTANCE hInst, DWORD dwThreadId);
    bool Unhook();
};

