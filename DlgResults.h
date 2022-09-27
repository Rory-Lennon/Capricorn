#pragma once

class CDlgResults : public CDialog
{
public:

	CDlgResults();   // standard constructor
	void request_result(int show);
	void update_view();
	//{{AFX_DATA(CDlgResults)
	enum { IDD = IDD_RESULTS };
	double	m_gain;
	int		m_res_num;
	//}}AFX_DATA

	SJDataBase* mp_data_base;
	int m_request;

	//{{AFX_VIRTUAL(CDlgResults)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CDlgResults)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LONG on_params(WPARAM	wParam, LPARAM	lParam);
	afx_msg void OnButUp();
	afx_msg void OnButDown();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
