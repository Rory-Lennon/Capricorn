#include "stdafx.h"
#include "Capricorn.h"
#include "CapSheet.h"

IMPLEMENT_DYNAMIC(CCapSheet, CPropertySheet)

BEGIN_MESSAGE_MAP(CCapSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CCapSheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CCapSheet::CCapSheet() 
{
	mp_data_base = &(((CCapricornApp*)AfxGetApp())->m_data_base);
}

CCapSheet::~CCapSheet()
{}

BOOL CCapSheet::OnInitDialog() 
{
	CPropertySheet::OnInitDialog();
	
	CTabCtrl* p_tab = GetTabControl();
	p_tab->ModifyStyle(NULL, TCS_BOTTOM);
	p_tab->EnableWindow(FALSE);
	p_tab->ShowWindow(SW_HIDE);
	
	SetActivePage(0);
	SetActivePage(1);
	SetActivePage(2);
	SetActivePage(3);
	SetActivePage(4);
	SetActivePage(5);
	SetActivePage(6);

	return TRUE;
}

