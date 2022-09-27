#pragma once

#include "CapSheet.h"
#include "CtrlStatus.h"
#include "DlgList.h"
#include "DlgResults.h"
#include "ViewOne.h"
#include "ViewTwo.h"
#include "ViewTime.h"

#include "PageRange.h"
#include "PageMedian.h"
#include "PageDiff.h"
#include "PageFlags.h"
#include "PageAnalyse.h"
#include "PageInfo.h"
#include "PageImport.h"

class CMainFrame : public CFrameWnd
{
	
public:

	CMainFrame();

protected: 

	DECLARE_DYNAMIC(CMainFrame)

public:

	//{{AFX_VIRTUAL(CMainFrame)
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	//}}AFX_VIRTUAL

public:

	virtual			~CMainFrame();
	void				update_views();

	CCtrlStatus		m_status;
	CToolBar			m_wndToolBar;
	CViewOne 		m_view_one;
	CViewTwo			m_view_two;
	CViewTime		m_view_time;
	CDlgResults		m_results;
	CDlgList			m_list;
	CCapSheet		m_sheet;
/////// PAGES /////////////////////
	CPageImport		m_page_import;
	CPageRange		m_page_range;
	CPageMedian		m_page_median;
	CPageDiff		m_page_diff;
	CPageAnalyse	m_page_analyse;
	CPageFlags		m_page_flags;
	CPageInfo		m_page_info;

	CWnd*				mp_last_wnd;

protected:

	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


