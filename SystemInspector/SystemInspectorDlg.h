
// SystemInspectorDlg.h : header file
//

#pragma once

#include "KeyboardHookEngine.h"
#include "MouseHookEngine.h"
#include "afxwin.h"

// CSystemInspectorDlg dialog
class CSystemInspectorDlg : public CDialogEx
{
// Construction
public:
	CSystemInspectorDlg(CWnd* pParent = NULL);	// standard constructor
    virtual ~CSystemInspectorDlg();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYSTEMINSPECTOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
    static UINT s_nHookNotifyId;
    CKeyboardHookEngine *m_pKeyboardHookEngine;
    CMouseHookEngine *m_pMouseHookEngine;
    IHookManager* m_pHookManager;
    HMODULE m_hHookLibrary;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedBtnHookKeyboard();
    afx_msg void OnBnClickedBtnHookMouse();
    afx_msg LRESULT OnHookNotify(WPARAM wParam, LPARAM lParam);
    afx_msg void OnBnClickedBtnClearLog();
    CEdit m_edtLog;
};
