#include "C2InterpolatingCurve.h"
#include <assert.h>
#include "mat.h"
#include "vec.h"
#include "matrix.h"
#include "B¨¦ziercurveevaluator.h"

#define SEGMENT 30

void C2InterpolatingCurve::evaluateCurve(const std::vector<Point>& controlPoints,
	std::vector<Point>& evaluatedPoints,
	const float& animationLength,
	const bool& beWrap,
	const bool& bAdaptive,
	const float& bflatness, const float& btension) const
{
	evaluatedPoints.clear();
	
	vector<Point> controlPointsTemp(controlPoints);
	int size_point = controlPointsTemp.size();

	if (beWrap) {
		Point phantomPointRight(controlPointsTemp[0].x + animationLength, controlPointsTemp[0].y);
		Point phantomPointLeft(controlPointsTemp[size_point - 1].x - animationLength, controlPointsTemp[size_point - 1].y);
		controlPointsTemp.insert(controlPointsTemp.begin(), phantomPointLeft);
		controlPointsTemp.push_back(phantomPointRight);
		size_point += 2;
	}
	else {
		if (size_point == 2) {
			evaluatedPoints.assign(controlPointsTemp.begin(), controlPointsTemp.end());
			evaluatedPoints.push_back(Point(0, controlPointsTemp[0].y));
			evaluatedPoints.push_back(Point(animationLength, controlPointsTemp[size_point - 1].y));
			return;
		}
	}
	

	
	

	float* data = new float[size_point * size_point];

	for (int i = 0; i < size_point * size_point; i++)
	{
		data[i] = 0.0f;
	}

	data[0] = 2.0f;
	data[1] = 1.0f;
	data[size_point * size_point - 2] = 1.0f;
	data[size_point * size_point - 1] = 2.0f;

	for (int i = 1; i < size_point - 1; i++) {
		int index = i * size_point + i - 1;
		data[index] = 1.0f;
		data[index + 1] = 4.0f;
		data[index + 2] = 1.0f;
	}

	float* right_equation = new float[size_point * 2];

	right_equation[0] = 3 * (controlPointsTemp[1].x - controlPointsTemp[0].x);
	right_equation[1] = 3 * (controlPointsTemp[1].y - controlPointsTemp[0].y);

	right_equation[2* size_point-2] = 3 * (controlPointsTemp[size_point-1].x - controlPointsTemp[size_point-2].x);
	right_equation[2 * size_point-1] = 3 * (controlPointsTemp[size_point-1].y - controlPointsTemp[size_point-2].y);

	for (int i = 1;i < size_point-1;i++)
	{
		right_equation[i*2] = 3 * (controlPointsTemp[i+1].x- controlPointsTemp[i-1].x);
		right_equation[i*2+1] = 3 * (controlPointsTemp[i + 1].y - controlPointsTemp[i-1].y);
	}

	Mat<float> basis(data, size_point, size_point);
	Mat<float> rhs(right_equation, size_point, 2);
	Mat<float> result = basis.inverse() * rhs;//D0 ~ Dm


	
	//compute the curve
	for (int i = 0; i < size_point - 1; i++) {
		vector<Point> points;
		Point v1(controlPointsTemp[i].x + Point(result.at(i, 0) / 3.0f, result.at(i, 1) / 3.0f).x, controlPointsTemp[i].y + Point(result.at(i, 0) / 3.0f, result.at(i, 1) / 3.0f).y);

		if (v1.x + 0.00001 > controlPointsTemp[i + 1].x)
			v1.x = controlPointsTemp[i + 1].x - 0.00001;
		Point v2(controlPointsTemp[i + 1].x - Point(result.at(i + 1, 0) / 3.0f, result.at(i + 1, 1) / 3.0f).x, controlPointsTemp[i + 1].y - Point(result.at(i + 1, 0) / 3.0f, result.at(i + 1, 1) / 3.0f).y);
		if (v2.x < controlPointsTemp[i].x + 0.00001)
		{
			v2.x = controlPointsTemp[i].x + 0.00001;
		}
		points.push_back(controlPointsTemp[i]);
		points.push_back(v1);
		points.push_back(v2);
		points.push_back(controlPointsTemp[i + 1]);
		
		
		vector<Point> param_evaluated;
		Beziercurveevaluator bezierCurveEvaluator;
		bezierCurveEvaluator.evaluateCurve(points, param_evaluated, animationLength, false, bAdaptive, bflatness, btension);
		//evaluatedPoints.insert(evaluatedPoints.end(), param_evaluated.begin(), param_evaluated.end()-2);
		for (int k = 0; k < param_evaluated.size() - 1; k++)
			if (param_evaluated[k].x < controlPointsTemp[i + 1].x && param_evaluated[k].x >= controlPointsTemp[i].x)
				evaluatedPoints.push_back(param_evaluated[k]);

		if (i == size_point - 2) {//the last group
			evaluatedPoints.push_back(points.back());
		}

	}

	if (!beWrap)
	{
		evaluatedPoints.push_back(Point(0, controlPoints.front().y));
		evaluatedPoints.push_back(Point(animationLength, controlPoints.back().y));
	}



}
