#pragma once

class CViewBase : public CWnd
{
public:

								CViewBase();
	virtual					~CViewBase();
	void						draw_bar(CDC& dc);
	virtual void			draw_window(CDC& dc);
	virtual void			select_point(int x);
	virtual SJDataSet*	get_dataset();
	virtual int				get_mode();

	BOOL						m_show_hairs;

public:

	//{{AFX_VIRTUAL(CViewBase)
public:
protected:
	virtual BOOL			PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

protected:
	
	CRect						m_clip;
	CBitmap*					mp_tl;
	CBitmap					m_bm;
	int						m_TLWidth;
	CBitmap					m_TrafficLightOn;
	CBitmap					m_TrafficLightOff;	
	SJDataBase*				mp_data_base;
	CString					m_str_label;
	CString					m_str_label_value;
	CString					m_str_data;

protected:

	//{{AFX_MSG(CViewBase)
	afx_msg					BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int				OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void			OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void			OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

