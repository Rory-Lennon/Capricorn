#pragma once

class	SJDataBase;
class	SJParamSet;

class CPageBase : public CPropertyPage
{
public:

	CPageBase(UINT val);
	~CPageBase();
	void update_view();

	CRect	m_rect;
	SJDataBase* mp_data_base;
	//{{AFX_DATA(CPageBase)
	enum { IDD = IDD_BASE };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CPageBase)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnSetActive();
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CPageBase)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

