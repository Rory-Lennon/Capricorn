#pragma once

#include "ViewBase.h"

class CViewOne : public CViewBase
{
public:

	CViewOne();
	virtual ~CViewOne();
	virtual SJDataSet* get_dataset();
	virtual int	get_mode();
	virtual void draw_window(CDC& dc);

public:

	//{{AFX_VIRTUAL(CViewOne)
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CViewOne)
	afx_msg LONG on_params(WPARAM	wParam, LPARAM	lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

