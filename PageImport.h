#pragma once

#include "PageBase.h"

class CPageImport : public CPageBase
{

public:

	CPageImport();   // standard constructor

	//{{AFX_DATA(CPageImport)
	enum { IDD = IDD_IMPORT };
	int		m_col_date;
	int		m_col_val;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPageImport)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnSetActive();
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPageImport)
	virtual BOOL OnInitDialog();
	afx_msg LONG on_params(WPARAM	wParam, LPARAM	lParam);
	afx_msg void OnMoveUp();
	afx_msg void OnDelete();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
