#pragma once

class CCapThread;
class CPageAnalyse;

class CDlgCalc : public CDialog
{
public:

	CDlgCalc(CPageAnalyse* p_page);  

	CCapThread*	mp_thread;
	SJDataBase* mp_data_base;
	CPageAnalyse* mp_page;

	//{{AFX_DATA(CDlgCalc)
	enum { IDD = IDD_CALC };
	CProgressCtrl	m_prog;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CDlgCalc)
public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CDlgCalc)
	virtual BOOL OnInitDialog();
	afx_msg LONG on_progress(WPARAM	wParam, LPARAM	lParam);
	afx_msg void OnButEnd();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

