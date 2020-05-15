#include "CatmullRomcurveevaluator.h"
#include <assert.h>
#include "mat.h"
#include "vec.h"



#define SEGMENT 30


void CatmullRomcurveevaluator::evaluateCurve(const std::vector<Point>& controlPoints,
	std::vector<Point>& evaluatedPoints,
	const float& animationLength,
	const bool& beWrap,
	const bool& bAdaptive,
	const float& bflatness, const float& btension) const
{
	evaluatedPoints.clear();

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
		controlPointsTemp.push_back(Point(0, controlPoints.front().y));
		controlPointsTemp.insert(controlPointsTemp.end(), controlPoints.begin(), controlPoints.end());
		controlPointsTemp.push_back(Point(animationLength, controlPoints.back().y));
	}

	const Mat4d basis = Mat4d(
		-1, 3, -3, 1,
		2, -5, 4, -1,
		-1, 0, 1, 0,
		0, 2, 0, 0) / 2.0;

	for (size_t cnt = 0; cnt + 3 < controlPointsTemp.size(); ++cnt)
	{
		const Vec4d param_x(controlPointsTemp[cnt].x, controlPointsTemp[cnt + 1].x,
			controlPointsTemp[cnt + 2].x, controlPointsTemp[cnt + 3].x);
		const Vec4d param_y(controlPointsTemp[cnt].y, controlPointsTemp[cnt + 1].y,
			controlPointsTemp[cnt + 2].y, controlPointsTemp[cnt + 3].y);

		for (int i = 0; i < SEGMENT; ++i)
		{
			const double t = i / (double)SEGMENT;
			const Vec4d param_time(t * t * t, t * t, t, 1);
			Point eval_point(param_time * basis * param_x, param_time * basis * param_y);
			// avoid wave curve occurs
			if (evaluatedPoints.empty() || eval_point.x > evaluatedPoints.back().x)
			{
				evaluatedPoints.push_back(eval_point);
			}
		}
	}

	if (!beWrap)
	{
		// avoid slope interpolate at the end
		if (controlPoints.back().x > evaluatedPoints.back().x)
		{
			evaluatedPoints.push_back(controlPoints.back());
		}
		evaluatedPoints.push_back(Point(0, controlPoints.front().y));
		evaluatedPoints.push_back(Point(animationLength, controlPoints.back().y));
	}
}