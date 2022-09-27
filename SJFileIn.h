#pragma once

#include "SJPtrList.h"
#include "SJDataSet.h"

class SJFileIn : public CStdioFile
{
public:

							SJFileIn();
							~SJFileIn();

	bool					process_files();
	SJDataSet*			read_file();
	bool					set_markers(CString &str);

protected:

	void					extract_date(int dmy, CString str_date, SJData* p_data);
	void					extract_val(CString str_val, SJData* p_data);
	CString				extract_string(CString str_input, CString str_after);

	double				string_to_double(CString str);
	int					string_to_int(CString str);
	int					set_dmy();
	int					is_space(int charin);
	int					is_div(int charin);
	int					is_comma(int charin);
	double				extract_double(CString str_input, CString str_after);
	int					extract_int(CString str_input, CString str_after);

	SJDataBase*			mp_data_base;
	int					m_date_left;
	int					m_date_right;
	int					m_val_left;
	int					m_val_right;
};


