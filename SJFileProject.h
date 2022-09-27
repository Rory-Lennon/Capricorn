#pragma once

#include "SJFileIn.h"

class SJFileProject : public SJFileIn
{
public:

							SJFileProject();
							~SJFileProject();
	void					extract_params(CString single_line, SJParamSet* p_params);
	void					extract_limits(CString single_line);
	void					extract_result(CString single_line, SJDataSet* p_dataset);
	void					extract_datapoint(CString single_line, SJDataSet* p_dataset);
	void					extract_dataset(CString single_line);
	bool					read_file();
	void					extract_date(CString single_line, CString str_after, SJData* p_data);

protected:
};
