#include "stdafx.h"
#include "capricorn.h"
#include "DlgCalc.h"
#include "CapThread.h"
#include "PageAnalyse.h"

CDlgCalc::CDlgCalc(CPageAnalyse* p_page) : CDialog(CDlgCalc::IDD)
{
	//{{AFX_DATA_INIT(CDlgCalc)
	//}}AFX_DATA_INIT
	mp_data_base = &(((CCapricornApp*)AfxGetApp())->m_data_base);
	mp_page = p_page;
	mp_thread = NULL;
}

void CDlgCalc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCalc)
	DDX_Control(pDX, IDC_PROG, m_prog);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgCalc, CDialog)
	//{{AFX_MSG_MAP(CDlgCalc)
	ON_MESSAGE(MSG_PROGRESS, on_progress)
	ON_BN_CLICKED(IDC_BUT_END, OnButEnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgCalc::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_prog.SetPos(0);
	mp_thread = new CCapThread(mp_data_base, this);
	mp_thread->CreateThread();
	return TRUE;  
}

LONG CDlgCalc::on_progress(WPARAM wParam, LPARAM lParam)
{
//	TRACE("Post %i %i\n", (int)wParam, (int)lParam);
	if(lParam) CDialog::OnCancel();
	if(wParam) m_prog.SetPos(wParam);
	return TRUE;
}

void CDlgCalc::OnButEnd() 
{
	mp_data_base->stop_calc();
}

void CDlgCalc::OnCancel() 
{}
