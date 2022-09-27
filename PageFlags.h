#pragma once

#include "PageBase.h"

class CPageFlags : public CPageBase
{

public:

	CPageFlags();   // standard constructor

	//{{AFX_DATA(CPageFlags)
	enum { IDD = IDD_FLAGS };
	CSliderCtrl	m_slider_resolution;
	int		m_ML;
	int		m_MU;
	int		m_MC;
	int		m_BC;
	double	m_RC;
	CButton	m_rad_coarse;
	CButton	m_rad_fine;
	double	m_resolution;
	//}}AFX_DATA

	int		m_BI;

	//{{AFX_VIRTUAL(CPageFlags)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnSetActive();
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPageFlags)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LONG on_params(WPARAM	wParam, LPARAM	lParam);
	afx_msg void OnButUpdate();
	afx_msg void OnReleasedcaptureSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCoarse();
	afx_msg void OnFine();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

