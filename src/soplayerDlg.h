
// soplayerDlg.h : header file
//

#pragma once

class CDsopocx;

// CsoplayerDlg dialog
class CsoplayerDlg : public CDialogEx
{
// Construction
public:
	CsoplayerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SOPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CDsopocx *m_sop;
	CStatic *m_status;
	CFont *m_font;
	CBrush *m_brush;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnIdok();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
