#include "stdafx.h"
#include "capricorn.h"
#include "PageBase.h"
#include "MainFrm.h"
#include "SJParamSet.h"

CPageBase::CPageBase(UINT val) : CPropertyPage(val) 
{
	//{{AFX_DATA_INIT(CPageBase)
	//}}AFX_DATA_INIT
	mp_data_base = &(((CCapricornApp*)AfxGetApp())->m_data_base);
}

CPageBase::~CPageBase()
{}

void CPageBase::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageBase)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageBase, CPropertyPage)
	//{{AFX_MSG_MAP(CPageBase)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CPageBase::OnSetActive()
{
	update_view();
	return CPropertyPage::OnSetActive();
}

void CPageBase::update_view()
{
	((CMainFrame*)AfxGetMainWnd())->update_views();
}

BOOL CPageBase::OnInitDialog() 
{
//	ModifyStyleEx(0, WS_EX_CONTROLPARENT);

	CPropertyPage::OnInitDialog();
	MoveWindow(&m_rect);

	return TRUE;  // return TRUE unless you set the focus to a control
}


