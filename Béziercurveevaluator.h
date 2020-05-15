#pragma once

#ifndef INCLUDED_Bezier_CURVE_EVALUATOR_H
#define INCLUDED_Bezier_CURVE_EVALUATOR_H

#pragma warning(disable : 4786)  

//#include "CurveEvaluator.h"
#include "../curveevaluator.h"
#include "Curve.h"

class Beziercurveevaluator: public CurveEvaluator
{
public:
	void evaluateCurve(const std::vector<Point>& ptvCtrlPts,
		std::vector<Point>& ptvEvaluatedCurvePts,
		const float& fAniLength,
		const bool& bWrap,
		const bool& bAdaptive,
		const float& bflatness, const float& btension) const;

	/*void displayBezier(std::vector<Point>& points4, const std::vector<Point>& controlPoints,
		std::vector<Point>& evaluatedPoints);
	bool FlatEnough(const std::vector<Point>& points4);
	void subdivide(std::vector<Point>& points4);*/

};

#endif