#ifndef __HOOK_INTERFACES_DEF__
#define __HOOK_INTERFACES_DEF__

#include <Windows.h>

__interface IHookEngine
{
public:
    virtual bool PreHook(int nCode, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    virtual void PostHook(int nCode, WPARAM wParam, LPARAM lParam, LRESULT res);
    virtual HHOOK HookHandle();
    virtual int HookId();
};

__interface IHookManager
{
public:
    virtual bool registerEngine(int idHook, IHookEngine* pEngine);
    virtual bool removeEngine(int idHook);
};

typedef IHookManager* (CALLBACK *getHookManagerFunc)(void);

#define getHookManagerFuncName      "getHookManager"
#define LowlevelKeyboardProcName    "LowlevelKeyboardProc"
#define LowlevelMouseProcName       "LowlevelMouseProc"

#endif // __HOOK_INTERFACES_DEF__
