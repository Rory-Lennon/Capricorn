#include "stdafx.h"
#include "capricorn.h"
#include "PageImport.h"
#include "MainFrm.h"
#include "SJParamSet.h"

CPageImport::CPageImport() : CPageBase(CPageImport::IDD)
{
	//{{AFX_DATA_INIT(CPageImport)
	m_col_date	= 1;
	m_col_val	= 2;
	//}}AFX_DATA_INIT
}

void CPageImport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageImport)
	DDX_Text(pDX, IDE_COL_DATE, m_col_date);
	DDX_Text(pDX, IDE_COL_VAL, m_col_val);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageImport, CPageBase)
	//{{AFX_MSG_MAP(CPageImport)
	ON_MESSAGE(MSG_PARAMS, on_params)
	ON_BN_CLICKED(IDB_MOVE_UP, OnMoveUp)
	ON_BN_CLICKED(IDB_DELETE, OnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

LONG CPageImport::on_params(WPARAM wParam, LPARAM lParam)
{
	if(wParam == TO_DIALOG)
	{
		m_col_date = ((CCapricornApp*)AfxGetApp())->m_datesincol;
		m_col_val = ((CCapricornApp*)AfxGetApp())->m_valsincol;
		UpdateData(TO_DIALOG);	
	}
	if(wParam == FROM_DIALOG)
	{
		UpdateData(FROM_DIALOG);	
		((CCapricornApp*)AfxGetApp())->m_datesincol = m_col_date;
		((CCapricornApp*)AfxGetApp())->m_valsincol = m_col_val;
	}
	return TRUE; 
}

BOOL CPageImport::OnSetActive()
{
	mp_data_base->change_mode_one(IDM_VAL);
	CPageBase::OnSetActive();
	return TRUE; 
}

BOOL CPageImport::OnInitDialog() 
{
	CPageBase::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CPageImport::OnMoveUp() 
{
	mp_data_base->move_up();
	on_params(UPDATE_LIST, 0);	
	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, UPDATE_LIST);
	update_view();		
}

void CPageImport::OnDelete() 
{
	mp_data_base->delete_set();
	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, UPDATE_LIST);
	update_view();			
}
