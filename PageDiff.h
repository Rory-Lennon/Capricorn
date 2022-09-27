#pragma once

#include "PageBase.h"

class CPageDiff : public CPageBase
{

public:

	CPageDiff();   // standard constructor

	//{{AFX_DATA(CPageDiff)
	enum { IDD = IDD_DIFF };
	CButton	m_rad1;
	CButton	m_rad2;
	CButton	m_rad3;
	//}}AFX_DATA

	void disable_d2();
	void enable_d2();
	void reset();

	int m_mode;

	//{{AFX_VIRTUAL(CPageDiff)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnSetActive();
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPageDiff)
	virtual BOOL OnInitDialog();
	afx_msg void OnButDiff1();
	afx_msg void OnButDiff2();
	afx_msg void OnButDiff3();
	afx_msg LONG on_params(WPARAM	wParam, LPARAM	lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


