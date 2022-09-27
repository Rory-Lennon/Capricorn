
#pragma once

class CCtrlStatus : public CStatusBar
{
	DECLARE_DYNCREATE(CCtrlStatus)
public:
						CCtrlStatus();

	//{{AFX_VIRTUAL(CCtrlStatus)
	//}}AFX_VIRTUAL

	virtual			~CCtrlStatus();
	void				set_info(CString str_date, CString str_name, double val, int rec);

	bool				m_show_grid;
	bool				m_show_index;

protected:
	
	//{{AFX_MSG(CCtrlStatus)
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnSize(UINT nType, int cx, int cy);
	afx_msg LONG	on_params(WPARAM	wParam, LPARAM	lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


