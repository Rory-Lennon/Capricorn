#include "stdafx.h"
#include "capricorn.h"
#include "SJDataSet.h"
#include "MainFrm.h"

SJDataSet::SJDataSet(CString name)
{
	mp_data_base = &(((CCapricornApp*)AfxGetApp())->m_data_base);
	m_name = name;
	mp_selected = NULL;
	m_first = TRUE;
	mp_added = NULL; 
	m_maxv = 0.0;
	m_minv = 0.0;
	m_maxa = 0.0;
	m_mina = 0.0;
	m_loop = 1;
	m_break = FALSE;
}

SJDataSet::~SJDataSet()
{
	ml_data.delete_data();
	ml_results.delete_data();
}

void SJDataSet::draw_trendline(CDC &dc, SJLimits &limits, int which, COLORREF color, int draw_axes, BOOL draw_hairs)
{
	if(draw_axes) limits.draw_value_axes(dc);

	CRect rcdc; 
	dc.GetClipBox(rcdc);
	rcdc.bottom -= INFO_BAR;
	rcdc.right -= CHART_BORDER;

	int height = rcdc.bottom;
	int width = rcdc.right + 1;
	if (width <= 0) width = 1;

	CPen pen(PS_SOLID, 1, color);
	CPen* p_old_pen = dc.SelectObject(&pen);

	int		hair_x = -500;
	int		hair_y = -500;

	int		x = 0;
	int		y = 0;

	int		data_x;
	double	data_y;

/////////////////////////////////////////////////
	int date = 1;
	int mind = mp_data_base->m_limits_one.m_min.m_date;
	int maxd = mp_data_base->m_limits_one.m_max.m_date;
	int		lim_width	= limits.get_range();
	double	lim_height	= limits.m_vwmax - limits.m_vwmin;
/////////////////////////////////////////////////

//	TRACE("left %i right %i top %i bottom %i \n", rcdc.left, rcdc.right, rcdc.top, rcdc.bottom);

	SJData* p_current_data = NULL;			
	int first = TRUE;
	POS pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_current_data = ml_data.get_next(pos);
		date = p_current_data->m_date;

		if((date >= mind) && (date <= maxd)) 
		{
			data_x = p_current_data->m_date - limits.m_min.m_date;
			x = ((int)((double)width * (double)data_x / (double)lim_width));
		
			data_y = p_current_data->get_val(which) - limits.m_vwmin;
			y = (int)((float)height * (1.0 - (data_y / lim_height)));

			if(y <= height)
			{	
				if(first) dc.MoveTo(x, y);
				else dc.LineTo(x, y);
				first = FALSE;

				if((mp_selected == p_current_data) && draw_hairs) 
				{
					hair_x = x;
					hair_y = y;
				}
			}
		}
	}
	if(draw_hairs) draw_selected(dc, hair_x, hair_y);
	dc.SelectObject(p_old_pen);
}

void SJDataSet::draw_flags(CDC &dc)
{
	CRect rcdc; 
	dc.GetClipBox(rcdc);
	rcdc.bottom -= INFO_BAR;
	rcdc.right -= CHART_BORDER;

	int		height = rcdc.bottom;
	int		width = rcdc.right + 1;
	if			(width <= 0) width = 1;

	int		x = 0;
	int		y = 0;

	int		data_x;
	double	data_y;

/////////////////////////////////////////////////
	int		date			= 1;
	double	minv			= mp_data_base->m_limits_two.m_vwmin;
	int		mind			= mp_data_base->m_limits_two.m_min.m_date;
	int		maxd			= mp_data_base->m_limits_two.m_max.m_date;
	int		lim_width	= mp_data_base->m_limits_two.get_range();
	double	lim_height	= mp_data_base->m_limits_two.get_height();
/////////////////////////////////////////////////

//	TRACE("left %i right %i top %i bottom %i \n", rcdc.left, rcdc.right, rcdc.top, rcdc.bottom);
		
	SJData* p_data = NULL;			
	int prev_flag = FLAG_SELL;
	double val = 0.0;
	int index = 0;
	int first = TRUE;
	POS pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);
		date = p_data->m_date;

		if((date >= mind) && (date <= maxd)) 
		{
			val = p_data->get_val(IDM_CT);
			index = p_data->m_date;

			data_x = index - mind;
			x = ((int)((double)width * (double)data_x / (double)lim_width));
		
			data_y = val - minv;
			y = (int)((float)height * (1.0 - (data_y / lim_height)));

			if((p_data->m_flag == FLAG_BUY) && (prev_flag == FLAG_SELL)) 
			{
				draw_circle(dc, x, y, RGB(0, 255, 0), RGB(0, 150, 0));
			}
			if((p_data->m_flag == FLAG_SELL) && (prev_flag == FLAG_BUY)) 
			{
				draw_circle(dc, x, y, RGB(255, 0, 0), RGB(150, 0, 0));
			}
			prev_flag = p_data->m_flag;
		}
	}
}

void SJDataSet::draw_circle(CDC &dc, int x, int y, COLORREF inside, COLORREF outside)
{
	CRect prect;
	prect.left		= x - POINT_SIZE;
	prect.right		= x + POINT_SIZE;
	prect.top		= y - POINT_SIZE;
	prect.bottom	= y + POINT_SIZE;

//	dc.SetBkMode(TRANSPARENT);

	CPen pen_outside(PS_SOLID, 1, outside);
	CPen* p_old_pen = dc.SelectObject(&pen_outside);
	dc.SetBkColor(inside);

	CBrush br(inside);
	CBrush* p_old_br = dc.SelectObject(&br);

	dc.Ellipse(prect);

	dc.SelectObject(p_old_br);
	dc.SelectObject(p_old_pen);
}

void SJDataSet::draw_selected(CDC &dc, int x, int y)
{
//	CPoint apoint(0, 1);
	CRect arect;
	dc.GetClipBox(arect);
	arect.right -= CHART_BORDER;

/////////////////////////////////
	int old_rop = dc.SetROP2(R2_MERGENOTPEN);

	CPen pen_white(PS_SOLID, 2, RGB(150, 150, 150));
	CPen* p_old_pen = dc.SelectObject(&pen_white);

	dc.MoveTo(arect.left, y);
	dc.LineTo(arect.right, y);
	dc.MoveTo(x, arect.top);
	dc.LineTo(x, arect.bottom);

	dc.SetROP2(old_rop);

	dc.SelectObject(p_old_pen);

	draw_circle(dc, x, y, RGB(255, 255, 255), RGB(0, 0, 255));
}

void SJDataSet::set_val_limits(SJLimits &limits, int which)
{
	int first_pass = TRUE;
	SJData* p_data;
	POS pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);
		if((p_data->m_date >= limits.m_min.m_date) && (p_data->m_date <= limits.m_max.m_date))
		{
			if(first_pass) limits.prime_val(p_data, which);
			first_pass = FALSE;
			limits.expand_val_limits(p_data, which);
//			TRACE("which %i\n", which);
//			p_data->trace_data();
		}
	}
	limits.set_tickmarks(which);
}

SJData* SJDataSet::set_selection(double ratio)
{
//	TRACE("ratio %10.5f\n", ratio);

	if(ratio > 1.0) ratio = 1.0;
	if(ratio < 0.0) ratio = 0.0;
/////////////////////////////////////////////////
	int current_date = 1;
	int mind = mp_data_base->m_limits_one.m_min.m_date;
	int maxd = mp_data_base->m_limits_one.m_max.m_date;
	int lim_width = mp_data_base->m_limits_one.get_range();
	if(lim_width <= 0) return NULL;
/////////////////////////////////////////////////
	int select_date = mind + int((double)lim_width * ratio);

	SJData* p_data = NULL;
	SJData* p_last_data = NULL;
	POS pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);
		current_date = p_data->m_date;

		if((current_date >= mind) && (current_date <= maxd)) 
		{		
			if(current_date > select_date) 
			{
				mp_selected = p_last_data;
				return p_last_data;
			}
			p_last_data = p_data;
		}
	}
	mp_selected = p_last_data;
	return p_last_data;
}

BOOL SJDataSet::add_new_point(int day, int month, int year, double val)
{
	SJData* p_new_data = new SJData;
	p_new_data->set_date(DDMMYY, day, month, year);
	p_new_data->set_val(IDM_VAL, val);
	int success = add_tail(p_new_data);
	if(success) 
	{
		mp_data_base->m_limits_one.expand_date_limits(p_new_data);
		mp_data_base->m_limits_two.expand_date_limits(p_new_data);

		mp_added = p_new_data;
	}
	return success;
}

void SJDataSet::undo_add(SJLimits &limits)
{
	if(mp_added)
	{
		if(mp_added == ml_data.get_tail())
		{
			ml_data.delete_tail();
			if(ml_data.get_tail()) limits.m_max.set_date(ml_data.get_tail());
		}
	}
}

void SJDataSet::solve_single()
{
	zero_data(IDM_D2);
	zero_data(IDM_D3);

	SJDataSet* p_dataset;
	POS pos = mp_data_base->ml_datasets.get_head_pos();
	while(pos) 
	{	
		p_dataset = mp_data_base->ml_datasets.get_next(pos);

		p_dataset->calc_median(m_params.m_ML);
		p_dataset->calc_d1(1);

//		p_dataset->m_params.trace_out();

		combine_in_d2(p_dataset, p_dataset->m_params.m_RC);
		copy_data(IDM_D2, IDM_D3);
	}
	calc_flags(m_params.m_BC);
	m_params.m_GN = calc_gain(m_params.m_IN, m_params.m_OUT);

	set_status();
	set_val_limits(mp_data_base->m_limits_two, IDM_C1);
}

////////////////////////////////////////////////
////////////////////////////////////////////////
/*
void SJDataSet::solve_range()
{
///// REMOVE RESULTS ////////////////////
	m_loop = 1;
	m_break = FALSE;
	SJDataSet* p_dataset;
	POS pos = mp_data_base->ml_datasets.get_head_pos();
	while(pos) 
	{
		p_dataset = mp_data_base->ml_datasets.get_next(pos);
		p_dataset->ml_results.delete_data();
	}
/////////////////////////////////////////
	int ML =	mp_data_base->m_range.m_ML;
	int MU =	mp_data_base->m_range.m_MU;

	for(int m = ML; m <= MU; m++) 
	{
		stage2(m);
		if(m_break) break;
	}
}

void SJDataSet::stage2(int m)
{
	m_work_params.m_MU = m;

	zero_data(IDM_D2);
	zero_data(IDM_D3);

	SJDataSet* p_dataset;
	POS pos = mp_data_base->ml_datasets.get_head_pos();
	while(pos) 
	{
		p_dataset = mp_data_base->ml_datasets.get_next(pos);
		stage3(p_dataset);
		if(m_break) break;
	}
	pos = mp_data_base->ml_datasets.get_head_pos();
	while(pos) 
	{
		p_dataset = mp_data_base->ml_datasets.get_next(pos);
		SJParamSet* p_set = new SJParamSet;
		p_set->m_GN		= m_work_params.m_GN;
		p_set->m_ML		= m_work_params.m_ML;
		p_set->m_RC		= p_dataset->m_params.m_RC;
		p_set->m_BC		= m_work_params.m_BC;
		p_dataset->add_to_results(p_set);
	}
//	TRACE("\n");
//	m_work_params.trace_out();
//	TRACE("\n");
	
//	calc_flags(p_dataset->m_params.m_BL);
//	double dOUT = 0.0;
//	m_work_params.m_GN = calc_gain(m_params.m_IN, dOUT);
}

void SJDataSet::stage3(SJDataSet* p_dataset)
{
	int RR = mp_data_base->m_range.m_RR;

	p_dataset->calc_median(m_work_params.m_MU);
	p_dataset->calc_d1(1);
	double rc = 0.0;

	m_first = TRUE;
	for(int rp = -RR; rp <= RR; rp++) 
	{
		rc = (double)rp / (double)RR;
		stage4(p_dataset, rc);
		if(m_break) break;
		if(m_numloops < 1) m_numloops = 1;
		int progress = (int)((double)m_loop * 100.0 / (double)m_numloops);
		mp_progress->PostMessage(MSG_PROGRESS, progress);
	}
	combine_in_d2(p_dataset, p_dataset->m_params.m_RC);
	copy_data(IDM_D2, IDM_D3);
}

void SJDataSet::stage4(SJDataSet* p_dataset, double rc)
{
	m_work_params.m_RC = rc;
	combine_in_d2(p_dataset, rc);

	int BI =		mp_data_base->m_range.m_BI;

	for(int b = BUY_LOWER; b <= BUY_UPPER; b += BI) 
	{
		stage5(p_dataset, b);
		if(m_break) break;
	}
}

void SJDataSet::stage5(SJDataSet* p_dataset, int b)
{
	calc_flags(b);
	m_loop++;

	double dGN = 0.0;
	double dOUT = 0.0;

	dGN = calc_gain(m_params.m_IN, dOUT);

//	TRACE("calc_gain %10.5f\n", dGN);	
	if(m_first) 
	{
		m_work_params.m_GN = dGN;
		m_first = FALSE;
//		TRACE("first %i\n", m_params.m_D2U);
	}
	if(dGN >= m_work_params.m_GN)
	{
		m_work_params.m_GN = dGN;
		m_work_params.m_ML = m_work_params.m_MU;
		p_dataset->m_params.m_RC = m_work_params.m_RC;
		m_work_params.m_BC = b;

//		m_work_params.trace_out();
//		TRACE("gain %10.5f ratio %i flag %i\n", dGN, m_work_params.m_RC, m_params.m_BL);
	}
}
*/

void SJDataSet::calc_flags(int b)
{
	reset_flags();
	
	double dd1 = ((double)b) / 100.0;
	double dd2 = ((double)-b) / 100.0;

	SJData* p_data;
	POS pos;
	int mode = FLAG_SELL;

	int date = 1;
	int mind = mp_data_base->m_limits_one.m_min.m_date;
	int maxd = mp_data_base->m_limits_one.m_max.m_date;

	pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);
		date = p_data->m_date;
		if((date < mind) | (date > maxd)) continue;

		if(p_data->get_val(IDM_D2) > dd1) mode = FLAG_BUY;
		if(p_data->get_val(IDM_D2) < dd2) mode = FLAG_SELL;
		p_data->m_flag = mode;
	}	
}

double SJDataSet::calc_gain(double input, double &output)
{
	SJData* p_data = NULL;
	POS pos;
	double c = input;
	double cb = 0.0;
	double b = 0.0;

	double xc = input;
	double xcb = 0.0;
	double xb = 0.0;

//	double c1 = input;
//	double c1b = 0.0;
//	double b1 = 0.0;

	int prev_flag = FLAG_SELL;

	zero_data(IDM_C1);
	zero_data(IDM_CT);

	pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);

/////////////////////////////////////////////////
		int date = p_data->m_date;
		int mind = mp_data_base->m_limits_one.m_min.m_date;
		int maxd = mp_data_base->m_limits_one.m_max.m_date;
		if((date < mind) | (date > maxd)) continue;
/////////////////////////////////////////////////

//		TRACE("calc_gain double input %10.5f\n", input);

		if(p_data->m_flag == FLAG_BUY)
		{
			if(prev_flag == FLAG_SELL) 
			{
				b	= p_data->get_val(IDM_VAL);
				xb = p_data->get_val(IDM_VAL);

				xc -= m_params.m_TT;

				cb = c;
				xcb = xc;
			}
			if(b != 0.0) c = cb * p_data->get_val(IDM_VAL) / b;
			if(xb != 0.0) xc = xcb * p_data->get_val(IDM_VAL) / xb;
		}
		if(p_data->m_flag == FLAG_SELL)
		{
			if(prev_flag == FLAG_BUY) 
			{
				if((b != 0.0) && (p_data->get_val(IDM_VAL) != 0.0)) c = cb * p_data->get_val(IDM_VAL) / b;
				if((xb != 0.0) && (p_data->get_val(IDM_VAL) != 0.0)) xc = xcb * p_data->get_val(IDM_VAL) / xb;
				xc -= m_params.m_TT;
			}
		}
		p_data->set_val(IDM_C1, c);
		p_data->set_val(IDM_CT, xc);
		prev_flag = p_data->m_flag;
		output = xc;
	}
	return (output - input) * 100.0 / input;
}


void SJDataSet::set_status()
{
	SJData* p_data = NULL;
	SJData* p_info_data = NULL;
	POS pos;

	int date = 1;
	int mind = mp_data_base->m_limits_one.m_min.m_date;
	int maxd = mp_data_base->m_limits_one.m_max.m_date;

	pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);
		date = p_data->m_date;
		if((date < mind) | (date > maxd)) continue;
		p_info_data = p_data;
	}
	if(p_info_data)
	{
		CString str_date = p_info_data->get_date();
		double val = p_info_data->get_val(IDM_CT);
		int rec = p_info_data->m_flag;
		((CMainFrame*)AfxGetMainWnd())->m_status.set_info(str_date, m_name, val, rec);
	}
}

void SJDataSet::combine_in_d2(SJDataSet* p_outside_set, double r2)
{
	SJData* p_this_data;
	SJData* p_outside_data;

	double r1 = 1.0 - fabs(r2);

	zero_data(IDM_D2);

	double result = 0.0;

	POS pos_this = ml_data.get_head_pos();
	POS pos_outside = p_outside_set->ml_data.get_head_pos();

	while(pos_this && pos_outside) 
	{		
		p_this_data = ml_data.get_next(pos_this);
		p_outside_data = p_outside_set->ml_data.get_next(pos_outside);

		while((p_outside_data->m_date < p_this_data->m_date) && pos_outside)
		{
			p_outside_data = p_outside_set->ml_data.get_next(pos_outside);
		}
		while((p_outside_data->m_date > p_this_data->m_date) && pos_this)
		{
			p_this_data->set_val(IDM_D2, result);
			p_this_data = ml_data.get_next(pos_this);
		}
		result = combine(p_this_data, p_outside_data, r1, r2);
		p_this_data->set_val(IDM_D2, result);
	}
//	norm2(IDM_D2);
}

double SJDataSet::combine(SJData* p_this, SJData* p_outside, double r1, double r2)
{
	double d3 = p_this->get_val(IDM_D3) * r1;
	double d1 = p_outside->get_val(IDM_D1) * r2;
	return d3 + d1;
}

void SJDataSet::add_to_results(SJParamSet* p_set)
{
	SJParamSet* p_list_paramset;
	int added = FALSE;
	POS pos = ml_results.get_head_pos();
	while(pos) 
	{
		p_list_paramset = ml_results.get_next(pos);
		double g1 = p_set->m_GN;
		double g2 = p_list_paramset->m_GN;

		if(g1 > g2) 
		{
			ml_results.insert_before(p_list_paramset, p_set);
			added = TRUE;
			break;
		}
	}
	if(added == FALSE) ml_results.add_tail(p_set);
	if(ml_results.get_count() > NUM_RESULTS) ml_results.delete_tail();
}

void SJDataSet::request_result(int &request, int show)
{
	if(request < 0) request = 0;
	int count = ml_results.get_count();
	if(request > count) request = count;
	if((count > 0) && (request == 0)) request = 1;

	SJDataSet* p_dataset;
	POS pos = mp_data_base->ml_datasets.get_head_pos();
	while(pos) 
	{	
		p_dataset = mp_data_base->ml_datasets.get_next(pos);
		p_dataset->set_result(request);
	}
	solve_single();
}

int SJDataSet::set_result(int request)
{
	SJParamSet* p_set = ml_results.get_at(request - 1);
	if(p_set == NULL) return NULL;

	m_params.m_ML	= p_set->m_ML;
	m_params.m_RC	= p_set->m_RC;
	m_params.m_BC	= p_set->m_BC;

	return TRUE;
}

SJParamSet* SJDataSet::create_result()
{
	SJParamSet* p_paramset = new SJParamSet;
	ml_results.add_tail(p_paramset);
	return p_paramset;
}

BOOL SJDataSet::add_tail(SJData* p_new_data)
{
	SJData* p_tail = ml_data.get_tail();
	if(p_tail)
	{
		if(p_new_data->m_date > p_tail->m_date)
		{
			ml_data.add_tail(p_new_data);
			mp_selected = p_new_data;
			return TRUE;
		}
		else 
		{
			delete p_new_data;
			return FALSE;
		}
	}
	else 
	{
		ml_data.add_tail(p_new_data);
		return TRUE;
	}
}

BOOL SJDataSet::add_head(SJData* p_new_data)
{
	SJData* p_head = ml_data.get_head();
	if(p_head)
	{
		if(p_new_data->m_date < p_head->m_date)
		{
			ml_data.add_head(p_new_data);
			mp_selected = p_new_data;
			return TRUE;
		}
		else 
		{
			delete p_new_data;
			return FALSE;
		}
	}
	else 
	{
		ml_data.add_head(p_new_data);
		return TRUE;
	}
}

void SJDataSet::calc_diff(int from, int to)
{
	set_working(from);
	
	SJData* p_data;
	SJData* p_prev_data = NULL;
	double diff = 0.0;
	int start = 0;
	int dt = 0;

	POS pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);
		start++;
		if(start > to)
		{
			if(p_prev_data == NULL) diff = 0.0;
			else 
			{
				dt = p_data->m_date - p_prev_data->m_date;
				if(dt != 0) 
				{
					diff = (p_data->m_work - p_prev_data->m_work) / (double)dt;
				}
			}
		}
		p_data->set_val(to, diff);
		p_prev_data = p_data;
	}
}

void SJDataSet::calc_median(int range)
{
	copy_data(IDM_VAL, IDM_MED);
	smooth_data(IDM_MED, range);
//	calc_d1(1);
//	calc_d2(1);
//	calc_d3(5);
}

void SJDataSet::calc_d1(int range)
{
//	if(range == 0) return;
	calc_diff(IDM_MED, IDM_D1);
	if(range > 1) smooth_data(IDM_D1, range);
//	stdev(IDM_D1);
	norm2(IDM_D1);
//	m_calc_mode = IDM_D1;
}

void SJDataSet::calc_d2(int range)
{
//	if(range == 0) return;
	calc_diff(IDM_D1, IDM_D2);
	if(range > 1) smooth_data(IDM_D2, range);
//	stdev(IDM_D2);
	norm2(IDM_D2);
//	m_calc_mode = IDM_D2;
}

void SJDataSet::reset_data()
{
	reset_flags();

	zero_data(IDM_D1);
	zero_data(IDM_D2);
	zero_data(IDM_C1);

//	((CMainFrame*)AfxGetMainWnd())->m_status.set_info("", -1.0, -1);
}

void SJDataSet::reset_flags()
{
	POS pos = ml_data.get_head_pos();
	while(pos) ml_data.get_next(pos)->m_flag = FLAG_SELL;
}

void SJDataSet::copy_data(int from, int to)
{
	SJData* p_data;
	POS pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);
		p_data->set_val(to, p_data->get_val(from));
	}
}

void SJDataSet::zero_data(int which)
{
	SJData* p_data;
	POS pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);
		p_data->set_val(which, 0.0);
	}
}

void SJDataSet::set_working(int which)
{
	SJData* p_data;
	POS pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);
		p_data->m_work = p_data->get_val(which);
	}
}

void SJDataSet::smooth_data(int which, int range)
{
	double d1 = 0.0;
	double d2 = 0.0;
	int t, cdate, xdate, xspan, rspan;
	POS pos, pos2;
	SJData* p_data;
	PL_DATA pl_xdata;
	SJData* p_xdata;

	set_working(which);

	pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);
		cdate = p_data->m_date;
		pl_xdata.add_head(p_data); // REVERSE LIST
		if(pl_xdata.get_count() > range) pl_xdata.remove_tail();

		d1 = 0.0;
		t = 0;

		pos2 = pl_xdata.get_head_pos();
		while(pos2) 
		{
			p_xdata = pl_xdata.get_next(pos2);
			xdate = p_xdata->m_date;
			xspan = cdate - xdate;
			rspan = range - xspan;
			if(xspan < range)
			{
				t += rspan;
				d1 += p_xdata->m_work * (double)rspan;
			}
		}
		p_data->set_val(which, d1 / (double)t);
	}
}

void SJDataSet::normalize_data(int which)
{
	SJData* p_data;
	POS pos;
	double max = 0.0;
	double maxc = 0.0;

	max = 0.0;
	maxc = 0.0;

	set_working(which);

	pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);
		maxc = fabs(p_data->get_val(which));
		if(maxc > max) max = maxc;
	}
	if (max <= 0.0) return;

	pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);
		p_data->set_val(which, p_data->m_work / max);
	}
}

void SJDataSet::norm2(int which)
{
	SJData* p_data;
	POS pos;
	int count = 0;
	double average = 0.0;

	set_working(which);

	pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);
		count++;
		average += fabs(p_data->get_val(which));
	}
	if(count <= 0) return;
	average /= (double)count;

	pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);
		p_data->set_val(which, p_data->m_work / (average * 5.0));
	}
}

void SJDataSet::stdev(int which)
{
	SJData* p_data;
	POS pos;
	int count = 0;
	double cval = 0.0;

	set_working(which);

	pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);
		count++;
		cval += pow(p_data->m_work, 2.0);
	}
	if(count <= 0) return;
	double dcount = (double)count;
	cval /= dcount;

	pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);
		p_data->set_val(which, p_data->m_work / cval);
	}
}

void SJDataSet::set_val(int which, double val)
{
	SJData* p_data;
	POS pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);
		p_data->set_val(which, val);
	}
}

void SJDataSet::write_data(ofstream* p_file)
{
	char dqs = 34;
	SJData* p_data;

	*p_file << "<DATASET NAME=";
	*p_file << dqs;
	*p_file << m_name;
	*p_file << dqs;
	*p_file << ">" << endl;

	*p_file << "<CURRENCY VALUE=";
	*p_file << dqs;
	*p_file << m_currency;
	*p_file << dqs;
	*p_file << " />" << endl;

	*p_file << "<COMMENT VALUE=";
	*p_file << dqs;
	*p_file << m_comment;
	*p_file << dqs;
	*p_file << " />" << endl;

	m_params.write_params(p_file);

	SJParamSet* p_result;
	POS pos = ml_results.get_head_pos();
	while(pos) 
	{
		p_result = ml_results.get_next(pos);
		p_result->write_result(p_file);
	}
	pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);
		p_data->write_data(p_file);
	}
	*p_file << "</DATASET>" << endl;
}

void SJDataSet::calc_stats()
{
	calc_median(m_params.m_ML);

/////////////////////////////////////////////////
	int mind = mp_data_base->m_limits_one.m_min.m_date;
	int maxd = mp_data_base->m_limits_one.m_max.m_date;
	int range = mp_data_base->m_limits_one.get_range();
	if(range < 1) range = 1;
/////////////////////////////////////////////////

	m_maxv = 0.0;
	m_minv = 0.0;
	m_maxa = 0.0;
	m_mina = 0.0;

	double startv = 0.0;
	double starta = 0.0;
	double endminv = 0.0;
	double endmaxv = 0.0;
	double endmina = 0.0;
	double endmaxa = 0.0;

	double v = 0.0;
	double last_v = 0.0;
	double dv = 0.0;

	double a = 0.0;
	double last_a = 0.0;
	double da = 0.0;

	int date = 0;
	int last_date = 0;
	int first = TRUE;
	SJData* p_data;
	POS pos = ml_data.get_head_pos();
	while(pos) 
	{
		p_data = ml_data.get_next(pos);
		date = p_data->m_date;
		if((date < mind) | (date > maxd)) continue;
		v = p_data->get_val(IDM_VAL);
		a = p_data->get_val(IDM_MED);

		if(first)
		{
			last_v = v;
			last_a = a;
			startv = v;
			starta = a;
			first = FALSE;	
		}
		dv = v - last_v;
		da = a - last_a;

		if(dv > 0.0) endmaxv += dv;
		else endminv += dv;

		if(da > 0.0) endmaxa += da;
		else endmina += da;

		last_a = a;
		last_v = v;
	}
	m_maxv = endmaxv / startv * 100.0;
	m_minv = endminv / startv * 100.0;
	m_maxa = endmaxa / starta * 100.0;
	m_mina = endmina / starta * 100.0;

	m_maxv = m_maxv * 365.25 / (double)range;
	m_minv = m_minv * 365.25 / (double)range;
	m_maxa = m_maxa * 365.25 / (double)range;
	m_mina = m_mina * 365.25 / (double)range;
}

