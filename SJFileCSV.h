#pragma once

#include "SJFileIn.h"

class SJFileCSV : public SJFileIn
{
public:

			SJFileCSV();
			~SJFileCSV();
	void	extract_datapoint(CString single_line, SJDataSet* p_dataset);
	SJDataSet* read_file();
	void	extract_date(CString str_date, SJData* p_data);
	int	string_to_month(CString str_month);
	BOOL	set_markers(CString &single_line);
	void	set_dmy();
	int	dmy_line(CString single_line);

	int	m_mdy;
	int	m_datesincol;
	int	m_valsincol;
	int	m_last_date;

protected:
};
