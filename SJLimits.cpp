#include "stdafx.h"
#include "capricorn.h"
#include "SJLimits.h"
#include <math.h>

SJLimits::SJLimits()
{
	m_vinc = 0.0;
	m_vmax = 0.0;
	m_vmin = 0.0;
	m_vwmax = 0.0;
	m_vwmin = 0.0;
	m_base_zero = FALSE;
	m_draw_text = FALSE;
}

void SJLimits::prime_date(SJData* p_data)
{
	m_max.set_date(p_data);
	m_min.set_date(p_data);
}

void SJLimits::prime_val(SJData* p_data, int which)
{
	m_max.set_val(which, p_data->get_val(which));
	m_min.set_val(which, p_data->get_val(which));
}

void SJLimits::expand_date_limits(SJData* p_data)
{
	if(p_data->m_date < m_min.m_date) m_min.set_date(p_data);
	if(p_data->m_date > m_max.m_date) m_max.set_date(p_data);
}

void SJLimits::expand_val_limits(SJData* p_data, int which)
{
	if(p_data->get_val(which) < m_min.get_val(which)) m_min.set_val(which, p_data->get_val(which));
	if(p_data->get_val(which) > m_max.get_val(which)) m_max.set_val(which, p_data->get_val(which));
}

void SJLimits::set_date_limits(SJLimits &limits)
{
	m_min.set_date(&(limits.m_min));
	m_max.set_date(&(limits.m_max));
}

void SJLimits::set_tickmarks(int which)
{
	double min;
	if(m_base_zero) min = min(0.0, m_min.get_val(which));
	else min = m_min.get_val(which);
	double max = m_max.get_val(which);

	m_vinc = 0.1;
	double vrange = max - min;
//	TRACE("min %10.5f m_max.get_val %10.5f trange %10.5f\n", min, m_max.get_val(which), trange);
	if (vrange <= 0.0) 
	{
		m_vsteps = 5;
		m_vmin = 0.0;
		m_vmax = 1.0;
		m_vinc = 0.2;
		m_vwmax = 1.04;
		m_vwmin = -0.04;

		return;
	}
	while((vrange > 1.0) || (vrange <= 0.1))
	{
		if(vrange > 1.0) 
		{
			vrange /= 10.0;
			m_vinc *= 10.0;
		}
		if(vrange <= 0.1) 
		{	
			vrange *= 10.0;
			m_vinc /= 10.0;
		}
//		TRACE("trange m_vinc %10.5f %10.5f\n", trange, m_vinc);
//		TRACE("looping\n");
	}

	m_vmax = round_up(max, m_vinc);
	m_vmin = round_down(min, m_vinc);
	m_vsteps = (int)((m_vmax - m_vmin) / m_vinc);

	if(m_vsteps <= 5) 
	{
		m_vinc /= 2.0;
		m_vmax = round_up(max, m_vinc);
		m_vmin = round_down(min, m_vinc);
		m_vsteps = (int)((m_vmax - m_vmin) / m_vinc);
	}
	m_vwmax = m_vmax + (m_vmax - m_vmin) * TOP_MARGIN;
	m_vwmin = m_vmin - (m_vmax - m_vmin) * TOP_MARGIN;
}

double SJLimits::round_up(double num, double round)
{
	return ceil(num / round) * round;
}

double SJLimits::round_down(double num, double round)
{
	return floor(num / round) * round;
}

void SJLimits::draw_value_axes(CDC &dc)
{
	//// DC /////////////////////////////////////////////////////
	CPen pen(PS_SOLID, 1, RGB(GRID_COLOR, GRID_COLOR, GRID_COLOR));
	CPen* p_old_pen = dc.SelectObject(&pen);

	CFont font;
	font.CreateFont(-10, 0, 0, 0, 0, 0, 0, 0,
								DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
								ANTIALIASED_QUALITY, DEFAULT_PITCH, _T("Verdana Bold"));

	CFont* p_old_font = dc.SelectObject(&font);
	dc.SetTextColor(RGB(FONT_COLOR, FONT_COLOR, FONT_COLOR));
	dc.SetTextAlign(TA_LEFT);

//	int old_rop = dc.SetROP2(R2_MASKPENNOT);
	int old_bkmode = dc.SetBkMode(TRANSPARENT);

	/////////////////////////////////////////////////////////////
	CRect rcdc; 
	dc.GetClipBox(rcdc);
	rcdc.bottom -= INFO_BAR;
	rcdc.right -= CHART_BORDER;
	//////////////////// VERTICAL VAL
	int height = rcdc.bottom;
	int width = rcdc.right;
	if (width <= 0) width = 1;

	double val_range = m_vwmax - m_vwmin;

	int wnmarker;
	for(double vmarker = m_vmin; vmarker <= m_vwmax; vmarker+=m_vinc) 
	{	
		wnmarker = (int)((double)height * (m_vwmax - vmarker) / val_range);
		draw_hline(dc, wnmarker, vmarker);
	}
//	TRACE("y %i m %i d %i\n", years_per_div, months_per_div, days_per_div);
//	TRACE("scale %i\n\n", scale);
	dc.SetBkMode(old_bkmode);
	dc.SelectObject(p_old_pen);
	dc.SelectObject(p_old_font);
}

void SJLimits::draw_date_axes(CDC &dc)
{
	//// DC /////////////////////////////////////////////////////
	CPen pen(PS_SOLID, 1, RGB(GRID_COLOR, GRID_COLOR, GRID_COLOR));
	CPen* p_old_pen = dc.SelectObject(&pen);

	CFont font;
	font.CreateFont(-10, 0, 0, 0, 0, 0, 0, 0,
								DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
								ANTIALIASED_QUALITY, DEFAULT_PITCH, _T("Verdana Bold"));

	CFont* p_old_font = dc.SelectObject(&font);
	dc.SetTextColor(::GetSysColor(COLOR_BTNTEXT));
	dc.SetTextAlign(TA_RIGHT);

//	int old_rop = dc.SetROP2(R2_MASKPENNOT);
	int old_bkmode = dc.SetBkMode(TRANSPARENT);

	/////////////////////////////////////////////////////////////
	CRect rcdc; 
	dc.GetClipBox(rcdc);
	rcdc.right -= (CHART_BORDER - 1);
	int width = rcdc.right;

	//////////////////// HORIZONTAL MONTH
	SJData data(m_min);
	int last_month = 0;
	int last_year = 0;

	int ndays = get_range();

	double nmonths = (double)ndays / 30.0;
	double nyears = (double)ndays / 365.25;
	double trgt_divs = (double)width / (double)DIV_WIDTH;

	int days_per_div = (int)(ndays / trgt_divs) + 1;
	int months_per_div = (int)(nmonths / trgt_divs) + 1;
	int years_per_div = (int)(nyears / trgt_divs) + 1;

	int scale = SCALE_DAYS;
	if(days_per_div > 14) scale = SCALE_MONTHS;
	if(months_per_div == 5) months_per_div = 6;
	if(months_per_div > 6) scale = SCALE_YEARS;

	if(scale == SCALE_DAYS) draw_days(dc, width, days_per_div);
	if(scale == SCALE_MONTHS) draw_months(dc, width, months_per_div);
	if(scale == SCALE_YEARS) draw_years(dc, width, years_per_div);

	dc.SetBkMode(old_bkmode);
	dc.SelectObject(p_old_pen);
	dc.SelectObject(p_old_font);
}

void SJLimits::draw_hline(CDC &dc, int marker, double val)
{
	CRect rcdc; 
	dc.GetClipBox(rcdc);
	rcdc.bottom -= INFO_BAR;
	rcdc.right -= CHART_BORDER;
	CString str;

	if(m_vinc >= 1.0    ) str.Format("%10.0f", val);
	if((m_vinc < 1.0    ) && (m_vinc >= 0.1    )) str.Format("%10.1f", val);
	if((m_vinc < 0.1    ) && (m_vinc >= 0.01   )) str.Format("%10.2f", val);
	if((m_vinc < 0.01   ) && (m_vinc >= 0.001  )) str.Format("%10.3f", val);
	if((m_vinc < 0.001  ) && (m_vinc >= 0.0001 )) str.Format("%10.4f", val);
	if((m_vinc < 0.0001 ) && (m_vinc >= 0.00001)) str.Format("%10.5f", val);
	if( m_vinc < 0.00001) str.Format("%1.1e", val);

	str.TrimLeft();

	dc.TextOut(rcdc.right + 6, marker - 6, str);

	dc.MoveTo(rcdc.right + 2, marker);
	dc.LineTo(rcdc.left - 1, marker);		
}

void SJLimits::draw_days(CDC &dc, int width, int freq)
{
	if(freq <= 0) freq = 1;

	SJData data;
	data.set_date(m_min.m_date - 2);

	int last_month;
	int last_year;	

	SJData end_data;

	int txt_day;
	int txt_month;
	int txt_year;

	int ndays = get_range();
	int hmarker = 0;
	int end_marker = 0;
	int last_h = 0;

	for(int i = m_min.m_date; i < m_max.m_date; i++) 
	{
		last_year = data.m_year;
		last_month = data.m_month;
		data.set_date(i);
	
		txt_day = data.m_day;
		txt_month = -1;
		txt_year = -1;

		if((((data.m_day - 1) % freq) == 0) && ((data.m_day + freq - 1) <= data.days_in_month()))
		{	
			if(data.m_day == 1)
			{
				txt_month = data.m_month;
				if(data.m_month == 1)
				{
					txt_year = data.m_year;
				}
			}
			hmarker = (int)((double)width * (double)(i - m_min.m_date) / (double)ndays);
			draw_vtext(dc, hmarker, txt_day, txt_month, txt_year);
//			TRACE(" draw_vtext d %i m %i y %i\n", txt_day, txt_month, txt_year);
		}		
	}
}

void SJLimits::draw_months(CDC &dc, int width, int freq)
{
	if(freq <= 0) freq = 1;

	SJData data;
	data.set_date(m_min.m_date - 2);

	int last_month;
	int last_year;	

	int txt_day;
	int txt_month;
	int txt_year;

	int ndays = m_max.m_date - m_min.m_date;
	int hmarker = 0;

	for(int i = m_min.m_date; i < m_max.m_date; i++) 
	{
		last_year = data.m_year;
		last_month = data.m_month;
		data.set_date(i);
	
		txt_day = -1;
		txt_month = -1;
		txt_year = -1;

		txt_month = data.m_month;
		if(last_year != data.m_year) txt_year = data.m_year;

		if(last_month != data.m_month)
		{
			if(((data.m_month - 1) % freq) == 0)
			{
				hmarker = (int)((double)width * (double)(i - m_min.m_date) / (double)ndays);
				draw_vtext(dc, hmarker, txt_day, txt_month, txt_year);
			}
		}
	}
}

void SJLimits::draw_years(CDC &dc, int width, int freq)
{
	if(freq <= 0) freq = 1;

	SJData data;
	data.set_date(m_min.m_date - 2);

	int last_year;	

	int txt_day;
	int txt_month;
	int txt_year;

	int ndays = get_range();
	int hmarker = 0;

	for(int i = m_min.m_date; i < m_max.m_date; i++) 
	{
		last_year = data.m_year;
		data.set_date(i);
	
		txt_day = -1;
		txt_month = -1;
		txt_year = data.m_year;

		if(last_year != data.m_year)
		{
			if((data.m_year % freq) == 0)
			{
				hmarker = (int)((double)width * (double)(i - m_min.m_date) / (double)ndays);
				draw_vtext(dc, hmarker, txt_day, txt_month, txt_year);
			}
		}
	}
}

void SJLimits::draw_vline(CDC &dc, int marker)
{
	CRect rcdc; 
	dc.GetClipBox(rcdc);
//	rcdc.bottom -= INFO_BAR;

	dc.MoveTo(marker, 0);
	dc.LineTo(marker, rcdc.bottom);		
}

void SJLimits::draw_vtext(CDC &dc, int marker, int day, int month, int year)
{
	draw_vline(dc, marker);

	if(!m_draw_text) return;

	CRect rcdc; 
	dc.GetClipBox(rcdc);
	rcdc.bottom -= INFO_BAR;

	dc.SetTextAlign(TA_LEFT);

	if(marker > (rcdc.right - DIV_WIDTH)) return;

	int mv = 0;
	int yv = 0;

	if(day > 0) 
	{
		CString str_day;
		str_day.Format("%i", day);
		mv = TXT_GAP;
		dc.TextOut(marker + TEXT_ACROSS, TEXT_DOWN, str_day);
	}
	if(month > 0) 
	{
		CString str_month = g_smonths[month];
		dc.TextOut(marker + TEXT_ACROSS, TEXT_DOWN + mv, str_month);
		yv = TXT_GAP;
	}
	if(year > 0) 
	{
		CString str_year;
		str_year.Format("%i", year);
		str_year = str_year.Mid(2, 2);
		dc.TextOut(marker + TEXT_ACROSS, TEXT_DOWN + yv + mv, str_year);
	}
}

int SJLimits::get_range()
{
	int range = m_max.m_date - m_min.m_date + 1;
	if(range <= 0) range = 1;
	return range;
}

double SJLimits::get_height()
{
	return m_vwmax - m_vwmin;
}
	
void SJLimits::write_data(ofstream* p_file)
{
	*p_file << "<LIMITS START=";
	m_min.write_date(p_file);

	*p_file << " END=";
	m_max.write_date(p_file);

	*p_file << " />" << endl;
}