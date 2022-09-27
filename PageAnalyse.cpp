#include "stdafx.h"
#include "capricorn.h"
#include "PageAnalyse.h"
#include "SJParamSet.h"
#include "MainFrm.h"
#include "DlgCalc.h"

CPageAnalyse::CPageAnalyse() : CPageBase(CPageAnalyse::IDD)
{
	//{{AFX_DATA_INIT(CPageAnalyse)
	m_IN = 1000.0;
	m_TT = 5.0;
	//}}AFX_DATA_INIT
}

void CPageAnalyse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageAnalyse)
	DDX_Text(pDX, IDE_IN, m_IN);
	DDX_Text(pDX, IDE_TT, m_TT);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageAnalyse, CPageBase)
	//{{AFX_MSG_MAP(CPageAnalyse)
	ON_BN_CLICKED(IDC_BUT_PROCESS, OnButProcess)
	ON_MESSAGE(MSG_PARAMS, on_params)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

LONG CPageAnalyse::on_params(WPARAM wParam, LPARAM lParam)
{
////////////////
	SJParamSet* p_range_params = &mp_data_base->m_range;
////////////////
	SJDataSet* p_primary_dataset = mp_data_base->mp_primary_dataset;
	if(p_primary_dataset == NULL) return TRUE;
	SJParamSet* p_primary_params = &p_primary_dataset->m_params;
////////////////
	SJDataSet* p_current_dataset = mp_data_base->mp_current_dataset;
	if(p_current_dataset == NULL) return TRUE;
	SJParamSet* p_current_params = &p_current_dataset->m_params;
////////////////

	if(wParam == TO_DIALOG)
	{
		m_IN = p_primary_params->m_IN;
		if(m_IN < 0)
		{
			m_IN = 1.0;
			p_primary_params->m_IN = m_IN;
		}
		m_TT = p_primary_params->m_TT;
		if(m_TT < 0)
		{
			m_TT = 0.0;
			p_primary_params->m_TT = m_TT;
		}
		update_gain(p_primary_params->m_GN, p_primary_params->m_OUT);
		UpdateData(TO_DIALOG);
	}
	if(wParam == FROM_DIALOG)
	{
		UpdateData(FROM_DIALOG);
		p_primary_params->m_IN = m_IN;
		p_primary_params->m_TT = m_TT;
	}
	if(wParam == NEW_FILE)
	{
		update_gain(0.0, 0.0);
		UpdateData(TO_DIALOG);
	}
	return TRUE;
}

BOOL CPageAnalyse::OnSetActive()
{
	mp_data_base->change_mode_one(IDM_VAL);
	CPageBase::OnSetActive();
	return TRUE; 
}

void CPageAnalyse::update_gain(double gain, double out)
{
	CString str = format_double(out);
	GetDlgItem(IDC_OUTPUT)->SetWindowText(str);
	str.Format("%5.1f", gain);
	GetDlgItem(IDC_GAIN)->SetWindowText(str);

	int days = mp_data_base->m_limits_one.get_range();
	double gpy = gain *  365.25 / (double)days;
	str.Format("%5.1f", gpy);
	GetDlgItem(IDS_GNY)->SetWindowText(str);
}

BOOL CPageAnalyse::OnInitDialog() 
{
	CPageBase::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CPageAnalyse::OnButProcess() 
{
	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, FROM_DIALOG, 0, TRUE);
	CDlgCalc calc_dlg(this);
	calc_dlg.DoModal();
	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, REQUEST_RESULT, 0, TRUE);
}

