#include "subsivisioncurveevaluator.h"


void SubdivisionCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float& fAniLength,
	const bool& bWrap,const bool& bAdaptive,
	const float& bflatness, const float& btension) const {

	vector<Point> controlPointsTemp;
	controlPointsTemp.assign(ptvCtrlPts.begin(), ptvCtrlPts.end());
	if (bWrap) {
		controlPointsTemp.insert(controlPointsTemp.begin(), Point(0, 0));
		controlPointsTemp.push_back(Point(fAniLength, 0));
	}

	double k = 0;
	while (k < 10) {
		if (controlPointsTemp.size() == 2)
			break;

		vector<Point> divided;
		divided.push_back(controlPointsTemp[0]);
		for (int i = 0; i < controlPointsTemp.size() - 1; i++) {
			Point mid ((controlPointsTemp[i].x + controlPointsTemp[i + 1].x) / 2, (controlPointsTemp[i].y + controlPointsTemp[i + 1].y) / 2);
			divided.push_back(mid);
			divided.push_back(controlPointsTemp[i + 1]);
		}

		vector<Point> bin;
		bin.push_back(divided[0]);
		for (int i = 0; i < divided.size() - 1; i++) {
			float x = (divided[i + 1].x - divided[i].x) * avgMask + divided[i].x;
			float y = (divided[i + 1].y - divided[i].y) * avgMask + divided[i].y;
			bin.push_back(Point(x, y));
		}
		bin.push_back(divided.back());
		controlPointsTemp = bin;
		k++;
	}

	ptvEvaluatedCurvePts.clear();
	ptvEvaluatedCurvePts.assign(controlPointsTemp.begin(), controlPointsTemp.end());

	if (!bWrap) {
		ptvEvaluatedCurvePts.insert(ptvEvaluatedCurvePts.begin(), Point(0, controlPointsTemp[0].y));
		ptvEvaluatedCurvePts.push_back(Point(fAniLength, controlPointsTemp.back().y));
	}
}