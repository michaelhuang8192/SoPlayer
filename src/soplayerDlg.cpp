
// soplayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "soplayer.h"
#include "soplayerDlg.h"
#include "afxdialogex.h"
#include "CDsopocx.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CsoplayerDlg dialog

#define ID_AX_SOPLAYER 100001
#define ID_ST_STATUS 100010
#define ID_TM_STATUS 100100
#define ID_TM_SFOCUS 100101

typedef struct
{
	union {
		wchar_t data[4][256];
		struct {
			wchar_t sopaddress[256];
			wchar_t user[256];
			wchar_t pass[256];
			wchar_t authurl[256];
		};
	};

} channel_t;

static channel_t g_channels[11];
static int g_cur_chid = 0;

static void parse_channel()
{
	wchar_t ini[MAX_PATH];
	wchar_t buf[1024];
	wchar_t key[16];

	GetModuleFileName(0, ini, sizeof(ini)/sizeof(ini[0]));
	wcscpy(wcsrchr(ini, L'\\'), L"\\channel.ini");
	memset(g_channels, 0, sizeof(g_channels));

	for(int i = 0; i <= 10; i++) {
		channel_t *channel = &g_channels[i];
		swprintf(key, L"key_%01X", i);
		GetPrivateProfileString(L"channel", key, L"", buf, sizeof(buf)/sizeof(buf[0]), ini);
		wchar_t *beg = buf;
		for(int j = 0; j < 4; j++) {
			wchar_t *end = wcschr(beg, L',');
			if(end) {
				memcpy(&channel->data[j], beg, (unsigned long)end - (unsigned long)beg);
				beg = &end[1];
			} else {
				wcscpy((wchar_t*)&channel->data[j], beg);
				break;
			}
		}
		//printf("-%S -%S -%S -%S\n", channel->sopaddress, channel->user, channel->pass, channel->authurl);
	}

}

static void play_channel(CDsopocx *sop, int i)
{
	channel_t *channel = &g_channels[i];
	g_cur_chid = i;

	if(sop->GetState(2)) sop->Stop();
	if(!channel->sopaddress[0]) return;

	//printf("play_channel---\n");

	sop->SetSopAddress(channel->sopaddress);
	sop->Play();

}


CsoplayerDlg::CsoplayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CsoplayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_sop = new CDsopocx();
	m_font = new CFont();
}

void CsoplayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, ID_STATIC_STATUS, m_status);
}

BEGIN_MESSAGE_MAP(CsoplayerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDOK, &CsoplayerDlg::OnIdok)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CsoplayerDlg message handlers

BOOL CsoplayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	parse_channel();

	m_brush = new CBrush(RGB(0, 0, 0));

	int cx = ::GetSystemMetrics(SM_CXSCREEN);
	int cy = ::GetSystemMetrics(SM_CYSCREEN) + 73;
	this->SetWindowPos(0, 0, 0, cx, cy, 0);

	m_sop->Create(L"soplayer", WS_VISIBLE, CRect(0, 0, cx, cy), this, ID_AX_SOPLAYER);
	m_sop->EnableWindow(0);

	//::AllocConsole();
	//freopen("CONOUT$", "w", stdout);

	m_status = new CStatic();
	int s_x = (cx - 300) / 2;
	int s_y = (cy - 100) / 2;
	m_status->Create(L"", WS_CHILD | SS_CENTER,
		CRect(s_x, s_y, s_x + 300, s_y + 100),
		this, ID_ST_STATUS
		);
	m_font->CreatePointFont(720, L"Arial");
	m_status->SetFont(m_font);
	m_status->SetWindowPos(&this->wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	this->SetTimer(ID_TM_STATUS, 1000, 0);
	this->SetTimer(ID_TM_SFOCUS, 500, 0);

	m_sop->SetAuthUrl(g_channels[0xA].authurl);
	m_sop->SetUsername(g_channels[0xA].user);
	m_sop->SetPassword(g_channels[0xA].pass);
	play_channel(m_sop, 0);

	::ShowCursor(0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CsoplayerDlg::OnPaint()
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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CsoplayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CsoplayerDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN) {
		long key = pMsg->wParam;
		//printf("%X\n", key);
		if(key >= 0x60 && key <= 0x69) {
			play_channel(m_sop, key - 0x60);

		} else if(key == 0x6B) { //+

		} else if(key == 0x6D) { //-

		} else if(key == 0x0D) {
			if(m_sop->GetState(2))
				m_sop->Stop();
			else
				m_sop->Play();
		}

	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CsoplayerDlg::OnIdok()
{
	// TODO: Add your command handler code here

}


void CsoplayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == ID_TM_STATUS) {
		long prc;
		if(m_sop->GetState(2) == 1 && (prc=m_sop->GetState(3)) >= 0 && prc < 50) {
			wchar_t buf[32];
			swprintf(buf, L"%d%%", prc);
			m_status->SetWindowTextW(buf);
			if(!m_status->IsWindowVisible()) m_status->ShowWindow(1);

		} else {
			if(m_status->IsWindowVisible()) m_status->ShowWindow(0);

		}

	} else if(nIDEvent == ID_TM_SFOCUS) {
		if(this->GetForegroundWindow() != this) this->SetForegroundWindow();

	}

	CDialogEx::OnTimer(nIDEvent);
}


HBRUSH CsoplayerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == ID_ST_STATUS) {
		pDC->SetTextColor(RGB(30, 255, 0));
		pDC->SetBkMode(TRANSPARENT);

		return *m_brush;
	}

	return hbr;
}


void CsoplayerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	m_sop->SetWindowPos(0, 0, 0, cx, cy, 0);

}
