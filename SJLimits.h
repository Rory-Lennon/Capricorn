#pragma once

class SJLimits  
{
public:

	SJLimits::SJLimits();
	void prime_date(SJData* p_data);
	void prime_val(SJData* p_data, int which);
	void expand_date_limits(SJData* p_data);
	void expand_val_limits(SJData* p_data, int which);
	void set_date_limits(SJLimits &limits);
	void draw_value_axes(CDC &dc);
	void draw_date_axes(CDC &dc);
	void draw_hline(CDC &dc, int marker, double val);
	void draw_vline(CDC &dc, int marker);
	void draw_vtext(CDC &dc, int marker, int day, int month, int year);
	void draw_days(CDC &dc, int width, int freq);	
	void draw_months(CDC &dc, int width, int freq);
	void draw_years(CDC &dc, int width, int freq);
	int get_range();
	double get_height();
	void set_tickmarks(int which);
	double round_up(double num, double round);
	double round_down(double num, double round);
	void write_data(ofstream* p_file);

	int m_draw_text;
	SJData m_max;
	SJData m_min;
	double m_vmax;
	double m_vmin;
	double m_vwmax;
	double m_vwmin;
	double m_vinc;
	int m_vsteps;
	int m_base_zero;
};