#include "stdafx.h"
#include "capricorn.h"
#include "ViewTwo.h"

CViewTwo::CViewTwo() : CViewBase()
{
	m_str_label = "INVESTMENT HISTORY:    ";
}

CViewTwo::~CViewTwo()
{
}

BEGIN_MESSAGE_MAP(CViewTwo, CViewBase)
	//{{AFX_MSG_MAP(CViewTwo)
	ON_MESSAGE(MSG_PARAMS, on_params)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

SJDataSet* CViewTwo::get_dataset()
{
	return mp_data_base->mp_primary_dataset;
}

int CViewTwo::get_mode()
{
	return IDM_CT;
}

void CViewTwo::draw_window(CDC& dc)
{
	((CCapricornApp*)AfxGetApp())->m_data_base.draw_two(dc, m_show_hairs);
	draw_bar(dc);
}

LONG CViewTwo::on_params(WPARAM wParam, LPARAM lParam)
{
////////////////
	SJDataSet* p_primary_dataset = mp_data_base->mp_primary_dataset;
	if(p_primary_dataset == NULL) 
	{
		m_str_label_value = "";
		return TRUE;
	}
////////////////
	if(wParam == TO_CURRENT)
	{
		m_str_label_value = p_primary_dataset->m_name;
	}
	return TRUE;
}