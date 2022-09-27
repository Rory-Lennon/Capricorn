#include "stdafx.h"
#include "capricorn.h"
#include "ViewOne.h"

CViewOne::CViewOne() : CViewBase()
{
	m_str_label = "DATA SET:    ";
}

CViewOne::~CViewOne()
{}

SJDataSet* CViewOne::get_dataset()
{
	return mp_data_base->mp_current_dataset;
}

int CViewOne::get_mode()
{
	return mp_data_base->m_mode_one;
}

BEGIN_MESSAGE_MAP(CViewOne, CViewBase)
	//{{AFX_MSG_MAP(CViewOne)
	ON_MESSAGE(MSG_PARAMS, on_params)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

LONG CViewOne::on_params(WPARAM wParam, LPARAM lParam)
{
////////////////
	SJDataSet* p_current_dataset = mp_data_base->mp_current_dataset;
	if(p_current_dataset == NULL) 
	{
		m_str_label_value = "";
		return TRUE;
	}
////////////////
	if(wParam == TO_CURRENT)
	{
		m_str_label_value = p_current_dataset->m_name;
	}
	return TRUE;
}

void CViewOne::draw_window(CDC& dc)
{
	mp_data_base->draw_one(dc, m_show_hairs);
	draw_bar(dc);
}