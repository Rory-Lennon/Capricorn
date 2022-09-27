#pragma once

#include "PageBase.h"

class CPageAnalyse : public CPageBase
{

public:

	CPageAnalyse();   // standard constructor
	CDlgCalc* mp_dlg_calc;
	void update_gain(double gain, double out);
	//{{AFX_DATA(CPageAnalyse)
	enum { IDD = IDD_ANALYSE };
	double	m_IN;
	double	m_TT;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPageAnalyse)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnSetActive();
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPageAnalyse)
	virtual BOOL OnInitDialog();
	afx_msg void OnButProcess();
	afx_msg LONG on_params(WPARAM	wParam, LPARAM	lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
