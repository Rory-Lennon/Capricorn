#include "stdafx.h"
#include "Capricorn.h"
#include "CapThread.h"
#include "SJDataSet.h"

IMPLEMENT_DYNCREATE(CCapThread, CWinThread)

CCapThread::CCapThread(SJDataBase* p_base, CWnd* p_wnd)
{
	mp_data_base	= p_base;
	mp_wnd = p_wnd; 
}

CCapThread::CCapThread()
{}

CCapThread::~CCapThread()
{}

BOOL CCapThread::InitInstance()
{
//	CWinThread::InitInstance();
	SetThreadPriority(THREAD_PRIORITY_BELOW_NORMAL);
	m_bAutoDelete = TRUE;
	return TRUE;
}

BEGIN_MESSAGE_MAP(CCapThread, CWinThread)
	//{{AFX_MSG_MAP(CCapThread)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CCapThread::Run() 
{
	mp_data_base->solve_range(mp_wnd);
	mp_wnd->PostMessage(MSG_PROGRESS, (WPARAM)0, (LPARAM)1);
	return TRUE;
}
