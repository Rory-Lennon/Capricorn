#pragma once

class SJDataSet;

class CCapThread : public CWinThread
{
	DECLARE_DYNCREATE(CCapThread)

public:

	CCapThread(SJDataBase* p_base, CWnd* p_wnd);
	virtual ~CCapThread();

	SJDataBase* mp_data_base;

//{{AFX_VIRTUAL(CCapThread)
public:
	virtual BOOL	InitInstance();
	virtual int		Run();
//}}AFX_VIRTUAL

protected:

	CCapThread();
	CWnd* mp_wnd;

//{{AFX_MSG(CCapThread)
//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


