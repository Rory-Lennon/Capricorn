#include "stdafx.h"
#include "capricorn.h"
#include "PageInfo.h"
#include "MainFrm.h"
#include "SJParamSet.h"

CPageInfo::CPageInfo() : CPageBase(CPageInfo::IDD)
{
	//{{AFX_DATA_INIT(CPageInfo)
	m_comment = _T("");
	m_currency = _T("");
	m_maxa = 0.0;
	m_maxv = 0.0;
	m_mina = 0.0;
	m_minv = 0.0;
	//}}AFX_DATA_INIT
}

void CPageInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageInfo)
	DDX_Text(pDX, IDE_COMMENT, m_comment);
	DDX_Text(pDX, IDE_CURRENCY, m_currency);
	DDX_Text(pDX, IDE_MAXA, m_maxa);
	DDX_Text(pDX, IDE_MAXV, m_maxv);
	DDX_Text(pDX, IDE_MINA, m_mina);
	DDX_Text(pDX, IDE_MINV, m_minv);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageInfo, CPageBase)
	//{{AFX_MSG_MAP(CPageInfo)
	ON_MESSAGE(MSG_PARAMS, on_params)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

LONG CPageInfo::on_params(WPARAM wParam, LPARAM lParam)
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
	CString str;

	if(wParam == FROM_DIALOG)
	{
		UpdateData(FROM_DIALOG);

		p_current_dataset->m_currency = m_currency;
		p_current_dataset->m_comment = m_comment;		
	}
	if(wParam == TO_CURRENT)
	{
		m_maxv = p_current_dataset->m_maxv;
		m_maxa = p_current_dataset->m_maxa;
		m_minv = p_current_dataset->m_minv;
		m_mina = p_current_dataset->m_mina;

		round_to(m_maxv, 1);
		round_to(m_maxa, 1);
		round_to(m_minv, 1);
		round_to(m_mina, 1);

		m_currency = p_current_dataset->m_currency;
		m_comment = p_current_dataset->m_comment;		

		UpdateData(TO_DIALOG);
	}
	if(wParam == NEW_FILE)
	{
		m_currency = "";
		m_comment = "";
		m_maxv = 0.0;
		m_maxa = 0.0;
		m_minv = 0.0;
		m_mina = 0.0;

		UpdateData(TO_DIALOG);
	}
	return TRUE;
}

BOOL CPageInfo::OnSetActive()
{
	mp_data_base->change_mode_one(IDM_VAL);
	CPageBase::OnSetActive();
	return TRUE; 
}

BOOL CPageInfo::OnInitDialog() 
{
	CPageBase::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
}
