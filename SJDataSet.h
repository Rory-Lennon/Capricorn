#pragma once

#include "SJPtrList.h"
#include "SJData.h"

class SJDataBase;
class SJDataSet;
typedef SJPtrList<SJDataSet*> PL_DATASET;

class SJDataSet  
{
public:

	SJDataSet(CString name);
	~SJDataSet();
	void add_to_results(SJParamSet* p_pset);
	void request_result(int &request, int show);
	int set_result(int request);
	SJParamSet* create_result();
	void solve_single();
//	void solve_range();
//	void stage2(int m);
//	void stage3(SJDataSet* p_dataset);
//	void stage4(SJDataSet* p_dataset, double r);
//	void stage5(SJDataSet* p_dataset, int b);
	BOOL add_new_point(int day, int month, int year, double val);
	BOOL add_tail(SJData* p_data);
	BOOL add_head(SJData* p_data);
	void undo_add(SJLimits &limits);
	void calc_median(int range);
	void calc_diff(int from, int to);
	void calc_d1(int range);
	void calc_d2(int range);
	void combine_in_d2(SJDataSet* p_otherset, double r2);
	double combine(SJData* p_this, SJData* p_outside, double r1, double r2);
	void calc_flags(int b);
	void draw_trendline(CDC &dc, SJLimits &limits, int which, COLORREF color, int draw_axes, BOOL draw_hairs);
	void draw_selected(CDC &dc, int x, int y);
	void draw_flags(CDC &dc);
	void draw_circle(CDC &dc, int x, int y, COLORREF inside, COLORREF outside);
	void reset_flags();
	void reset_data();
	double calc_gain(double input, double &output);
	void set_working(int which);
	void smooth_data(int which, int range);
	void normalize_data(int which);
	void norm2(int which);
	void stdev(int which);
	void set_val(int which, double val);
	void copy_data(int from, int to);
	void zero_data(int which);
	void set_val_limits(SJLimits &limits, int which);
	void write_data(ofstream* p_file);
	SJData* set_selection(double ratio);
	void calc_stats();
	void set_status();

	double m_maxv;
	double m_minv;
	double m_maxa;
	double m_mina;
	int m_loop;
	int m_numloops;
	int m_break;
	int m_first;
	SJDataBase* mp_data_base;
	CWnd* mp_progress;
	SJParamSet m_params;
	SJParamSet m_work_params;
	SJData* mp_selected;
	SJData* mp_added;
	CString m_name;
	CString m_currency;
	CString m_comment;
	PL_DATA ml_data;
	PL_PSET ml_results;
};



