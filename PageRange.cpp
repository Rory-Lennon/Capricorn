#include "stdafx.h"
#include "capricorn.h"
#include "PageRange.h"
#include "MainFrm.h"
#include "SJParamSet.h"
// 
CPageRange::CPageRange() : CPageBase(CPageRange::IDD)
{
	//{{AFX_DATA_INIT(CPageRange)
	m_end_day = 1;
	m_end_month = 1;
	m_end_year = 99;
	m_start_day = 1;
	m_start_month = 1;
	m_start_year = 98;
	m_base_zero = FALSE;
	//}}AFX_DATA_INIT
}

void CPageRange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageRange)
	DDX_Text(pDX, IDC_END_DAY, m_end_day);
	DDX_Text(pDX, IDC_END_MONTH, m_end_month);
	DDX_Text(pDX, IDC_END_YEAR, m_end_year);
	DDX_Text(pDX, IDC_START_DAY, m_start_day);
	DDX_Text(pDX, IDC_START_MONTH, m_start_month);
	DDX_Text(pDX, IDC_START_YEAR, m_start_year);
	DDX_Check(pDX, IDC_BASE_ZERO, m_base_zero);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageRange, CPageBase)
	//{{AFX_MSG_MAP(CPageRange)
	ON_BN_CLICKED(IDC_BASE_ZERO, OnBaseZero)
	ON_BN_CLICKED(IDC_BUT_APPLY, OnButApply)
	ON_BN_CLICKED(IDC_BUT_LIMITS, OnButLimits)
	ON_NOTIFY(UDN_DELTAPOS, IDC_PAN, OnDeltaposPan)
	ON_NOTIFY(UDN_DELTAPOS, IDC_ZOOM, OnDeltaposZoom)
	ON_MESSAGE(MSG_PARAMS, on_params)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPageRange::check_dates()
{
	if(m_end_day <  1) m_end_day = 1;
	if(m_end_day > 31) m_end_day = 31;

	if(m_end_month <  1) m_end_month =  1;
	if(m_end_month > 12) m_end_month = 12;

	if(m_start_day <  1) m_start_day = 1;
	if(m_start_day > 31) m_start_day = 31;

	if(m_start_month <  1) m_start_month =  1;
	if(m_start_month > 12) m_start_month = 12;

	UpdateData(TO_DIALOG);
}

LONG CPageRange::on_params(WPARAM wParam, LPARAM lParam)
{	
	if(wParam == TO_DIALOG)
	{
		m_start_day		= mp_data_base->m_limits_one.m_min.m_day;
		m_start_month	= mp_data_base->m_limits_one.m_min.m_month;
		m_start_year	= mp_data_base->m_limits_one.m_min.m_year;
		m_end_day		= mp_data_base->m_limits_one.m_max.m_day;
		m_end_month		= mp_data_base->m_limits_one.m_max.m_month;
		m_end_year		= mp_data_base->m_limits_one.m_max.m_year;

		UpdateData(TO_DIALOG);
	}
	if(wParam == FROM_DIALOG)
	{
		UpdateData(FROM_DIALOG);

		check_dates();

		SJLimits limits;
		limits.m_min.set_date(DDMMYY, m_start_day, m_start_month, m_start_year);
		limits.m_max.set_date(DDMMYY, m_end_day, m_end_month, m_end_year);

		mp_data_base->set_date_limits(limits);
	}
	if(wParam == NEW_FILE)
	{
		SJLimits limits;
		limits.m_min.set_date(DDMMYY, 1, 1, 2000);
		limits.m_max.set_date(DDMMYY, 1, 1, 2003);

		mp_data_base->set_date_limits(limits);
		on_params(TO_DIALOG, 0);
	}
	return TRUE;
}

BOOL CPageRange::OnInitDialog() 
{
	CPageBase::OnInitDialog();
//	OnButLimits();
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CPageRange::OnBaseZero() 
{
	UpdateData(FROM_DIALOG);
	mp_data_base->m_limits_one.m_base_zero = m_base_zero;
	mp_data_base->m_limits_two.m_base_zero = m_base_zero;
	mp_data_base->set_val_limits();
	update_view();
}

void CPageRange::OnButApply() 
{
	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, FROM_DIALOG);
	update_view();
}

void CPageRange::OnButLimits() 
{
	mp_data_base->set_date_limits();
	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, TO_DIALOG);
	update_view();
}

void CPageRange::OnDeltaposPan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	SJLimits current_limits;
	mp_data_base->get_date_limits(current_limits);
	int range = current_limits.get_range();
	int dcr = (range / 5) + 1;

	SJLimits new_limits;

	if(pNMUpDown->iDelta == -1) 
	{
		new_limits.m_min.set_date(current_limits.m_min.m_date - dcr);
		new_limits.m_max.set_date(current_limits.m_max.m_date - dcr);
	}
	if(pNMUpDown->iDelta ==  1) 
	{
		new_limits.m_min.set_date(current_limits.m_min.m_date + dcr);
		new_limits.m_max.set_date(current_limits.m_max.m_date + dcr);
	}
	mp_data_base->set_date_limits(new_limits);

	m_start_day		= new_limits.m_min.m_day;
	m_start_month	= new_limits.m_min.m_month;
	m_start_year	= new_limits.m_min.m_year;
	m_end_day		= new_limits.m_max.m_day;
	m_end_month		= new_limits.m_max.m_month;
	m_end_year		= new_limits.m_max.m_year;

	UpdateData(TO_DIALOG);
	update_view();

	*pResult = 0;
}

void CPageRange::OnDeltaposZoom(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	SJLimits current_limits;
	mp_data_base->get_date_limits(current_limits);
	int range = current_limits.get_range();
	int dcr;

	SJLimits new_limits;
	new_limits.m_max.set_date(current_limits.m_max.m_date);
	
	if(pNMUpDown->iDelta == -1) 
	{
		dcr = (range / 5) + 1;
		new_limits.m_min.set_date(current_limits.m_min.m_date - dcr);
	}
	if(pNMUpDown->iDelta == 1) 
	{
		dcr = range / 5;
		new_limits.m_min.set_date(current_limits.m_min.m_date + dcr);
	}
	mp_data_base->set_date_limits(new_limits);

	m_start_day		= new_limits.m_min.m_day;
	m_start_month	= new_limits.m_min.m_month;
	m_start_year	= new_limits.m_min.m_year;
	m_end_day		= new_limits.m_max.m_day;
	m_end_month		= new_limits.m_max.m_month;
	m_end_year		= new_limits.m_max.m_year;

	UpdateData(TO_DIALOG);
	update_view();

	*pResult = 0;
}

