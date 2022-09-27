
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

const	  MSG_TRENDLINE	= WM_USER + 100;
const	  MSG_PROGRESS		= WM_USER + 101;
const	  MSG_PAGE			= WM_USER + 102;
const	  MSG_PARAMS		= WM_USER + 103;

#define BOLD				TVIS_BOLD
#define NOT_BOLD			0

#define DRAW_CHARTS		0
#define DRAW_MATRIX		1

#define BUY_UPPER			100
#define BUY_LOWER			0

#define DIV_WIDTH			40
#define GRID_COLOR		85
#define POINT_SIZE		3
#define HAIR_SIZE		   3
#define TIME_HEIGHT		40

#define MMDDYY				0
#define DDMMYY				1

#define SCALE_DAYS		0
#define SCALE_MONTHS		1
#define SCALE_YEARS		2

/////////////////////////////
#define TO_DIALOG			FALSE
#define FROM_DIALOG		TRUE
#define REQUEST_RESULT	2
#define TO_CURRENT		3
#define UPDATE_LIST		4
#define NEW_FILE			5
/////////////////////////////

#define BAR_SHADE			255
#define INFO_BAR			14
#define DOCK_WIDTH		150
#define MOVE_HEIGHT		0
#define CTRLS_HEIGHT		130
#define LIST_HEIGHT		200
#define FONT_COLOR		255
#define RESULTS_HEIGHT	90
#define CHART_BORDER		60
#define TOP_MARGIN		0.04
#define TL_WIDTH			30

#define TEXT_DOWN			0
#define TEXT_ACROSS		4
#define TXT_GAP			10

#define IDM_VAL			0
#define IDM_D1				1
#define IDM_D2				2
#define IDM_D3				3
#define IDM_MED			4
#define IDM_C1				5
#define IDM_CT				6

#define FLAG_SELL			0
#define FLAG_BUY			1

#define NUM_RESULTS		20

#include "resource.h"       // main symbols

const CString g_smonths[] = 
{
	"",
	"JAN",
	"FEB",
	"MAR",
	"APR",
	"MAY",
	"JUN",
	"JUL",
	"AUG",
	"SEP",
	"OCT",
	"NOV",
	"DEC",
};

#define JAN  1
#define FEB  2
#define MAR  3
#define APR  4 
#define MAY  5
#define JUN  6
#define JUL  7
#define AUG  8
#define SEP  9
#define OCT 10
#define NOV 11
#define DEC 12

const COLORREF g_colors[] = 
{
	RGB(255,   0,   0), // 0  // RED 
	RGB(  0, 255,   0), // 1  // GREEN
	RGB(  0,   0, 255), // 2  // BLUE
	RGB(255, 255,   0), // 3 
	RGB(  0, 255, 255), // 4
	RGB(255,   0, 255), // 5
};

const int g_months[] = 
{
0,   // 0,  // 0
31,  // 31, // JAN
59,  // 28, // FEB
90,  // 31, // MAR
120, // 30, // APR
151, // 31, // MAY
181, // 30, // JUN
212, // 31, // JUL
243, // 31, // AUG
273, // 30, // SEP
304, // 31, // OCT
334, // 30, // NOV
365, // 31  // DEC
};

const int g_lmonths[] = 
{
0,   // 0,  // 0
31,  // 31, // JAN
60,  // 29, // FEB
91,  // 31, // MAR
121, // 30, // APR
152, // 31, // MAY
182, // 30, // JUN
213, // 31, // JUL
244, // 31, // AUG
274, // 30, // SEP
305, // 31, // OCT
335, // 30, // NOV
366  // 31  // DEC
};

#include "SJDataBase.h"
#include "fstream.h"
#include "math.h"
#include "afxpriv.h"

class CCapricornApp : public CWinApp
{
public:

						CCapricornApp();
	BOOL				save_file(CString file_path);
	BOOL				open_file(CString file_path);
	BOOL				import_file(CString file_path);

	SJDataBase		m_data_base;
	HICON				m_app_icon;
	CString			m_last_file;
	int				m_datesincol;
	int				m_valsincol;

	//{{AFX_VIRTUAL(CCapricornApp)
	public:
	virtual			BOOL InitInstance();
	virtual	int	ExitInstance();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

public:

	//{{AFX_MSG(CCapricornApp)
	afx_msg void	OnAppAbout();
	afx_msg void	OnRefreshData();
	afx_msg void	OnFileSaveAs();
	afx_msg void	OnFileSave();
	afx_msg void	OnFileOpen();
	afx_msg void	OnFileNew();
	afx_msg void	OnImport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


