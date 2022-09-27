#include "stdafx.h"
#include "Capricorn.h"
#include "SJParamSet.h"

SJParamSet::SJParamSet()
{	
	m_ML	=	20;
	m_MU	=	40;
	m_RC	=	0.0;
	m_RR	=	20;
	m_BC	=	60;
	m_BI	=	10;
	m_IN	=	1000.0;
	m_TT 	=	5.0;
	m_OUT =	0.0;
	m_GN	=	0.0;
}

void SJParamSet::trace_out()
{
	TRACE("ML %i MU %i RC %6.2f RR %i BC %i BI %i GN %10.5f\n", m_ML, m_MU, m_RC, m_RR, m_BC, m_BI, m_GN);
}

void SJParamSet::set_out(double din, double dout)
{
	m_IN	= din;
	m_OUT = dout;
	m_GN	= (dout - din) * 100.0 / din;
}

int SJParamSet::calc_loops(int ndatasets)
{
	int MD = m_MU - m_ML + 1;
	if(MD < 1) MD = 1;

	if(m_RR < 1) m_RR = 1;
	int RD = (m_RR * 2) + 3;

	int BD = (BUY_UPPER - BUY_LOWER) / m_BI;
	if(BD < 1) BD = 1;

	if(ndatasets < 1) ndatasets = 1;

	return MD * RD * BD * ndatasets;
}

void SJParamSet::write_params(ofstream* p_file)
{
	char dqs = 34;

	*p_file << "<PARAMETERS ";

	*p_file << " ML=";
	*p_file << dqs << m_ML << dqs;

	*p_file << " RC=";
	*p_file << dqs << m_RC << dqs;

	*p_file << " BL=";
	*p_file << dqs << m_BC << dqs;

	*p_file << " IN=";
	*p_file << dqs << m_IN << dqs;

	*p_file << " TT=";
	*p_file << dqs << m_TT << dqs;

	*p_file << " GN=";
	*p_file << dqs << m_GN << dqs;

	*p_file << " />" << endl;
}

void SJParamSet::write_range(ofstream* p_file)
{
	char dqs = 34;

	*p_file << "<RANGE ";

	*p_file << " ML=";
	*p_file << dqs << m_ML << dqs;

	*p_file << " MU=";
	*p_file << dqs << m_MU << dqs;

	*p_file << " RR=";
	*p_file << dqs << m_RR << dqs;

	*p_file << " BL=";
	*p_file << dqs << m_BC << dqs;

	*p_file << " BI=";
	*p_file << dqs << m_BI << dqs;

	*p_file << " />" << endl;
}

void SJParamSet::write_result(ofstream* p_file)
{
	char dqs = 34;

	*p_file << "<RESULT";

	*p_file << " ML=";
	*p_file << dqs << m_ML << dqs;

	*p_file << " RC=";
	*p_file << dqs << m_RC << dqs;

	*p_file << " BC=";
	*p_file << dqs << m_BC << dqs;

	*p_file << " GN=";
	*p_file << dqs << m_GN << dqs;
	
	*p_file << " />" << endl;
}


