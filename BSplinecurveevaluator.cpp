#include "BSplinecurveevaluator.h"
#include "B¨¦ziercurveevaluator.h"
#include <assert.h>
#include "mat.h"
#include "vec.h"

void BSplinecurveevaluator::evaluateCurve(
	const std::vector<Point>& controlPoints,
	std::vector<Point>& evaluatedPoints,
	const float& animationLength,
	const bool& beWrap,
	const bool& bAdaptive,
	const float& bflatness, const float& btension) const
{
	evaluatedPoints.clear();

	if (!beWrap)
	{
		evaluatedPoints.push_back(Point(0, controlPoints.front().y));
		evaluatedPoints.push_back(Point(animationLength, controlPoints.back().y));
	}

	// a hack to make the endpoints controllable
	vector<Point> controlPointsTemp;
	if (beWrap)
	{
		Point start_point1 = Point((controlPoints.end() - 2)->x - animationLength,
			(controlPoints.end() - 2)->y);
		Point start_point2 = Point((controlPoints.end() - 1)->x - animationLength,
			(controlPoints.end() - 1)->y);
		Point end_point1 = Point((controlPoints.begin())->x + animationLength,
			(controlPoints.begin())->y);
		Point end_point2 = Point((controlPoints.begin() + 1)->x + animationLength,
			(controlPoints.begin() + 1)->y);
		controlPointsTemp.push_back(start_point1);
		controlPointsTemp.push_back(start_point2);
		controlPointsTemp.insert(controlPointsTemp.end(), controlPoints.begin(), controlPoints.end());
		controlPointsTemp.push_back(end_point1);
		controlPointsTemp.push_back(end_point2);
	}
	else
	{
		controlPointsTemp.push_back(controlPoints.front());
		controlPointsTemp.push_back(controlPoints.front());
		controlPointsTemp.insert(controlPointsTemp.end(), controlPoints.begin(), controlPoints.end());
		controlPointsTemp.push_back(controlPoints.back());
		controlPointsTemp.push_back(controlPoints.back());
	}
	const Mat4d basis = Mat4d(
		1, 4, 1, 0,
		0, 4, 2, 0,
		0, 2, 4, 0,
		0, 1, 4, 1) / 6.0;

	Beziercurveevaluator bezierCurveEvaluator;
	for (size_t count = 0; count + 3 < controlPointsTemp.size(); ++count)
	{
		Vec4d param_x(controlPointsTemp[count].x, controlPointsTemp[count + 1].x,
			controlPointsTemp[count + 2].x, controlPointsTemp[count + 3].x);
		Vec4d param_y(controlPointsTemp[count].y, controlPointsTemp[count + 1].y,
			controlPointsTemp[count + 2].y, controlPointsTemp[count + 3].y);
		param_x = basis * param_x;
		param_y = basis * param_y;
		vector<Point> param_control;
		for (int i = 0; i < 4; ++i)
		{
			param_control.push_back(Point(param_x[i], param_y[i]));
		}
		vector<Point> param_evaluated;
		bezierCurveEvaluator.evaluateCurve(param_control, param_evaluated, animationLength, false,bAdaptive, bflatness, btension);
		evaluatedPoints.insert(evaluatedPoints.end(), param_evaluated.begin(), param_evaluated.end() - 2);
	}

}