#pragma once

#include "SJPtrList.h"
#include "fstream.h"
		
class SJLimits;

class SJData  
{
public:

	SJData();
	~SJData();

	void init();
	void set_date(SJData* p_data);
	void set_data(SJData* p_data);
	void set_date(int dmy, int day, int month, int year);
	void set_date(int index);
	void trace_data();
	double get_val(int which);
	void set_val(int which, double val);
	CString get_date();
	int days_in_month();	
	void write_data(ofstream* p_file);
	void write_date(ofstream* p_file);
	void write_float(ofstream* p_file);

	int m_date;
	int m_year;
	int m_day;
	int m_month;
	int m_flag;
	int m_weight;
	double m_work;

protected:

	double m_data[7];
};

typedef SJPtrList<SJData*> PL_DATA;

