// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the HOOKENGINE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// HOOKENGINE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef HOOKENGINE_EXPORTS
#define HOOKENGINE_API __declspec(dllexport)
#else
#define HOOKENGINE_API __declspec(dllimport)
#endif
#include "HookInterfaces.h"


class HOOKENGINE_API CHookManager : public IHookManager
{
private:
    CHookManager(void);
    static CHookManager* s_pInstance;
    IHookEngine* m_pEngines[WH_MAX+2];
public:
    virtual ~CHookManager();
    CHookManager& operator=(const CHookManager& r) = delete;

    static CHookManager* getInstance() {
        if (nullptr == CHookManager::s_pInstance) {
            s_pInstance = ( new CHookManager() );
        }
        return s_pInstance;
    }

    bool PreHook(int idHook, int nCode, WPARAM, LPARAM lParam, LRESULT* pResult);
    LRESULT PostHook(int idHook, int nCode, WPARAM, LPARAM lParam);
    IHookEngine* findEngine(int idHook);
    bool registerEngine(int idHook, IHookEngine* pEngine);
    bool removeEngine(int idHook);
};


HOOKENGINE_API IHookManager* CALLBACK getHookManager();
HOOKENGINE_API LRESULT CALLBACK LowlevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
HOOKENGINE_API LRESULT CALLBACK LowlevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam);
