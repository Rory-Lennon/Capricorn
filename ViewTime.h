#pragma once

#include "ViewBase.h"

class CViewTime : public CWnd
{
public:

	CViewTime();
	SJDataBase*		mp_data_base;

public:

	//{{AFX_VIRTUAL(CViewTime)
public:
	//}}AFX_VIRTUAL

	virtual ~CViewTime();

protected:

	//{{AFX_MSG(CViewTime)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

