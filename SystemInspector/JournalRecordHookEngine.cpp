#include "stdafx.h"
#include "JournalRecordHookEngine.h"

CJournalRecordHookEngine* CJournalRecordHookEngine::s_pInstance = nullptr;

CJournalRecordHookEngine::CJournalRecordHookEngine(CWnd* pOwnerWnd /* = nullptr */, UINT nCommMsg /* = 0 */)
    :CHookClient(WH_JOURNALRECORD, pOwnerWnd, nCommMsg)
{
    
}


CJournalRecordHookEngine::~CJournalRecordHookEngine()
{
}
