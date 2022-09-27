#include "stdafx.h"
#include "capricorn.h"
#include "DlgResults.h"
#include "MainFrm.h"

CDlgResults::CDlgResults() //: CDialog(CDlgResults::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgResults)
	m_gain = 0.0;
	m_res_num = 0;
	//}}AFX_DATA_INIT
	mp_data_base = &(((CCapricornApp*)AfxGetApp())->m_data_base);
	m_request = 1;
}

void CDlgResults::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgResults)
	DDX_Text(pDX, IDS_GAIN, m_gain);
	DDX_Text(pDX, IDC_RES_NUM, m_res_num);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgResults, CDialog)
	//{{AFX_MSG_MAP(CDlgResults)
	ON_WM_SIZE()
	ON_MESSAGE(MSG_PARAMS, on_params)
	ON_BN_CLICKED(IDC_BUT_UP, OnButUp)
	ON_BN_CLICKED(IDC_BUT_DOWN, OnButDown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

LONG CDlgResults::on_params(WPARAM wParam, LPARAM lParam)
{
////////////////
	SJDataSet* p_primary_dataset = mp_data_base->mp_primary_dataset;
	if(p_primary_dataset == NULL) return TRUE;
	SJParamSet* p_primary_params = &p_primary_dataset->m_params;
////////////////

	if(wParam == TO_DIALOG)
	{
		double gain = p_primary_params->m_GN;
		int days = mp_data_base->m_limits_one.get_range();
		double gpy = gain *  365.25 / (double)days;
		m_gain = gpy;
		round_to(m_gain, 1);
		m_res_num = m_request;

		UpdateData(TO_DIALOG);
	}
	if(wParam == REQUEST_RESULT)
	{
		request_result(TRUE);
	}
	if(wParam == NEW_FILE)
	{
		m_gain = 0.0;
		UpdateData(TO_DIALOG);
	}
	return TRUE;
}

BOOL CDlgResults::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	request_result(TRUE);
	return TRUE;  
}

void CDlgResults::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
}

void CDlgResults::update_view()
{
	((CMainFrame*)AfxGetMainWnd())->update_views();
}

void CDlgResults::OnButUp() 
{
	m_request++;
	request_result(TRUE);
}

void CDlgResults::OnButDown() 
{
	m_request--;
	request_result(TRUE);	
}

void CDlgResults::request_result(int show)
{
	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, FROM_DIALOG, 0, TRUE);
	mp_data_base->request_result(m_request);
	if(show) update_view();
	AfxGetMainWnd()->SendMessageToDescendants(MSG_PARAMS, TO_DIALOG, 0, TRUE);
}
