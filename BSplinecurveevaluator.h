#pragma once

#ifndef INCLUDED_BSpline_CURVE_EVALUATOR_H
#define INCLUDED_BSpline_CURVE_EVALUATOR_H

#pragma warning(disable : 4786)  

#include "CurveEvaluator.h"

class BSplinecurveevaluator
	: public CurveEvaluator
{
public:
	void evaluateCurve(const std::vector<Point>& ptvCtrlPts,
		std::vector<Point>& ptvEvaluatedCurvePts,
		const float& fAniLength,
		const bool& bWrap) const;
};

#endif