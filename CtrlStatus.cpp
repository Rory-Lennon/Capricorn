#include "stdafx.h"
#include "Capricorn.h"
#include "CtrlStatus.h"

IMPLEMENT_DYNCREATE(CCtrlStatus, CStatusBar)

CCtrlStatus::CCtrlStatus()
{
	m_show_grid  = false;
	m_show_index = false;
}

CCtrlStatus::~CCtrlStatus()
{}

BEGIN_MESSAGE_MAP(CCtrlStatus, CStatusBar)
	//{{AFX_MSG_MAP(CCtrlStatus)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(MSG_PARAMS, on_params)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

LONG CCtrlStatus::on_params(WPARAM wParam, LPARAM lParam)
{
	if(wParam == NEW_FILE)
	{
		set_info("", "", 0.0, -1);
	}
	return TRUE;
}

static UINT indicators[] =
{
	ID_SEPARATOR,	
//	IDS_LEFT,
	IDS_DATE,
	IDS_CURRENCY,
	IDS_CONVERSION,
	IDS_RECOMMEND,
};

int CCtrlStatus::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatusBar::OnCreate(lpCreateStruct) == -1) return -1;
	
	SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

//	SetStyle(0, SBPS_STRETCH);
	SetPaneInfo(0, ID_SEPARATOR, SBPS_STRETCH, 50);


//	CRect rect;
//	GetItemRect(CommandToIndex(IDS_COVERED), &rect);
//	SetWindowText("Cyclops Ready");

//| PBS_SMOOTH

	return 0;
}

void CCtrlStatus::OnSize(UINT nType, int cx, int cy) 
{
	CStatusBar::OnSize(nType, cx, cy);
}

void CCtrlStatus::set_info(CString str_date, CString str_name, double val, int rec)
{
	SetPaneText(CommandToIndex(IDS_DATE), str_date);
	SetPaneText(CommandToIndex(IDS_CURRENCY), str_name);
	CString sval = format_double(val);
	if(val < 0.0) sval = "";
	SetPaneText(CommandToIndex(IDS_CONVERSION), sval);
	CString rstr;
	if(rec == FLAG_SELL) rstr = "LOW";
	if(rec == FLAG_BUY) rstr = "HIGH";
	if(rec < 0) rstr = "";
	SetPaneText(CommandToIndex(IDS_RECOMMEND), rstr);
}
