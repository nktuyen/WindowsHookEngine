
// SystemInspectorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SystemInspector.h"
#include "SystemInspectorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSystemInspectorDlg dialog

UINT CSystemInspectorDlg::s_nHookNotifyId = 0;

CSystemInspectorDlg::CSystemInspectorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SYSTEMINSPECTOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_pKeyboardHookEngine = nullptr;
    m_pMouseHookEngine = nullptr;
    m_hHookLibrary = nullptr;
}

CSystemInspectorDlg::~CSystemInspectorDlg()
{
    if (nullptr != m_pKeyboardHookEngine) {
        delete m_pKeyboardHookEngine;
        m_pKeyboardHookEngine = nullptr;
    }

    if (nullptr != m_pMouseHookEngine) {
        delete m_pMouseHookEngine;
        m_pMouseHookEngine = nullptr;
    }

    if (nullptr != m_hHookLibrary) {
        FreeLibrary(m_hHookLibrary);
        m_hHookLibrary = nullptr;
    }
}

void CSystemInspectorDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDT_LOG, m_edtLog);
}

BEGIN_MESSAGE_MAP(CSystemInspectorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BTN_HOOK_KEYBOARD, &CSystemInspectorDlg::OnBnClickedBtnHookKeyboard)
    ON_BN_CLICKED(IDC_BTN_HOOK_MOUSE, &CSystemInspectorDlg::OnBnClickedBtnHookMouse)
    ON_REGISTERED_MESSAGE(CSystemInspectorDlg::s_nHookNotifyId, &CSystemInspectorDlg::OnHookNotify)
    ON_BN_CLICKED(IDC_BTN_CLEAR_LOG, &CSystemInspectorDlg::OnBnClickedBtnClearLog)
END_MESSAGE_MAP()


// CSystemInspectorDlg message handlers

BOOL CSystemInspectorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

    CString strMsgId;
    strMsgId.Format(_T("%s-%p-%ld"), AfxGetAppName(), AfxGetInstanceHandle(), GetCurrentThreadId());
    s_nHookNotifyId = RegisterWindowMessage(strMsgId);

    m_pKeyboardHookEngine = new CKeyboardHookEngine(this, s_nHookNotifyId);
    m_pMouseHookEngine = new CMouseHookEngine(this, s_nHookNotifyId);
    m_hHookLibrary = LoadLibrary(_T("HookEngine.dll"));
    if (nullptr != m_hHookLibrary) {
        getHookManagerFunc fn = (getHookManagerFunc)GetProcAddress(m_hHookLibrary, getHookManagerFuncName);
        if (nullptr != fn) {
            m_pHookManager = fn();
            if (nullptr != m_pHookManager) {
                m_pHookManager->registerEngine(m_pKeyboardHookEngine->HookId(), m_pKeyboardHookEngine);
                m_pHookManager->registerEngine(m_pMouseHookEngine->HookId(), m_pMouseHookEngine);
            }
        }
    }

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSystemInspectorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CSystemInspectorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CSystemInspectorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CSystemInspectorDlg::OnHookNotify(WPARAM wParam, LPARAM lParam)
{
    SHookData* pData = (SHookData*)(lParam);
    CString strInfo;
    if (nullptr == pData) {
        return 0L;
    }

    switch (wParam)
    {
    case WH_MOUSE_LL:
    {
        if (HC_ACTION == pData->nCode) {
            UINT nMouseMsg = (UINT)pData->wParam;
            MSLLHOOKSTRUCT mouseData;
            ZeroMemory(&mouseData, sizeof(MSLLHOOKSTRUCT));
            CopyMemory(&mouseData, (MSLLHOOKSTRUCT*)pData->lParam, sizeof(MSLLHOOKSTRUCT));

            strInfo.Format(_T("Message=%d, X=%d, Y=%d"), nMouseMsg, mouseData.pt.x, mouseData.pt.y);
            
            CString strLog;
            m_edtLog.GetWindowText(strLog);
            if (!strLog.IsEmpty())
                strLog.Append(_T("\r\n"));

            strLog.Append(strInfo);
            m_edtLog.SetWindowText(strLog);
            m_edtLog.LineScroll(m_edtLog.GetLineCount(), -1);
        }
    }
    break;
    case WH_KEYBOARD_LL:
    {
        if (HC_ACTION == pData->nCode) {
            UINT nKeyMsg = (UINT)pData->wParam;
            KBDLLHOOKSTRUCT keyData;
            ZeroMemory(&keyData, sizeof(KBDLLHOOKSTRUCT));
            CopyMemory(&keyData, (KBDLLHOOKSTRUCT*)lParam, sizeof(KBDLLHOOKSTRUCT));

            strInfo.Format(_T("Message=%d, KeyCode=%d, ScanCode=%d, Flags=%d"), nKeyMsg, keyData.vkCode, keyData.scanCode, keyData.flags);

            CString strLog;
            m_edtLog.GetWindowText(strLog);
            if (!strLog.IsEmpty())
                strLog.Append(_T("\r\n"));

            strLog.Append(strInfo);
            m_edtLog.SetWindowText(strLog);
            m_edtLog.LineScroll(m_edtLog.GetLineCount(), -1);
        }
    }
    break;
    default:
        break;
    }

    return 0L;
}

void CSystemInspectorDlg::OnBnClickedBtnHookKeyboard()
{
    static BOOL bKeyboardHookStarted = FALSE;

    if (nullptr == m_hHookLibrary)
        return;

    if (!bKeyboardHookStarted) {
        HOOKPROC fn = (HOOKPROC)GetProcAddress(m_hHookLibrary, LowlevelKeyboardProcName);
        if (nullptr != fn) {
            if (nullptr != m_pKeyboardHookEngine) {
                m_pKeyboardHookEngine->Hook(fn, m_hHookLibrary, 0);
            }
            else {
                return;
            }
        }
    }
    else {
        if (nullptr != m_pKeyboardHookEngine) {
            m_pKeyboardHookEngine->Unhook();
        }
    }

    bKeyboardHookStarted = (!bKeyboardHookStarted);

    if (bKeyboardHookStarted) {
        SetDlgItemText(IDC_BTN_HOOK_KEYBOARD, _T("Stop Keyboard Hook"));
    }
    else {
        SetDlgItemText(IDC_BTN_HOOK_KEYBOARD, _T("Start Keyboard Hook"));
    }
}


void CSystemInspectorDlg::OnBnClickedBtnHookMouse()
{
    static BOOL bMouseHookStarted = FALSE;

    if (nullptr == m_hHookLibrary)
        return;

    if (!bMouseHookStarted) {
        HOOKPROC fn = (HOOKPROC)GetProcAddress(m_hHookLibrary, LowlevelMouseProcName);
        if (nullptr != fn) {
            if (nullptr != m_pMouseHookEngine) {
                m_pMouseHookEngine->Hook(fn, m_hHookLibrary, 0);
            }
            else {
                return;
            }
        }
    }
    else {
        if (nullptr != m_pMouseHookEngine) {
            m_pMouseHookEngine->Unhook();
        }
    }

    bMouseHookStarted = (!bMouseHookStarted);

    if (bMouseHookStarted) {
        SetDlgItemText(IDC_BTN_HOOK_MOUSE, _T("Stop Mouse Hook"));
    }
    else {
        SetDlgItemText(IDC_BTN_HOOK_MOUSE, _T("Start Mouse Hook"));
    }
}


void CSystemInspectorDlg::OnBnClickedBtnClearLog()
{
    SetDlgItemText(IDC_EDT_LOG, nullptr);
}
