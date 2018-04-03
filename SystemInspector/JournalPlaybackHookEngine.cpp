#include "stdafx.h"
#include "JournalPlaybackHookEngine.h"

CJournalPlaybackHookEngine* CJournalPlaybackHookEngine::s_pInstance = nullptr;

CJournalPlaybackHookEngine::CJournalPlaybackHookEngine(CWnd* pOwner /* = nullptr */, UINT nCommMsg /* = 0 */)
    :CHookClient(WH_JOURNALPLAYBACK, pOwner, nCommMsg)
{
}


CJournalPlaybackHookEngine::~CJournalPlaybackHookEngine()
{
}
