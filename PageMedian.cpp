#include "stdafx.h"
#include "capricorn.h"
#include "PageMedian.h"
#include "MainFrm.h"
#include "SJParamSet.h"

CPageMedian::CPageMedian() : CPageBase(CPageMedian::IDD)
{
   SYSTEMTIME curTime;
   GetLocalTime(&curTime);
	CTime time(curTime);

	//{{AFX_DATA_INIT(CPageMedian)
	m_add_day = time.GetDay();
	m_add_month = time.GetMonth();
	m_add_year = time.GetYear();
	m_add_val = 0.0;
	//}}AFX_DATA_INIT
}

void CPageMedian::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageMedian)
	DDX_Text(pDX, IDE_ADD_DAY, m_add_day);
	DDX_Text(pDX, IDE_ADD_MONTH, m_add_month);
	DDX_Text(pDX, IDE_ADD_YEAR, m_add_year);
	DDX_Text(pDX, IDE_ADD_VAL, m_add_val);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageMedian, CPageBase)
	//{{AFX_MSG_MAP(CPageMedian)
	ON_BN_CLICKED(IDC_BUT_NEW_APPLY, OnButNewApply)
	ON_MESSAGE(MSG_PARAMS, on_params)
	ON_BN_CLICKED(IDC_BUT_UNDO, OnButUndo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

LONG CPageMedian::on_params(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

BOOL CPageMedian::OnSetActive()
{
	mp_data_base->change_mode_one(IDM_VAL);
	CPageBase::OnSetActive();
	return TRUE; 
}

BOOL CPageMedian::OnInitDialog() 
{
	CPageBase::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CPageMedian::OnButNewApply() 
{
	UpdateData(FROM_DIALOG);

	if(m_add_day <  1) m_add_day = 1;
	if(m_add_day > 31) m_add_day = 31;

	if(m_add_month <  1) m_add_month =  1;
	if(m_add_month > 12) m_add_month = 12;

	UpdateData(FROM_DIALOG);
	
	if(!mp_data_base->add_new_point(m_add_day, m_add_month, m_add_year, m_add_val))
	{
		MessageBox("Date Too Small.", "Error", MB_OK | MB_ICONERROR);
	}
	mp_data_base->change_mode_one(IDM_VAL);
	update_view();	
}

void CPageMedian::OnButUndo() 
{
	mp_data_base->undo_add();
	update_view();	
}


