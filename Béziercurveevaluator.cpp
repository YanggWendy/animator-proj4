#include "B¨¦ziercurveevaluator.h"
#include "mat.h"
#include "vec.h"
#include "Point.h"
#include <assert.h>
#include <float.h>
#include <math.h>
#define SEGMENT 30


void subdivide(std::vector<Point>& points4)
{
	vector<Point> tempresult;
	tempresult.push_back(points4[0]);
	Point V10((points4[0].x + points4[1].x) / 2, (points4[0].y + points4[1].y) / 2);
	Point V11((points4[1].x + points4[2].x) / 2, (points4[1].y + points4[2].y) / 2);
	Point V12((points4[2].x + points4[3].x) / 2, (points4[2].y + points4[3].y) / 2);
	Point V20((V10.x + V11.x) / 2, (V10.y + V11.y) / 2);
	Point V21((V11.x + V12.x) / 2, (V11.y + V12.y) / 2);
	Point V3((V20.x + V21.x) / 2, (V20.y + V21.y) / 2);
	tempresult.push_back(V10);
	tempresult.push_back(V20);
	tempresult.push_back(V3);
	tempresult.push_back(V21);
	tempresult.push_back(V12);
	tempresult.push_back(points4[3]);
	points4.clear();
	points4.assign(tempresult.begin(), tempresult.end());

}

float distance(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool FlatEnough(const std::vector<Point>& points4)
{
	if (distance(points4[0], points4[3]) < 0.00001)
	{
		return true;
	}
	else
	{
		float flatness = (distance(points4[0], points4[1]) + distance(points4[1], points4[2])
			+ distance(points4[2], points4[3])) / (distance(points4[0], points4[3]));
		if (flatness < 1 + 0.000001)
		{
			return true;
		}
	}
	return false;
}


void displayBezier(std::vector<Point>& points4, const std::vector<Point>& controlPoints,
	std::vector<Point>& evaluatedPoints)
{
	if (FlatEnough(points4))
	{
		evaluatedPoints.push_back(points4.front());
		evaluatedPoints.push_back(points4.back());
	}
	else
	{
		//cout << "1" << endl;
		subdivide(points4);
		vector<Point> newpoints4_1;
		vector<Point> newpoints4_2;
		newpoints4_1.insert(newpoints4_1.end(), points4.begin(), points4.begin()+4);
		newpoints4_2.insert(newpoints4_2.end(), points4.begin() + 3, points4.begin() + 7);
		//cout << newpoints4_1.size()<<endl;
		//cout << newpoints4_2.size() << endl;
		displayBezier(newpoints4_1, controlPoints, evaluatedPoints);
		displayBezier(newpoints4_2, controlPoints, evaluatedPoints);
	}
}





void Beziercurveevaluator::evaluateCurve(
	const std::vector<Point>& controlPoints,
	std::vector<Point>& evaluatedPoints,
	const float& animationLength,
	const bool& beWrap,
	const bool& bAdaptive,
	const float& bflatness, const float& btension) const
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

	if (bAdaptive)
	{
		int cnt;
		for (cnt = 0; cnt + 3 < controlPoints_temp.size(); cnt += 3)
		{
			evaluatedPoints.push_back(controlPoints_temp[cnt]);
			evaluatedPoints.push_back(controlPoints_temp[cnt + 3]);
			vector<Point> points4;
			//points4.assign(controlPoints_temp.begin() + cnt, controlPoints_temp.begin() + cnt + 4);
			//cout << points4.size() << endl;
			Point p1(controlPoints_temp[cnt].x, controlPoints_temp[cnt].y);
			points4.push_back(p1);
			Point p2(controlPoints_temp[cnt+1].x, controlPoints_temp[cnt+1].y);
			points4.push_back(p2);
			Point p3(controlPoints_temp[cnt+2].x, controlPoints_temp[cnt+2].y);
			points4.push_back(p3);
			Point p4(controlPoints_temp[cnt+3].x, controlPoints_temp[cnt+3].y);
			points4.push_back(p4);
			displayBezier(points4, controlPoints, evaluatedPoints);
		}
		for (; cnt < controlPoints.size(); cnt++)
		{
			evaluatedPoints.push_back(controlPoints[cnt]);
		}
	}
	else
	{
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

	}

	printf("EvaluatePts:%d\n", evaluatedPoints.size());

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


