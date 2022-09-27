#include "stdafx.h"
#include "capricorn.h"
#include "PageFlags.h"
#include "SJParamSet.h"

CPageFlags::CPageFlags() : CPageBase(CPageFlags::IDD)
{
	//{{AFX_DATA_INIT(CPageFlags)
	m_ML = 20;
	m_MU = 40;
	m_MC = 30;
	m_BC = 60;
	m_RC = 0.0;
	m_BI = 10;
	m_resolution = 0.0;
	//}}AFX_DATA_INIT
}

void CPageFlags::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageFlags)
	DDX_Control(pDX, IDC_SLIDER, m_slider_resolution);
	DDX_Text(pDX, IDE_ML, m_ML);
	DDX_Text(pDX, IDE_MU, m_MU);
	DDX_Text(pDX, IDE_MC, m_MC);
	DDX_Text(pDX, IDE_BC, m_BC);
	DDX_Text(pDX, IDE_RC, m_RC);
	DDX_Control(pDX, IDR_COARSE, m_rad_coarse);
	DDX_Control(pDX, IDR_FINE, m_rad_fine);
	DDX_Text(pDX, IDS_RESOLUTION, m_resolution);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageFlags, CPageBase)
	//{{AFX_MSG_MAP(CPageFlags)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN, OnDeltaposSpin)
	ON_MESSAGE(MSG_PARAMS, on_params)
	ON_BN_CLICKED(IDC_BUT_UPDATE, OnButUpdate)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER, OnReleasedcaptureSlider)
	ON_BN_CLICKED(IDR_COARSE, OnCoarse)
	ON_BN_CLICKED(IDR_FINE, OnFine)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

LONG CPageFlags::on_params(WPARAM wParam, LPARAM lParam)
{
////////////////
	SJParamSet* p_range_params = &mp_data_base->m_range;
////////////////
	SJDataSet* p_current_dataset = mp_data_base->mp_current_dataset;
	if(p_current_dataset == NULL) return TRUE;
	SJParamSet* p_current_params = &p_current_dataset->m_params;
////////////////
	SJDataSet* p_primary_dataset = mp_data_base->mp_primary_dataset;
	if(p_primary_dataset == NULL) return TRUE;
	SJParamSet* p_primary_params = &p_primary_dataset->m_params;
////////////////
	
	if((wParam == TO_CURRENT) || (wParam == TO_DIALOG))
	{
		m_RC = p_current_params->m_RC;
		UpdateData(TO_DIALOG);
	}
	if(wParam == TO_DIALOG)
	{
		m_slider_resolution.SetPos(p_range_params->m_RR);
		if(p_range_params->m_RR > 0.0) m_resolution = 1.0 / (double)p_range_params->m_RR;

		m_MC = p_primary_params	->m_ML;

		m_ML = p_range_params	->m_ML;
		m_MU = p_range_params	->m_MU;
		
		m_BC = p_primary_params	->m_BC;		
		m_BI = p_range_params	->m_BI;
		if(m_BI <= 5) OnFine();
		if(m_BI > 5) OnCoarse();

		UpdateData(TO_DIALOG);
	}
	if(wParam == FROM_DIALOG)
	{
		UpdateData(FROM_DIALOG);

		p_range_params->m_RR = m_slider_resolution.GetPos();

		if(m_MC < 1) m_MC = 1;
		p_primary_params->m_ML	= m_MC;

		if(m_ML < 1) m_ML = 1;
		if(m_MU < m_ML) m_MU = m_ML;
		p_range_params->m_ML	= m_ML;
		p_range_params->m_MU	= m_MU;

		if(m_RC > 1.0) m_RC = 1.0;
		if(m_RC < -1.0) m_RC = -1.0;
		p_current_params->m_RC	= m_RC;

		if(m_BC < BUY_LOWER) m_BC = BUY_LOWER;
		if(m_BC > BUY_UPPER) m_BC = BUY_UPPER;
		p_primary_params->m_BC	= m_BC;

		p_range_params->m_BI	= m_BI;
	}
	if(wParam == NEW_FILE)
	{
		m_MC = 0;
		m_RC = 0.0;
		m_BC = 0;
		GetDlgItem(IDS_RESOLUTION)->SetWindowText("");
		UpdateData(TO_DIALOG);
	}

	return TRUE;
}

BOOL CPageFlags::OnSetActive()
{
	CPageBase::OnSetActive();
	mp_data_base->change_mode_one(IDM_VAL);
	return TRUE;
}

BOOL CPageFlags::OnInitDialog() 
{
	CPageBase::OnInitDialog();
	m_slider_resolution.SetRange(2, 50);
	m_slider_resolution.SetTicFreq(2);

	GetDlgItem(IDE_ML)->EnableWindow(FALSE);
	GetDlgItem(IDE_MU)->EnableWindow(FALSE);
	GetDlgItem(IDC_SLIDER)->EnableWindow(FALSE);
	GetDlgItem(IDR_FINE)->EnableWindow(FALSE);
	GetDlgItem(IDR_COARSE)->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CPageFlags::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(FROM_DIALOG);
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	if(pNMUpDown->iDelta == -1) m_BC += m_BI;
	if(pNMUpDown->iDelta ==  1) m_BC -= m_BI;
	UpdateData(TO_DIALOG);
	OnButUpdate();
	*pResult = 1;
}

void CPageFlags::OnButUpdate() 
{
	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, FROM_DIALOG, 0, TRUE);
	mp_data_base->solve_single();
	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, TO_DIALOG, 0, TRUE);
	update_view();
}


void CPageFlags::OnReleasedcaptureSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	on_params(FROM_DIALOG, 0);
	on_params(TO_DIALOG, 0);
	*pResult = 0;
}

void CPageFlags::OnCoarse() 
{
	m_BI = 10;
	m_rad_coarse.SetCheck(TRUE);
	m_rad_fine.SetCheck(FALSE);
	UpdateData(TO_DIALOG);	
}

void CPageFlags::OnFine() 
{
	m_BI = 5;
	m_rad_fine.SetCheck(TRUE);
	m_rad_coarse.SetCheck(FALSE);
	UpdateData(TO_DIALOG);	
}
