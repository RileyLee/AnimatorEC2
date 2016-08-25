#ifndef INCLUDED_BEZIER_CURVE_EVALUATOR_H
#define INCLUDED_BEZIER_CURVE_EVALUATOR_H

#pragma warning(disable : 4786)  
#pragma warning(disable : 4018)
#pragma warning(disable : 4267)
#pragma warning(disable : 4311)
#pragma warning(disable : 4312)
#pragma warning(disable : 4244)
#pragma warning(disable : 4305)

#include "curveevaluator.h"
#include <iostream>

class BezierCurveEvaluator : public CurveEvaluator
{
public:
	void evaluateCurve(const std::vector<Animator::Point>& ptvCtrlPts,
		std::vector<Animator::Point>& ptvEvaluatedCurvePts,
		const float& fAniLength,
		const bool& bWrap,
		const float default_val) const;
	bool Flatness(const Animator::Point& pt1, const Animator::Point& pt2, const Animator::Point& pt3, const Animator::Point& pt4, const float epsilon) const;
	Animator::Point Bezier(const Animator::Point& pt1, const Animator::Point& pt2, const Animator::Point& pt3, const Animator::Point& pt4, double u) const;
	Animator::Point BezierWrap(const std::vector<Animator::Point>& ptvCtrlPts, const int i, const float fAniLength, const float u) const;
	Animator::Point BezierWrap1(const std::vector<Animator::Point>& ptvCtrlPts, const float fAniLength, const float u) const;
};

#endif