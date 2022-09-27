#include "stdafx.h"
#include "capricorn.h"
#include "ViewTime.h"

CViewTime::CViewTime() 
{
	mp_data_base = &(((CCapricornApp*)AfxGetApp())->m_data_base);
}

CViewTime::~CViewTime()
{}

BEGIN_MESSAGE_MAP(CViewTime, CWnd)
	//{{AFX_MSG_MAP(CViewTime)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CViewTime::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rcdc; 
	dc.GetClipBox(rcdc);
	dc.FillSolidRect(rcdc, ::GetSysColor(COLOR_BTNFACE));
	((CCapricornApp*)AfxGetApp())->m_data_base.draw_time(dc);
}



