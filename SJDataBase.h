#pragma once

#include "SJPtrList.h"
#include "SJData.h"
#include "SJLimits.h"
#include "SJParamSet.h"
#include "SJDataSet.h"

class CDlgCalc;

class SJDataBase  
{
public:

	BOOL m_show_hairs;
	SJDataBase();
	~SJDataBase();
	void draw_background(CDC &dc);
	void draw_edges(CDC &dc, int grade);
	void draw_one(CDC &dc, BOOL draw_hairs);
	void draw_two(CDC &dc, BOOL draw_hairs);
	void draw_time(CDC &dc);
	void get_date_limits(SJLimits &limits);
	void set_date_limits(SJLimits &limits);
	void set_date_limits();
	void expand_date_limits(SJData* p_data);
	BOOL add_new_point(int day, int month, int year, double val);
	void undo_add();
	void write_data(ofstream* p_file);
	void solve_range(CWnd* p_progress);
	void solve_single();
	SJDataSet* create_dataset(CString name);
	void new_file();
	void request_result(int &request);
	void change_current(SJDataSet* p_current);
	void change_mode_one(int mode);
	void set_val_limits();
	void stop_calc();
	void move_up();
	void delete_set();
	void set_pointers();
	void reset_analysis();

	SJLimits m_limits_one;
	SJLimits m_limits_two;
	int m_show_median;
	int m_num;
	int m_dmy;
	int m_calc_mode;
	SJParamSet m_range;
	PL_DATASET ml_datasets;
	SJDataSet* mp_primary_dataset;
	SJDataSet* mp_current_dataset;
	int m_mode_one;

protected:

};

typedef SJPtrList<SJDataBase*> PL_DATABASE;