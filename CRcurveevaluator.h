#ifndef INCLUDED_CR_CURVE_EVALUATOR_H
#define INCLUDED_CR_CURVE_EVALUATOR_H

#pragma warning(disable : 4786)  
#pragma warning(disable : 4018)
#pragma warning(disable : 4267)
#pragma warning(disable : 4311)
#pragma warning(disable : 4312)
#pragma warning(disable : 4244)
#pragma warning(disable : 4305)

#include "curveevaluator.h"
#include <iostream>
#include "CRcurveevaluator.h"

class CRCurveEvaluator : public CurveEvaluator
{
public:
	void evaluateCurve(const std::vector<Animator::Point>& ptvCtrlPts,
		std::vector<Animator::Point>& ptvEvaluatedCurvePts,
		const float& fAniLength,
		const bool& bWrap,
		const float default_val) const;
	bool flatness(const Animator::Point& pt1, const Animator::Point& pt2, const Animator::Point& pt3, const Animator::Point& pt4, const float epsilon) const;
	Animator::Point bezier(const Animator::Point& pt1, const Animator::Point& pt2, const Animator::Point& pt3, const Animator::Point& pt4, double u) const;
	void catmullRom(const std::vector<Animator::Point>& ptvCtrlPts, const int i, std::vector<Animator::Point>& ptvEvaluatedCurvePts, const float& fAniLength) const;
};

#endif