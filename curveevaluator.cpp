#include "CurveEvaluator.h"

float CurveEvaluator::s_fFlatnessEpsilon = 0.00001f;
int CurveEvaluator::s_iSegCount = 16;
float CurveEvaluator::tension = 1 / 2;
CurveEvaluator::~CurveEvaluator(void)
{
}

