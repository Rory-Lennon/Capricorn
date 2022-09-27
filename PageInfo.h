#pragma once

#include "PageBase.h"

class CPageInfo : public CPageBase
{

public:

	CPageInfo();   // standard constructor

	//{{AFX_DATA(CPageInfo)
	enum { IDD = IDD_INFO };
	CString	m_comment;
	CString	m_currency;
	double	m_maxa;
	double	m_maxv;
	double	m_mina;
	double	m_minv;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPageInfo)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnSetActive();
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPageInfo)
	virtual BOOL OnInitDialog();
	afx_msg LONG on_params(WPARAM	wParam, LPARAM	lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

