#pragma once


#ifndef INCLUDED_CatmullRomcurve_CURVE_EVALUATOR_H
#define INCLUDED_CatmullRomcurve_CURVE_EVALUATOR_H

#pragma warning(disable : 4786)  

#include "CurveEvaluator.h"

class CatmullRomcurveevaluator
	: public CurveEvaluator
{
public:
	void evaluateCurve(const std::vector<Point>& ptvCtrlPts,
		std::vector<Point>& ptvEvaluatedCurvePts,
		const float& fAniLength,
		const bool& bWrap) const;
};

#endif