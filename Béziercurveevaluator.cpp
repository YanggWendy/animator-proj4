#include "B¨¦ziercurveevaluator.h"
#include "mat.h"
#include "vec.h"
#include "Point.h"
#include <assert.h>
#include <float.h>
#define SEGMENT 30

void Beziercurveevaluator::evaluateCurve(
	const std::vector<Point>& controlPoints,
	std::vector<Point>& evaluatedPoints,
	const float& animationLength,
	const bool& beWrap) const
{
	evaluatedPoints.clear();

	// Wrapping version remark:
	// we insert one value at the end of the animation coordinate
	// case1: if this node can be part of the 4-node group (to generate curve)
	//		  the intersection y-value will determined by two close point in the curve
	// case2: then we will determine the intersection by using linear interpolation

	vector<Point> controlPoints_temp(controlPoints);
	if (beWrap)
	{
		controlPoints_temp.push_back(Point(controlPoints.front().x + animationLength,
			controlPoints.front().y));
	}

	float x_first = 0.0;
	float y_first = controlPoints[0].y;

	
	const Mat4d basis(
		-1, 3, -3, 1,
		3, -6, 3, 0,
		-3, 3, 0, 0,
		1, 0, 0, 0);

	bool is_wrapped = false;
	int count;
	for (count = 0; count + 3 < controlPoints_temp.size(); count += 3)
	{
		// push starting and ending points first
		evaluatedPoints.push_back(controlPoints_temp[count]);
		evaluatedPoints.push_back(controlPoints_temp[count + 3]);
		const Vec4d px(controlPoints_temp[count].x, controlPoints_temp[count + 1].x,
			controlPoints_temp[count + 2].x, controlPoints_temp[count + 3].x);
		const Vec4d py(controlPoints_temp[count].y, controlPoints_temp[count + 1].y,
			controlPoints_temp[count + 2].y, controlPoints_temp[count + 3].y);

		for (int i = 0; i < SEGMENT; ++i)
		{
			const double t = i / (double)SEGMENT;
			const Vec4d time(t * t * t, t * t, t, 1);


			Point eval_point(time * basis * px, time * basis * py);

			if (eval_point.x > animationLength&& beWrap)
			{
				const float x_mod = fmod(eval_point.x, animationLength);
				if (!is_wrapped)
				{
					const Point prev_point(evaluatedPoints.back());
					const float x_neg1 = prev_point.x - animationLength;
					evaluatedPoints.push_back(Point(x_neg1, prev_point.y));
					evaluatedPoints.push_back(eval_point);
					is_wrapped = true;
				}
				eval_point.x = x_mod;
			}
			evaluatedPoints.push_back(eval_point);
		}

	}

	for (; count < controlPoints.size(); count++)
	{
		evaluatedPoints.push_back(controlPoints[count]);
	}

	if (!beWrap)
	{
		evaluatedPoints.push_back(Point(0, controlPoints.front().y));
		evaluatedPoints.push_back(Point(animationLength, controlPoints.back().y));
	}
	else if (!is_wrapped)
	{
		const float interval_length = controlPoints.front().x + animationLength - controlPoints.back().x;
		const float percent = 1.0f - controlPoints.front().x / interval_length;
		const float y = controlPoints.back().y + (controlPoints.front().y - controlPoints.back().y) * percent;
		evaluatedPoints.push_back(Point(animationLength, y));
		evaluatedPoints.push_back(Point(0.0f, y));
	}
}


