// TwoPathRadiowave.h: interface for the CTwoPathRadiowave class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TWOPATHRADIOWAVE_H__9C9F65E4_407E_4A6B_A5D2_4B7C64BADB8E__INCLUDED_)
#define AFX_TWOPATHRADIOWAVE_H__9C9F65E4_407E_4A6B_A5D2_4B7C64BADB8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TwoPathRadiowaveInterface.h"

class CTwoPathRadiowave  : public CTwoPathRadiowaveInterface
{
public:
	CTwoPathRadiowave();
	virtual ~CTwoPathRadiowave();
public:
	int UM2PathWaveCompute(SUMTransPosition tp,SUMReceiveInfo* rp,int Number,int PolarType,SUM2PathResult *res,int &resultNumber);
	double UM2PathWaveCompute_F(double G_d,double G_r,float nReflectFactor, float nDeltaR,float nWavelengh);

};

#endif // !defined(AFX_TWOPATHRADIOWAVE_H__9C9F65E4_407E_4A6B_A5D2_4B7C64BADB8E__INCLUDED_)



