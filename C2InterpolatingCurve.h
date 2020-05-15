#pragma once


#ifndef INCLUDED_C2InterpolatingCurve_CURVE_EVALUATOR_H
#define INCLUDED_C2InterpolatingCurve_CURVE_EVALUATOR_H

#pragma warning(disable : 4786)  

#include "CurveEvaluator.h"

class C2InterpolatingCurve
	: public CurveEvaluator
{
public:
	void evaluateCurve(const std::vector<Point>& ptvCtrlPts,
		std::vector<Point>& ptvEvaluatedCurvePts,
		const float& fAniLength,
		const bool& bWrap,
		const bool& bAdaptive,
		const float& bflatness, const float& btension) const;

	
};

#endif