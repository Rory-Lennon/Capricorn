#pragma once

#include "ViewBase.h"

class CViewTwo : public CViewBase
{
public:

	CViewTwo();
	virtual SJDataSet* get_dataset();
	virtual int	get_mode();
	virtual void draw_window(CDC& dc);

public:

	//{{AFX_VIRTUAL(CViewTwo)
	//}}AFX_VIRTUAL

	virtual ~CViewTwo();

protected:

	//{{AFX_MSG(CViewTwo)
	afx_msg LONG on_params(WPARAM	wParam, LPARAM	lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

