#include "stdafx.h"
#include "Capricorn.h"
#include "SJFileCSV.h"
#include "MainFrm.h"
#include "SJParamSet.h"

SJFileCSV::SJFileCSV() 
{
	m_mdy = TRUE;
	m_datesincol = 1;
	m_valsincol = 2;
	m_last_date = 1;

	mp_data_base = &(((CCapricornApp*)AfxGetApp())->m_data_base);
}

SJFileCSV::~SJFileCSV()
{}

SJDataSet* SJFileCSV::read_file()
{
	CString str = GetFileName();
	str.MakeUpper();
	int dot = str.ReverseFind('.');
	int len = str.GetLength() - dot;
	str.Delete(dot, len);

	set_dmy();

	SJDataSet* p_dataset = mp_data_base->create_dataset(str);

	CString single_line;
	SeekToBegin();
	while(ReadString(single_line))
	{
		if(single_line.GetLength() < 8) continue;
		if(single_line.Find("Date") >= 0) continue;
		if(set_markers(single_line)) extract_datapoint(single_line, p_dataset);
	}
	return p_dataset;
}

void SJFileCSV::extract_datapoint(CString single_line, SJDataSet* p_dataset)
{
	SJData* p_data = new SJData;

	CString str_date = single_line.Mid(m_date_left, m_date_right - m_date_left);
	extract_date(str_date, p_data);

	CString str_val = single_line.Mid(m_val_left, m_val_right - m_val_left);
	double val = string_to_double(str_val);
//	TRACE("-%s-\n", str_val);

	p_data->set_val(IDM_VAL, val);

//	p_data->trace_data();

	if(p_data->m_date > m_last_date) p_dataset->add_tail(p_data);
	else p_dataset->add_head(p_data);
	m_last_date = p_data->m_date;
}

void SJFileCSV::set_dmy()
{
	CString single_line;
	SeekToBegin();
	while(ReadString(single_line))
	{
		if(single_line.GetLength() < 8) continue;
		if(single_line.Find("Date") >= 0) continue;
		if(!dmy_line(single_line)) break;
	}
}

int SJFileCSV::dmy_line(CString single_line)
{
	set_markers(single_line);
	CString str_date = single_line.Mid(m_date_left, m_date_right - m_date_left);

	str_date.TrimLeft();
	str_date.TrimRight();

	int dot1 = 0;
	int dot2 = 0;
	int slen = str_date.GetLength();
	int cpos = 0;
	int v1 = 0;
	int v2 = 0;

	while(cpos++ < slen)
	{	
		if(is_div(str_date[cpos]))
		{
			dot1 = cpos;
			break;
		}
	}
	while(cpos++ < slen)
	{
		if(is_div(str_date[cpos]))
		{
			dot2 = cpos;
			break;
		}
	}

	CString str_1(str_date.Mid(0, dot1));
	v1 = string_to_int(str_1);

	if(v1 > 12)
	{
		m_mdy = FALSE;
		return FALSE;
	}

	CString str_2(str_date.Mid(dot1 + 1, dot2 - dot1 - 1));
	v2 = string_to_int(str_2);

	if(v2 > 12)
	{
		m_mdy = TRUE;
		return FALSE;
	}
	return TRUE;
}

void SJFileCSV::extract_date(CString str_date, SJData* p_data)
{
	str_date.TrimLeft();
	str_date.TrimRight();

	int dot1 = 0;
	int dot2 = 0;
	int slen = str_date.GetLength();
	int cpos = 0;
	int day = 0;
	int month = 0;
	int year = 0;

	while(cpos++ < slen)
	{	
		if(is_div(str_date[cpos]))
		{
			dot1 = cpos;
			break;
		}
	}
	while(cpos++ < slen)
	{
		if(is_div(str_date[cpos]))
		{
			dot2 = cpos;
			break;
		}
	}

	CString str_1(str_date.Mid(0, dot1));
	day = string_to_int(str_1);

	CString str_2(str_date.Mid(dot1 + 1, dot2 - dot1 - 1));
	str_2.MakeUpper();

	if(m_mdy == TRUE)
	{
		day = string_to_int(str_2);
		month = string_to_month(str_1);
	}
	else
	{
		day = string_to_int(str_1);
		month = string_to_month(str_2);
	}

	CString str_year(str_date.Mid(dot2 + 1, slen - dot2 - 1));
	year = string_to_int(str_year);
	if((year >  50) && (year < 1000)) year += 1900;
	if((year <= 50) && (year >    0)) year += 2000;

//	TRACE("str_2 %s %i str_1 %s %i str_year %s  %i \n", str_2, month, str_1, day, str_year, year);

	p_data->set_date(DDMMYY, day, month, year);
}

int SJFileCSV::string_to_month(CString str_month)
{
	int month = 0;
	CString str;
	for(int i = 1; i <= 12; i++) 
	{
		str_month.TrimLeft();
		str_month.TrimRight();

		if(str_month == g_smonths[i]) month = i;
		str.Format("%i", i);
		if(str_month == str) month = i;
		str.Insert(0, "0");
		if(str_month == str) month = i;
	}
	return month;
}

BOOL SJFileCSV::set_markers(CString &single_line)
{
	int slen = single_line.GetLength();
	int cpos = 0;
	int divnum = 0;

	int lastwasdiv = TRUE;
	int thisisdiv = TRUE;

	m_date_right = 0;
	m_val_right = 0;

	while(cpos < slen)
	{	
		lastwasdiv = thisisdiv;
		thisisdiv = is_comma(single_line[cpos]);

		if((lastwasdiv == TRUE) && (thisisdiv == FALSE)) 
		{
			divnum++;
			if(divnum == (m_datesincol)) m_date_left = cpos;
			if(divnum == (m_datesincol + 1)) m_date_right = cpos - 1;
			if(divnum == (m_valsincol)) m_val_left = cpos;
			if(divnum == (m_valsincol + 1)) m_val_right = cpos - 1;
		}
		cpos++;
	}
	if(m_date_right == 0) m_date_right = cpos;
	if(m_val_right == 0) m_val_right = cpos;

//	TRACE("set_markers %i %i %i %i\n", m_date_left, m_date_right, m_val_left, m_val_right);
	return TRUE;
}

