#include "stdafx.h"
#include "Capricorn.h"
#include "SJFileProject.h"
#include "MainFrm.h"
#include "SJParamSet.h"

SJFileProject::SJFileProject() 
{
	mp_data_base = &(((CCapricornApp*)AfxGetApp())->m_data_base);
}

SJFileProject::~SJFileProject()
{}

bool SJFileProject::read_file()
{
	CString str = GetFileName();
	str.MakeUpper();
	int dot = str.ReverseFind('.');
	int len = str.GetLength() - dot;
	str.Delete(dot, len);

	CString single_line;
	while(ReadString(single_line))
	{
		if(single_line.GetLength() < 8) continue;
		if(single_line.Find("<LIMITS") >= 0) extract_limits(single_line);
		if(single_line.Find("<RANGE") >= 0) 
		{
			extract_params(single_line, &mp_data_base->m_range);
//			mp_data_base->m_range.trace_out();
		}
		if(single_line.Find("<DATASET") >= 0) extract_dataset(single_line);
	}
	return true;
}

void SJFileProject::extract_limits(CString single_line)
{
	SJLimits limits;
	extract_date(single_line, "START",	&limits.m_min);
	extract_date(single_line, "END",		&limits.m_max);
	mp_data_base->set_date_limits(limits);
}

void SJFileProject::extract_dataset(CString single_line)
{
	CString name = extract_string(single_line, "NAME");
	SJDataSet* p_dataset = mp_data_base->create_dataset(name);

	CString next_line;
	while(ReadString(next_line))
	{
		if(next_line.GetLength() < 5) continue;
		if(next_line.Find("<PARAMETERS") >= 0) extract_params(next_line, &p_dataset->m_params);
		if(next_line.Find("<CURRENCY") >= 0)
		{
			p_dataset->m_currency = extract_string(next_line, "VALUE");
		}
		if(next_line.Find("<COMMENT") >= 0)
		{
			p_dataset->m_comment = extract_string(next_line, "VALUE");
		}
		if(next_line.Find("<RESULT") >= 0) extract_result(next_line, p_dataset);
		if(next_line.Find("<DATAPOINT") >= 0) extract_datapoint(next_line, p_dataset);
		if(next_line.Find("</DATASET") >= 0) return;
	}
}

void SJFileProject::extract_params(CString single_line, SJParamSet* p_params)
{	
	p_params->m_ML		= extract_int(single_line,		"ML");
	p_params->m_MU		= extract_int(single_line,		"MU");
	p_params->m_RC		= extract_double(single_line,	"RC");
	p_params->m_RR		= extract_int(single_line,		"RR");
	p_params->m_BC		= extract_int(single_line,		"BC");
	p_params->m_BI		= extract_int(single_line,		"BI");
	p_params->m_IN		= extract_double(single_line,	"IN");
	p_params->m_TT		= extract_double(single_line,	"TT");
}

void SJFileProject::extract_result(CString single_line, SJDataSet* p_dataset)
{
	SJParamSet* p_params = p_dataset->create_result();
	extract_params(single_line, p_params);
}

void SJFileProject::extract_datapoint(CString single_line, SJDataSet* p_dataset)
{
	SJData* p_data = new SJData;
	extract_date(single_line, "DATE", p_data);
	double val = extract_double(single_line, "VALUE");
	p_data->set_val(IDM_VAL, val);
	p_dataset->add_tail(p_data);
}

void SJFileProject::extract_date(CString single_line, CString str_after, SJData* p_data)
{
	char dqs = 34;
	int pos_char = single_line.Find(str_after);
	if(pos_char <= 0) return;
	int dqs_pos_1 = single_line.Find(dqs, pos_char);
	int dqs_pos_2 = single_line.Find(dqs, dqs_pos_1 + 1);

	CString str_date = single_line.Mid(dqs_pos_1 + 1, dqs_pos_2 - dqs_pos_1 - 1);
//	TRACE("str_date %s\n", str_date);

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
	CString str_month(str_date.Mid(0, dot1));
	CString str_day(str_date.Mid(dot1 + 1, dot2 - dot1 - 1));
	CString str_year(str_date.Mid(dot2 + 1, slen - dot2 - 1));

	day = string_to_int(str_day);
	month = string_to_int(str_month);
	year = string_to_int(str_year);

	p_data->set_date(DDMMYY, day, month, year);
}


