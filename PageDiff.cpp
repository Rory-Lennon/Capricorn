#include "stdafx.h"
#include "capricorn.h"
#include "PageDiff.h"
#include "SJParamSet.h"

CPageDiff::CPageDiff() : CPageBase(CPageDiff::IDD)
{
	//{{AFX_DATA_INIT(CPageDiff)
	//}}AFX_DATA_INIT

	m_mode = IDM_D1;
}

void CPageDiff::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageDiff)
	DDX_Control(pDX, IDC_RAD_D1, m_rad1);
	DDX_Control(pDX, IDC_RAD_D2, m_rad2);
	DDX_Control(pDX, IDC_RAD_D3, m_rad3);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageDiff, CPageBase)
	//{{AFX_MSG_MAP(CPageDiff)
	ON_BN_CLICKED(IDC_BUT_DIFF1, OnButDiff1)
	ON_BN_CLICKED(IDC_BUT_DIFF2, OnButDiff2)
	ON_BN_CLICKED(IDC_BUT_DIFF3, OnButDiff3)
	ON_MESSAGE(MSG_PARAMS, on_params)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

LONG CPageDiff::on_params(WPARAM wParam, LPARAM lParam)
{
	SJParamSet* p_params = &mp_data_base->mp_primary_dataset->m_params;
	if(p_params == NULL) return TRUE;

	if(wParam == TO_DIALOG)
	{
		UpdateData(TO_DIALOG);
	}
	if(wParam == FROM_DIALOG)
	{
		UpdateData(FROM_DIALOG);
	}
	return TRUE;
}

BOOL CPageDiff::OnSetActive()
{
	CPageBase::OnSetActive();
	mp_data_base->change_mode_one(m_mode);
	return TRUE;
}

BOOL CPageDiff::OnInitDialog() 
{
	CPageBase::OnInitDialog();
//	reset();
	OnButDiff1();
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CPageDiff::OnButDiff1() 
{
	UpdateData(FROM_DIALOG);
//	mp_data_base->reset_data();
//	mp_data_base->calc_d1(m_D1L);

	m_mode = IDM_D1;
	mp_data_base->change_mode_one(IDM_D1);

	m_rad1.SetCheck(TRUE);
	m_rad2.SetCheck(FALSE);
	m_rad3.SetCheck(FALSE);

//	enable_d2();
	update_view();	
}

void CPageDiff::OnButDiff2() 
{
	UpdateData(FROM_DIALOG);

//	mp_data_base->update_data();
	m_mode = IDM_D2;
	mp_data_base->change_mode_one(IDM_D2);

	m_rad1.SetCheck(FALSE);
	m_rad2.SetCheck(TRUE);
	m_rad3.SetCheck(FALSE);

	update_view();		
}

void CPageDiff::OnButDiff3() 
{
	UpdateData(FROM_DIALOG);
// _data_base->calc_d3(m_D3L);

	m_mode = IDM_D3;
	mp_data_base->change_mode_one(IDM_D3);
//	enable_d2();

	m_rad1.SetCheck(FALSE);
	m_rad2.SetCheck(FALSE);
	m_rad3.SetCheck(TRUE);	

	update_view();	
}

void CPageDiff::enable_d2()
{
	GetDlgItem(IDC_EDIT_RANGE2)->EnableWindow(TRUE);
	GetDlgItem(IDC_RAD_D2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUT_DIFF2)->EnableWindow(TRUE);
}

void CPageDiff::disable_d2()
{
	GetDlgItem(IDC_EDIT_RANGE2)->EnableWindow(FALSE);
	GetDlgItem(IDC_RAD_D2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_DIFF2)->EnableWindow(FALSE);
}

void CPageDiff::reset()
{
	m_rad1.SetCheck(FALSE);
	m_rad2.SetCheck(FALSE);
	m_rad3.SetCheck(FALSE);
	disable_d2();
}


