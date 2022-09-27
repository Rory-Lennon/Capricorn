#include "stdafx.h"
#include "Capricorn.h"
#include "MainFrm.h"

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_WM_CAPTURECHANGED()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMainFrame::CMainFrame()
{
	mp_last_wnd = NULL;
}

CMainFrame::~CMainFrame()
{}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1) return -1;

	m_view_one.	Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL);
	m_view_two.	Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL);
	m_view_time.Create(NULL, NULL, WS_CHILD | WS_VISIBLE,             CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL);

	m_status.Create(this);

	m_sheet.AddPage(&m_page_import);			// 0
	m_sheet.AddPage(&m_page_range);			// 1
	m_sheet.AddPage(&m_page_info);			// 2
	m_sheet.AddPage(&m_page_median);			// 3
//	m_sheet.AddPage(&m_page_diff);			// 
	m_sheet.AddPage(&m_page_flags);			// 4
	m_sheet.AddPage(&m_page_analyse);		// 5

	m_sheet.Create(this, WS_CHILD | WS_VISIBLE);
	m_list.Create(IDD_LIST, this);
	m_list.ShowWindow(SW_SHOW);
	m_results.Create(IDD_RESULTS, this);

	m_results.ShowWindow(SW_SHOW);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	CFrameWnd::PreCreateWindow(cs);
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
//	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	m_view_one.SetFocus();
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(rect);

	m_status.GetClientRect(rect);
	int STATUS_HEIGHT = rect.bottom;

	int vh	= cy - STATUS_HEIGHT - CTRLS_HEIGHT - TIME_HEIGHT;

	int v1h	= vh / 2;
	int vmh	= TIME_HEIGHT;
	int v2h	= vh / 2;

	int v1t	= 0;
	int vmt	= v1h;
	int v2t	= v1h + vmh;

	m_list.MoveWindow(0, 0, DOCK_WIDTH, cy - STATUS_HEIGHT - CTRLS_HEIGHT - RESULTS_HEIGHT);
	m_results.MoveWindow(0, cy - STATUS_HEIGHT - CTRLS_HEIGHT - RESULTS_HEIGHT, DOCK_WIDTH, RESULTS_HEIGHT);
	m_sheet.MoveWindow(0, cy - STATUS_HEIGHT - CTRLS_HEIGHT, cx, CTRLS_HEIGHT);

	m_view_time.MoveWindow(DOCK_WIDTH, vmt, cx - DOCK_WIDTH, vmh);
	m_view_one.MoveWindow(DOCK_WIDTH, v2t, cx - DOCK_WIDTH, v2h);
	m_view_two.MoveWindow(DOCK_WIDTH, v1t, cx - DOCK_WIDTH, v1h);
}

void CMainFrame::OnCaptureChanged(CWnd *pWnd) 
{
	CFrameWnd::OnCaptureChanged(pWnd);
	Invalidate(TRUE);
}

void CMainFrame::update_views()
{
	m_view_one.Invalidate();
	m_view_two.Invalidate();
	m_view_time.Invalidate();
}

void CMainFrame::OnMouseMove(UINT nFlags, CPoint point) 
{
	CFrameWnd::OnMouseMove(nFlags, point);
}

BOOL CMainFrame::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
//	TRACE("NOW\n");

//	TRACE("NOW %i %i\n", mp_last_wnd, &m_view_one);

	if(pWnd != &m_view_one)
	{
//		TRACE("NOW %i %i\n", mp_last_wnd, &m_view_one);

		if(mp_last_wnd == &m_view_one) 
		{
			m_view_one.m_show_hairs = FALSE;
			m_view_one.Invalidate();
		}
	}
	if(pWnd != &m_view_two)
	{
		if(mp_last_wnd == &m_view_two) 
		{
			m_view_two.m_show_hairs = FALSE;
			m_view_two.Invalidate();
		}
	}
	mp_last_wnd = pWnd;

	return CFrameWnd::OnSetCursor(pWnd, nHitTest, message);
}
