// stdafx.cpp : source file that includes just the standard includes
//	Capricorn.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "math.h"

const CString format_double(double data)
{
	CString str;

	if(data >= 1e6    ) str.Format("%1.1e", data);
	if(data >= 1.0    )								str.Format("%10.2f", data);
	if((data < 1.0    ) && (data >= 0.1    )) str.Format("%10.3f", data);
	if((data < 0.1    ) && (data >= 0.01   )) str.Format("%10.4f", data);
	if((data < 0.01   ) && (data >= 0.001  )) str.Format("%10.5f", data);
	if((data < 0.001  ) && (data >= 0.0001 )) str.Format("%10.6f", data);
	if((data < 0.0001 ) && (data >= 0.00001)) str.Format("%10.7f", data);
	if( data < 0.00001) str.Format("%1.1e", data);
	if(data == 0.0    ) str.Format("%3.1f", 0.0);

	str.TrimLeft();
	str.Insert(0, "(");
	str += ")";

	return str;
}

const void round_to(double &val, int index)
{
	double expval = pow(10.0, (double)-index);
	val -= fmod(val, expval);
}

