#include "stdafx.h"
#include "capricorn.h"
#include "ViewBase.h"

CViewBase::CViewBase()
{
	mp_data_base = &(((CCapricornApp*)AfxGetApp())->m_data_base);
	m_show_hairs = FALSE;
	m_clip.left = 0;
	m_clip.right = 0;
	m_clip.top = 0;
	m_clip.bottom = 0;
}

CViewBase::~CViewBase()
{}

BEGIN_MESSAGE_MAP(CViewBase, CWnd)
	//{{AFX_MSG_MAP(CViewBase)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CViewBase::draw_window(CDC& dc)
{} // VIRTUAL

SJDataSet* CViewBase::get_dataset()
{ 
	return NULL; // VIRTUAL
}

int CViewBase::get_mode()
{
	return 0;
}

BOOL CViewBase::OnEraseBkgnd(CDC* pDC) 
{
	return FALSE;
}

BOOL CViewBase::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs)) return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;

	return TRUE;
}

void CViewBase::draw_bar(CDC& dc)
{
	CRect rcdc; 
	dc.GetClipBox(rcdc);
	rcdc.top = rcdc.bottom - INFO_BAR;
	dc.FillSolidRect(rcdc, RGB(BAR_SHADE, BAR_SHADE, BAR_SHADE));
//////////////////////////////////////////
	CPen penShadow(PS_SOLID, 1, RGB(255, 255, 255));
	CPen *pOldPen = dc.SelectObject(&penShadow);
	dc.MoveTo(rcdc.right,  rcdc.top);
	dc.LineTo(rcdc.left, rcdc.top);
	dc.LineTo(rcdc.left, rcdc.bottom - 1);
//////////////////////////////////////////
	BITMAP bmInfo;
	mp_tl->GetObject(sizeof(bmInfo), &bmInfo);
//////////////////////////////////////////
	CDC dcCompat;
	dcCompat.CreateCompatibleDC(&dc);
	CBitmap* pBitmapOld = dcCompat.SelectObject(mp_tl);
	int pos = INFO_BAR;
	dc.BitBlt(pos, rcdc.top, TL_WIDTH, bmInfo.bmHeight, &dcCompat, 10, 0, SRCCOPY);
	dcCompat.SelectObject(pBitmapOld);
	dcCompat.DeleteDC();
//////////////////////////////////////////
	CPen pen2(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW));
	dc.SelectObject(&pen2);
	dc.MoveTo(INFO_BAR + TL_WIDTH, rcdc.top);
	dc.LineTo(INFO_BAR + TL_WIDTH, rcdc.bottom);
	dc.MoveTo(pos, rcdc.top);
	dc.LineTo(pos, rcdc.bottom);

//	dc.MoveTo(rcdc.left, rcdc.top);
	dc.MoveTo(rcdc.left, rcdc.bottom - 1);
	dc.LineTo(rcdc.right - 1, rcdc.bottom - 1);
	dc.LineTo(rcdc.right - 1, rcdc.top);
	
	dc.SetTextColor(RGB(50, 50, 50));
	int old_bkmode = dc.SetBkMode(TRANSPARENT);

	dc.SetTextAlign(TA_LEFT);

	CFont font;
	font.CreateFont(-10, 0, 0, 0, 0, 0, 0, 0,
								DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
								ANTIALIASED_QUALITY, DEFAULT_PITCH, _T("Arial Bold"));

	CFont* p_old_font = dc.SelectObject(&font);
	rcdc.left += INFO_BAR + TL_WIDTH + INFO_BAR ;
//	rcdc.top += 1;
	UINT uFormat = DT_LEFT;

	if(!m_show_hairs) m_str_data = "";
	dc.DrawText(m_str_label + m_str_label_value + m_str_data, -1, rcdc, uFormat);
	dc.SelectObject(p_old_font);
	dc.SelectObject(pOldPen);
//////////////////////////////////////////
	dc.SetBkMode(old_bkmode);
}

void CViewBase::select_point(int x)
{
	SJData*		p_data = NULL;
	SJDataSet*	p_set = get_dataset();
	if(p_set)
	{
		CRect rcdc; 
		GetClientRect(&rcdc);
		int cursor = x;
		int width = rcdc.right - CHART_BORDER;
		if(width > 0)
		{
			double ratio = (double)cursor / (double)width;
			p_data = p_set->set_selection(ratio);
		}
		m_str_label_value = p_set->m_name;
	}
	if(p_data) 
	{
		CString date;
		date.Format("      %i.%i.%i      ", p_data->m_month, p_data->m_day, p_data->m_year);

		double dval = p_data->get_val(get_mode());
		CString sval = format_double(dval);
		m_str_data.Empty();
		m_str_data = date;
		m_str_data += sval;
//		m_str_label_value = 
//		m_str_date
	}
	Invalidate();
}

int CViewBase::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) return -1;
	
	m_TrafficLightOn.LoadBitmap(IDB_LONG_GREEN);
	m_TrafficLightOff.LoadBitmap(IDB_TL_OFF);
	mp_tl = &m_TrafficLightOff;
	return 0;
}

void CViewBase::OnMouseMove(UINT nFlags, CPoint point) 
{
	select_point(point.x);
	m_show_hairs = TRUE;
	CWnd::OnMouseMove(nFlags, point);
}

void CViewBase::OnPaint() 
{
	CRect rcdc; 
	GetClientRect(&rcdc);

	CPaintDC dc(this); 

	if(m_clip != rcdc) 
	{
		m_bm.DeleteObject();
		m_bm.CreateCompatibleBitmap(&dc, rcdc.right, rcdc.bottom);	
		m_clip = rcdc;
	}

	if(m_show_hairs) mp_tl = &m_TrafficLightOn;
	else mp_tl = &m_TrafficLightOff;

//////////////////////////////////////////
	CDC dcCompat;
	dcCompat.CreateCompatibleDC(&dc);
	CBitmap* pBitmapOld = dcCompat.SelectObject(&m_bm);
	draw_window(dcCompat);
	dc.BitBlt(0, rcdc.top, rcdc.right, rcdc.bottom, &dcCompat, 0, 0, SRCCOPY);
	dcCompat.SelectObject(pBitmapOld);
	dcCompat.DeleteDC();
//////////////////////////////////////////
}


