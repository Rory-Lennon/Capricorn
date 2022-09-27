#include "stdafx.h"
#include "Capricorn.h"
#include "SJFileIn.h"
#include "MainFrm.h"

SJFileIn::SJFileIn()
{
	mp_data_base = &(((CCapricornApp*)AfxGetApp())->m_data_base);
	m_date_left = 0;
	m_date_right = 0;
	m_val_left = 0;
	m_val_right = 0;
}

SJFileIn::~SJFileIn()
{}

bool SJFileIn::process_files()
{
	CString str;
   CString wildcard = "..\\Data Files\\*.*";
	CFileFind finder;
	BOOL b_working = finder.FindFile(wildcard);
	while (b_working) 
	{
		b_working = finder.FindNextFile();
		if (finder.IsDots() || finder.IsDirectory()) continue;
		SetFilePath(finder.GetFilePath());
		str = finder.GetFileName();
//		read_file();
		break;
	}
	str.MakeUpper();
	int dot = str.ReverseFind('.');
	int len = str.GetLength() - dot;
	str.Delete(dot, len);

	return true;
}

SJDataSet* SJFileIn::read_file()
{
	CString name(GetFileName());
	name.MakeUpper();
	int dot = name.ReverseFind('.');
	int len = name.GetLength() - dot;
	name.Delete(dot, len);

	int dmy = set_dmy();

	SJDataSet* p_dataset = mp_data_base->create_dataset(name);

	CString single_line;
	SeekToBegin();
	while(ReadString(single_line))
	{
		if(single_line.GetLength() < 5) continue;
		set_markers(single_line);
		SJData* p_data = new SJData;
		CString str_date(single_line.Mid(m_date_left, m_date_right - m_date_left));
		extract_date(dmy, str_date, p_data);
		CString str_val(single_line.Mid(m_val_left, m_val_right - m_val_left));
		extract_val(str_val, p_data);
		p_dataset->ml_data.add_tail(p_data);
//		p_data->trace_data();
//		mp_data_base->ml_pri.add_tail(p_data);
//		TRACE("read_file\n");
	}
	if(mp_data_base->ml_datasets.get_count() <= 1) mp_data_base->set_date_limits();
	return p_dataset;
}

int SJFileIn::set_dmy()
{
	SJData data;

	CString single_line;
	SeekToBegin();
	while(ReadString(single_line))
	{
		set_markers(single_line);
		CString str_date(single_line.Mid(m_date_left, m_date_right - m_date_left));
		extract_date(DDMMYY, str_date, &data);
		if(data.m_day > 12) return DDMMYY;
		if(data.m_month > 12) return MMDDYY;
	}
	return DDMMYY;
}

bool SJFileIn::set_markers(CString &single_line)
{
	int slen = single_line.GetLength();
	int cpos = 0;

	while(cpos < slen)
	{	
		if(!is_space(single_line[cpos]))
		{
			m_date_left = cpos;
			break;
		}
		cpos++;
	}
	while(cpos < slen)
	{
		if(is_space(single_line[cpos]))
		{
			m_date_right = cpos;
			break;
		}
		cpos++;
	}
	while(cpos < slen)
	{
		if(!is_space(single_line[cpos]))
		{
			m_val_left = cpos;
			break;
		}
		cpos++;
	}
	while(cpos < slen)
	{
		if(is_space(single_line[cpos])) 
		{
			m_val_right = cpos;
			break;
		}
		if(cpos == slen - 1) 
		{
			m_val_right = slen;
			break;
		}
		cpos++;
	}
//	TRACE("set_markers %i %i %i %i\n", m_date_left, m_date_right, m_val_left, m_val_right);
	return true;
}

double SJFileIn::string_to_double(CString str)
{
	if(str.GetLength() <= 0) return 0.0f;
	if(str.GetLength() >= 100) return 0.0f;

	LPTSTR p_chars = str.GetBuffer(0);
	double ret_double = (double)atof(p_chars);
	str.ReleaseBuffer();
	return ret_double;
}

int SJFileIn::string_to_int(CString str)
{
	if(str.GetLength() <= 0) return 0;
	if(str.GetLength() >= 100) return 0;

	LPTSTR p_chars = str.GetBuffer(0);
	int ret_int = atoi(p_chars);
	str.ReleaseBuffer();

   return ret_int;
}

void SJFileIn::extract_date(int dmy, CString str_date, SJData* p_data)
{
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
	CString str_day(str_date.Mid(0, dot1));
	CString str_month(str_date.Mid(dot1 + 1, dot2 - dot1 - 1));
	CString str_year(str_date.Mid(dot2 + 1, slen - dot2 - 1));

	day = string_to_int(str_day);
	month = string_to_int(str_month);
	year = string_to_int(str_year);

	p_data->set_date(dmy, day, month, year);
}

int SJFileIn::is_space(int charin)
{
	if((charin == 32) || (charin == 9)) return TRUE;
	else return FALSE;
}

int SJFileIn::is_div(int charin)
{
	if((charin == '.') || (charin == '/') || (charin == '-')) return TRUE;
	else return FALSE;
}

int SJFileIn::is_comma(int charin)
{
	if((charin == ',') || (charin == ' ')) return TRUE;
	else return FALSE;
}

void SJFileIn::extract_val(CString str_input, SJData* p_data)
{
	double val = string_to_double(str_input);
	p_data->set_val(IDM_VAL, val);
}

double SJFileIn::extract_double(CString str_input, CString str_after)
{
	char dqs = 34;
	int pos_char = str_input.Find(str_after);
	if(pos_char <= 0) return 0.0f;
	int dqs_pos_1 = str_input.Find(dqs, pos_char);
	int dqs_pos_2 = str_input.Find(dqs, dqs_pos_1 + 1);
	return string_to_double(str_input.Mid(dqs_pos_1 + 1, dqs_pos_2 - dqs_pos_1 - 1));
}

int SJFileIn::extract_int(CString str_input, CString str_after)
{
	char dqs = 34;
	int pos_char = str_input.Find(str_after);
	if(pos_char <= 0) return 0;
	int dqs_pos_1 = str_input.Find(dqs, pos_char);
	int dqs_pos_2 = str_input.Find(dqs, dqs_pos_1 + 1);
	return string_to_int(str_input.Mid(dqs_pos_1 + 1, dqs_pos_2 - dqs_pos_1 - 1));
}

CString SJFileIn::extract_string(CString str_input, CString str_after)
{
	char dqs = 34;
	int pos_char = str_input.Find(str_after);
	if(pos_char <= 0) return "";
	int dqs_pos_1 = str_input.Find(dqs, pos_char);
	int dqs_pos_2 = str_input.Find(dqs, dqs_pos_1 + 1);
	return str_input.Mid(dqs_pos_1 + 1, dqs_pos_2 - dqs_pos_1 - 1);
}



