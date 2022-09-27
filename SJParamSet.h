#pragma once

#include "SJLimits.h"

class SJParamSet
{
public:

				SJParamSet();
	void		trace_out();
	void		write_params(ofstream* p_file);
	void		write_range(ofstream* p_file);
	void		write_result(ofstream* p_file);
	void		set_out(double din, double dout);
	int 		calc_loops(int ndatasets);

	int		m_ML;
	int		m_MU;
	double	m_RC;
	int		m_RR;
	int		m_BC;
	int		m_BI;
	double	m_IN;
	double	m_TT;
	double	m_OUT;
	double	m_GN;
};

typedef SJPtrList<SJParamSet*> PL_PSET;

