#pragma once

class CCapSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CCapSheet)

public:
						CCapSheet();

	CRect				m_rectPage;
	SJDataBase*		mp_data_base;
	
	//{{AFX_VIRTUAL(CCapSheet)
	public:
	virtual BOOL		OnInitDialog();
	//}}AFX_VIRTUAL

	virtual ~CCapSheet();

protected:

	//{{AFX_MSG(CCapSheet)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

