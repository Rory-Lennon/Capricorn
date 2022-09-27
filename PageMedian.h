#pragma once

#include "PageBase.h"

class CPageMedian : public CPageBase
{

public:

	CPageMedian();   // standard constructor

	//{{AFX_DATA(CPageMedian)
	enum { IDD = IDD_MEDIAN };
	int		m_add_day;
	int		m_add_month;
	int		m_add_year;
	double	m_add_val;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPageMedian)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnSetActive();
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPageMedian)
	virtual BOOL OnInitDialog();
	afx_msg void OnButNewApply();
	afx_msg LONG on_params(WPARAM	wParam, LPARAM	lParam);
	afx_msg void OnButUndo();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

