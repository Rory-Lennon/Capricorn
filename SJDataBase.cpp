#include "stdafx.h"
#include "capricorn.h"
#include "SJDataBase.h"
#include "MainFrm.h"
#include "SJFileIn.h"

SJDataBase::SJDataBase()
{
	m_show_median = TRUE;
	m_calc_mode = IDM_D1;
	m_mode_one = IDM_VAL;
	mp_current_dataset = NULL;
	mp_primary_dataset = NULL;
	m_show_hairs = FALSE;
}

SJDataBase::~SJDataBase()
{
	ml_datasets.delete_data();
}

void SJDataBase::draw_one(CDC &dc, BOOL draw_hairs)
{
	draw_background(dc);
	draw_edges(dc, 3);
	
	if(mp_primary_dataset == NULL) return;
	if(mp_current_dataset == NULL) return;

//	m_limits_one.draw_value_axes(dc);

	m_limits_one.m_draw_text = FALSE;
	m_limits_one.draw_date_axes(dc);

	if(mp_current_dataset == NULL) return;

	switch(m_mode_one)
   {
   case IDM_VAL: 
		if(m_show_median) mp_current_dataset->draw_trendline(dc, m_limits_one, IDM_MED, RGB(255, 0, 0), FALSE, FALSE);
		mp_current_dataset->draw_trendline(dc, m_limits_one, IDM_VAL, RGB(0, 100, 255), TRUE, draw_hairs);
	break;
   case IDM_D1: 
		mp_current_dataset->draw_trendline(dc, m_limits_one, IDM_D1, RGB(0, 200, 255), TRUE, draw_hairs);
	break;
   case IDM_D2: 
		mp_current_dataset->draw_trendline(dc, m_limits_one, IDM_D2, RGB(200, 0, 255), TRUE, draw_hairs);
	break;
   case IDM_D3: 
		mp_current_dataset->draw_trendline(dc, m_limits_one, IDM_D3, RGB(50, 0, 255), TRUE, draw_hairs);
	break;
	}
}

void SJDataBase::draw_two(CDC &dc, BOOL draw_hairs)
{
	draw_background(dc);	
	draw_edges(dc, 2);

	if(mp_primary_dataset == NULL) return;

	m_limits_one.m_draw_text = FALSE;
	m_limits_one.draw_date_axes(dc);

	mp_primary_dataset->draw_trendline(dc, m_limits_two, IDM_C1, RGB(125, 125, 125), TRUE, FALSE);
	mp_primary_dataset->draw_trendline(dc, m_limits_two, IDM_CT, RGB(  0, 200, 255), FALSE, draw_hairs);
	mp_primary_dataset->draw_flags(dc);
}

void SJDataBase::draw_time(CDC &dc)
{
	if(mp_primary_dataset == NULL) return;

//	draw_edges(dc, FALSE);
	m_limits_one.m_draw_text = TRUE;
	m_limits_one.draw_date_axes(dc);
}

void SJDataBase::draw_background(CDC &dc)
{
	CRect rcdc; 
	dc.GetClipBox(rcdc);
	dc.FillSolidRect(rcdc, RGB(0, 0, 0));
	rcdc.right -= CHART_BORDER;
	int width = rcdc.right + 1;
	if (width <= 0) width = 1;

	if(mp_primary_dataset == NULL) return;

/////////////////////////////////////////////////
	int		date = 1;
	int		mind = m_limits_one.m_min.m_date;
	int		maxd = m_limits_one.m_max.m_date;
	int		lim_width = m_limits_one.get_range();

	int		marker_x = 1;
	int		data_x = 1;

	CRect		rcbox(rcdc);
	CBrush	br(RGB(65, 65, 20));

//	TRACE("left %i right %i top %i bottom %i \n", rcdc.left, rcdc.right, rcdc.top, rcdc.bottom);

	SJData* p_data = NULL;			
	int prev_flag = FLAG_SELL;
	POS pos = mp_primary_dataset->ml_data.get_head_pos();
	while(pos) 
	{
		p_data = mp_primary_dataset->ml_data.get_next(pos);
		date = p_data->m_date;

		if((date >= mind) && (date <= maxd)) 
		{
			data_x = p_data->m_date - m_limits_one.m_min.m_date;
			marker_x = (int)(((double)width * (double)data_x / (double)lim_width));

			if((p_data->m_flag == FLAG_BUY) && (prev_flag == FLAG_SELL)) rcbox.left = marker_x;
			if((p_data->m_flag == FLAG_SELL) && (prev_flag == FLAG_BUY)) 
			{
				rcbox.right = marker_x + 1;
				dc.FillRect(&rcbox, &br);
			}
			prev_flag = p_data->m_flag;
		}
	}
	if(prev_flag == FLAG_BUY)
	{
		rcbox.right = marker_x + 1;
		dc.FillRect(&rcbox, &br);
	}
}

void SJDataBase::draw_edges(CDC &dc, int grade)
{
	CRect rcdc; 
	dc.GetClipBox(rcdc);
	rcdc.bottom -= INFO_BAR;

	int color[4];
	for (int i = 0; i < 4; i++) color[i] = 0;
	color[grade] = 1;

	CRect rcleft(rcdc);
	rcleft.left = rcdc.right - CHART_BORDER + 1;
	rcleft.bottom = rcdc.bottom;

	CRect rcc(rcleft);

	if(grade)
	{

		int shade = 0;
		int steps = 80;
		double hw = (double)rcleft.bottom / (double)steps;
		int hc = 0;
		for(int i = 0; i < steps; i++)
		{
			rcc.top = (int)(hw * (double)i);
			rcc.bottom = (int)(hw * (double)(i + 1));
			shade = (int)((1.0 - ((double)i / (double)steps)) * 200.0);
			dc.FillSolidRect(rcc, RGB(shade * color[1], shade * color[2], shade * color[3]));
		}
	}
	CRect rcbot(rcdc);
	rcbot.top = rcleft.bottom + 1;

	CPen pen(PS_SOLID, 1, RGB(FONT_COLOR, FONT_COLOR, FONT_COLOR));
	CPen* p_old_pen = dc.SelectObject(&pen);

	dc.MoveTo(rcleft.left, 0);
	dc.LineTo(rcleft.left, rcbot.top);

	dc.SelectObject(p_old_pen);
}

void SJDataBase::get_date_limits(SJLimits &limits)
{
	limits.set_date_limits(m_limits_one);
}

void SJDataBase::set_date_limits(SJLimits &limits)
{
	m_limits_one.set_date_limits(limits);
	m_limits_two.set_date_limits(limits);

	if(mp_current_dataset == NULL) return;
	mp_current_dataset->calc_stats();
	set_val_limits();
}

void SJDataBase::expand_date_limits(SJData* p_data)
{
	m_limits_one.expand_val_limits(p_data, m_mode_one);

	m_limits_one.expand_date_limits(p_data);
	m_limits_two.expand_date_limits(p_data);
}

void SJDataBase::set_date_limits()
{
	if(mp_current_dataset == NULL) return;

	SJData* p_data = mp_current_dataset->ml_data.get_head();
	if(p_data != NULL) 
	{
		m_limits_one.prime_date(p_data);		
		POS pos = mp_current_dataset->ml_data.get_head_pos();
		while(pos) m_limits_one.expand_date_limits(mp_current_dataset->ml_data.get_next(pos));
	}
	m_limits_two.set_date_limits(m_limits_one);

	if(mp_current_dataset == NULL) return;
	mp_current_dataset->calc_stats();
	reset_analysis();
}

BOOL SJDataBase::add_new_point(int day, int month, int year, double val)
{
	if(mp_current_dataset == NULL) return FALSE;
	int success = mp_current_dataset->add_new_point(day, month, year, val);
	return success;
}

void SJDataBase::undo_add()
{
	if(mp_current_dataset == NULL) return;
	mp_current_dataset->undo_add(m_limits_one);
}

void SJDataBase::solve_range(CWnd* p_progress)
{
	if(mp_primary_dataset == NULL) return;
	mp_primary_dataset->mp_progress = p_progress;
	int ndatasets = ml_datasets.get_count();
	mp_primary_dataset->m_numloops = m_range.calc_loops(ndatasets);
//	mp_primary_dataset->solve_range();
}

void SJDataBase::solve_single()
{
	if(mp_primary_dataset == NULL) return;
	mp_primary_dataset->solve_single();
}

SJDataSet* SJDataBase::create_dataset(CString name)
{
	SJDataSet* p_dataset = new SJDataSet(name);
	ml_datasets.add_tail(p_dataset);
	set_pointers();
	return p_dataset;
}

void SJDataBase::set_pointers()
{
	SJDataSet* p_dataset = NULL;
	int current_found = FALSE;
	int i = 0;
	POS pos = ml_datasets.get_head_pos();
	while(pos) 
	{
		i++;
		p_dataset = ml_datasets.get_next(pos);

		if(i == 1) mp_primary_dataset = p_dataset;
		if(mp_current_dataset == p_dataset) current_found = TRUE;
	}
	if(!current_found) mp_current_dataset = mp_primary_dataset;

	if(i == 0)
	{
		mp_primary_dataset = NULL;
		mp_current_dataset = NULL;
	}
}

void SJDataBase::reset_analysis()
{
	if(mp_primary_dataset == NULL) return;
	mp_primary_dataset->zero_data(IDM_C1);
	mp_primary_dataset->zero_data(IDM_CT);
	mp_primary_dataset->zero_data(IDM_MED);
	mp_primary_dataset->reset_flags();
	set_val_limits();
}

void SJDataBase::write_data(ofstream* p_file)
{
	char dqs = 34;

	*p_file << "<?xml version=" << dqs << "1.0" << dqs << "?>" << endl;
	*p_file << "<CYCLOPSMM>" << endl;
	m_limits_one.write_data(p_file);
	m_range.write_range(p_file);

	SJDataSet* p_dataset;
	POS pos = ml_datasets.get_head_pos();
	while(pos) 
	{
		p_dataset = ml_datasets.get_next(pos);
		p_dataset->write_data(p_file);
	}
	*p_file << "</CYCLOPSMM>" << endl;
}

void SJDataBase::new_file()
{
	mp_current_dataset = NULL;
	mp_primary_dataset = NULL;
	ml_datasets.delete_data();
	set_pointers();
}

void SJDataBase::request_result(int &request)
{
	if(mp_primary_dataset == NULL) return;
	mp_primary_dataset->request_result(request, FALSE);
}

void SJDataBase::change_current(SJDataSet* p_current)
{
	mp_current_dataset = p_current;
	if(mp_current_dataset == NULL) return;
	mp_current_dataset->calc_stats();
	mp_current_dataset->set_val_limits(m_limits_one, m_mode_one);
}

void SJDataBase::change_mode_one(int mode)
{
	m_mode_one = mode;
	if(mp_current_dataset == NULL) return;
	mp_current_dataset->set_val_limits(m_limits_one, m_mode_one);
}

void SJDataBase::set_val_limits()
{
	if(mp_primary_dataset == NULL) return;
	mp_primary_dataset->set_val_limits(m_limits_two, IDM_C1);

	if(mp_current_dataset == NULL) return;
	mp_current_dataset->set_val_limits(m_limits_one, m_mode_one);
}

void SJDataBase::stop_calc()
{
	if(mp_primary_dataset == NULL) return;
	mp_primary_dataset->m_break = TRUE;
}

void SJDataBase::move_up()
{
	if(mp_current_dataset == NULL) return;
	ml_datasets.move_up(mp_current_dataset);
	set_pointers();
	reset_analysis();
}

void SJDataBase::delete_set()
{
	if(mp_current_dataset == NULL) return;
	ml_datasets.delete_element(mp_current_dataset);
	set_pointers();
	reset_analysis();
}

