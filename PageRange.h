#pragma once

#include "PageBase.h"

class CPageRange : public CPageBase
{

public:

	CPageRange();   // standard constructor
	void check_dates();

	//{{AFX_DATA(CPageRange)
	enum { IDD = IDD_RANGE };
//	SJListBox	m_dataset_list;
	int		m_end_day;
	int		m_end_month;
	int		m_end_year;
	int		m_start_day;
	int		m_start_month;
	int		m_start_year;
	BOOL		m_base_zero;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPageRange)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPageRange)
	virtual BOOL OnInitDialog();
	afx_msg void OnBaseZero();
	afx_msg void OnButApply();
	afx_msg void OnButLimits();
	afx_msg void OnDeltaposPan(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposZoom(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LONG on_params(WPARAM	wParam, LPARAM	lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


