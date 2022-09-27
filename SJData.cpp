
#include "stdafx.h"
#include "capricorn.h"
#include "SJData.h"

SJData::SJData()
{
	init();
}

SJData::~SJData()
{}

void SJData::init()
{
	m_date = 1;
	m_day = 1;
	m_month = 1;
	m_year = 2000;
	m_flag = FLAG_SELL;
	m_work = 0.0;
	m_weight = 0;
	for(int i = 0; i < 7; i++) m_data[i] = 0;
}

void SJData::set_date(SJData* p_data)
{
	m_date = p_data->m_date;
	m_day = p_data->m_day;
	m_month = p_data->m_month;
	m_year = p_data->m_year;
}

void SJData::set_data(SJData* p_data)
{
	set_date(p_data);
	set_val(IDM_VAL, p_data->get_val(IDM_VAL));
}

void SJData::set_date(int dmy, int day, int month, int year)
{
	if(year < 1900)
	{
		if(year < 50) year += 2000;
		else year += 1900;
	}
	if(dmy == DDMMYY) 
	{
		m_day = day;
		m_month = month;
	}
	if(dmy == MMDDYY) 
	{
		m_day = month;
		m_month = day;
	}
	m_year = year;

	if(m_month > 12) return;

	int year_val = 0;
	year_val = 365 * m_year + (m_year / 4);

	int month_val = 0;
	if(m_year % 4) month_val = g_months[m_month - 1];
	else month_val = g_lmonths[m_month - 1];

	m_date = m_day + month_val + year_val;
}	
	
void SJData::set_date(int index)
{
	m_date = index;

///////// YEAR /////////
	m_year = (m_date / (365 * 4 + 1)) * 4;
	int modyear = m_date % (365 * 4 + 1);	
	m_year += modyear / 365;	
	int modday = modyear % 365;

///////// MONTH /////////
	for(int i = 1; i < 13; i++)
	{
		if(m_year % 4) 
		{	
			if(g_months[i] >= modday)
			{ 
				m_month = i;
				break;
			}
		}
		else
		{
			if(g_lmonths[i] >= modday) 
			{
				m_month = i;
				break;	
			}
		}
	}
	if(m_month > 12) return;

///////// DAY ///////////
	if(m_year % 4) m_day = modday - g_months[m_month - 1];
	else m_day = modday - g_lmonths[m_month - 1];
}

double SJData::get_val(int which)
{
	return m_data[which];
}

void SJData::set_val(int which, double val)
{
	m_data[which] = val;
}

void SJData::trace_data()
{
	TRACE("index %i day %i month %i year %i val %10.4f\n", m_date, m_day, m_month, m_year, get_val(IDM_VAL));
}

CString SJData::get_date()
{
	CString str;
	CString strw;

	strw.Format("%i", m_month);
	str  += strw;

	strw = "/";
	str  += strw;

	strw.Format("%i", m_day);
	str  += strw;

	strw = "/";
	str  += strw;

	strw.Format("%i", m_year);
	str  += strw;

	return str;
}

int SJData::days_in_month()
{
   if ((m_year % 4) == 0) return g_lmonths[m_month] - g_lmonths[m_month - 1];
   else return g_months[m_month] - g_months[m_month - 1];
}

void SJData::write_data(ofstream* p_file)
{
	*p_file << "<DATAPOINT ";
	*p_file << " DATE=";
	write_date(p_file);

	*p_file << " VALUE=";
	write_float(p_file);
	*p_file << " />" << endl;
}

void SJData::write_date(ofstream* p_file)
{
	char dqs = 34;
	*p_file << dqs << m_month << "." << m_day << "." << m_year << dqs;
}

void SJData::write_float(ofstream* p_file)
{
	char dqs = 34;
	*p_file << dqs;

	char szBuffer[15];
	::sprintf(szBuffer, "%15.5f", get_val(IDM_VAL));

	for(int i = 0; i < 15; i++)
	{
		if(szBuffer[i] != ' ') *p_file << szBuffer[i];
	}
	*p_file << dqs;
}