#include "beziercurveevaluator.h"
#include <cassert>
using namespace Animator;
using namespace std;

void BezierCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float& fAniLength,
	const bool& bWrap,
	const float default_val) const
{
	int iCtrlPtCount = ptvCtrlPts.size();  Point pt;
	std::vector<Point> tempCtrlPts;
	tempCtrlPts.assign(ptvCtrlPts.begin(), ptvCtrlPts.end());
	ptvEvaluatedCurvePts.clear();

	for (int i = 0; i < iCtrlPtCount; i = i + 3){
		if ((i + 3) < iCtrlPtCount && Flatness(tempCtrlPts[i], tempCtrlPts[i + 1], tempCtrlPts[i + 2], tempCtrlPts[i + 3], 0.1)){
			for (float u = 0; u <= 1.0; u = u + 0.001){
				pt = Bezier(tempCtrlPts[i], tempCtrlPts[i + 1], tempCtrlPts[i + 2], tempCtrlPts[i + 3], u);
				ptvEvaluatedCurvePts.push_back(pt);
			}
		}
	}

	if (iCtrlPtCount>3)
		tempCtrlPts.erase(tempCtrlPts.begin() + 1, tempCtrlPts.begin() + 3 * floor((iCtrlPtCount - 1) / 3));
	else{
		ptvEvaluatedCurvePts.push_back(tempCtrlPts[0]);
		ptvEvaluatedCurvePts.push_back(tempCtrlPts[tempCtrlPts.size() - 1]);
	}
		

	if (bWrap&&tempCtrlPts.size()==4){
		for (float u = 0; u <= 1.0; u = u + 0.001){
			pt = BezierWrap1(tempCtrlPts, fAniLength, u);
			ptvEvaluatedCurvePts.push_back(pt);
		}
	}
	else{
		if (tempCtrlPts.size() > 2 && iCtrlPtCount>4){
			ptvEvaluatedCurvePts.insert(ptvEvaluatedCurvePts.end(),tempCtrlPts.begin() + 2, tempCtrlPts.end());
		}
		else if (tempCtrlPts.size() > 2 && iCtrlPtCount<4){
			ptvEvaluatedCurvePts.insert(ptvEvaluatedCurvePts.end(), tempCtrlPts.begin() + 1, tempCtrlPts.end()-1);
		}
		float x = 0.0; float y1; iCtrlPtCount = tempCtrlPts.size();
		if (bWrap){
			if ((tempCtrlPts[0].x + fAniLength) - tempCtrlPts[iCtrlPtCount - 1].x > 0.0f) {
				y1 = (tempCtrlPts[0].y * (fAniLength - tempCtrlPts[iCtrlPtCount - 1].x) +
					tempCtrlPts[iCtrlPtCount - 1].y * tempCtrlPts[0].x) /
					(tempCtrlPts[0].x + fAniLength - tempCtrlPts[iCtrlPtCount - 1].x);
			}
		}
		else
			y1 = tempCtrlPts[0].y;
		ptvEvaluatedCurvePts.push_back(Point(x, y1));
		float y2;  x = fAniLength;
		if (bWrap)
			y2 = y1;
		else
			y2 = tempCtrlPts[iCtrlPtCount - 1].y;

		ptvEvaluatedCurvePts.push_back(Point(x, y2));

	}
}


bool BezierCurveEvaluator::Flatness(const Animator::Point& pt1, const Animator::Point& pt2, const Animator::Point& pt3, const Animator::Point& pt4, const float epsilon) const{
	float val;
	val = abs(pt2.y - pt1.y) + abs(pt3.y - pt2.y) + abs(pt4.y - pt3.y);
	val = val / abs(pt4.y - pt1.y);
	return val>(1 + epsilon);
}

Point BezierCurveEvaluator::Bezier(const Animator::Point& pt1, const Animator::Point& pt2, const Animator::Point& pt3, const Animator::Point& pt4, double u) const{
	Point pt;
	pt.x = pt1.x + (-3 * pt1.x + 3 * pt2.x) * u + (3 * pt1.x - 6 * pt2.x + 3 * pt3.x)*u*u + (-pt1.x + 3 * pt2.x - 3 * pt3.x + pt4.x)*u*u*u;
	pt.y = pt1.y + (-3 * pt1.y + 3 * pt2.y) * u + (3 * pt1.y - 6 * pt2.y + 3 * pt3.y)*u*u + (-pt1.y + 3 * pt2.y - 3 * pt3.y + pt4.y)*u*u*u;
	return pt;
}

Point BezierCurveEvaluator::BezierWrap(const std::vector<Point>& ptvCtrlPts, const int i, const float fAniLength, const float u) const{
	Point pt, pt1, pt2, pt3, pt4;
	pt1 = ptvCtrlPts[i];
	if (i + 1 >= ptvCtrlPts.size()) pt2 = ptvCtrlPts[i + 1];
	else {
		pt2 = ptvCtrlPts[i + 1 - ptvCtrlPts.size()];
		pt2.x = pt2.x + fAniLength;
	}
	if (i + 2 >= ptvCtrlPts.size()) pt3 = ptvCtrlPts[i + 2];
	else {
		pt3 = ptvCtrlPts[i + 2 - ptvCtrlPts.size()];
		pt3.x = pt3.x + fAniLength;
	}
	if (i + 3 >= ptvCtrlPts.size()) pt4 = ptvCtrlPts[i + 3];
	else {
		pt4 = ptvCtrlPts[i + 3 - ptvCtrlPts.size()];
		pt4.x = pt4.x + fAniLength;
	}
	pt.x = pt1.x + (-3 * pt1.x + 3 * pt2.x) * u + (3 * pt1.x - 6 * pt2.x + 3 * pt3.x)*u*u + (-pt1.x + 3 * pt2.x - 3 * pt3.x + pt4.x)*u*u*u;
	pt.y = pt1.y + (-3 * pt1.y + 3 * pt2.y) * u + (3 * pt1.y - 6 * pt2.y + 3 * pt3.y)*u*u + (-pt1.y + 3 * pt2.y - 3 * pt3.y + pt4.y)*u*u*u;
	if (pt.x > fAniLength)
		pt.x = pt.x - fAniLength;
	return pt;
}

Point BezierCurveEvaluator::BezierWrap1(const std::vector<Point>& ptvCtrlPts, const float fAniLength, const float u) const{
	Point pt, pt1, pt2, pt3, pt4;
	pt1 = ptvCtrlPts[1];
	pt2 = ptvCtrlPts[2];
	pt3 = ptvCtrlPts[3];
	pt4 = ptvCtrlPts[0];
	pt4.x = pt4.x + fAniLength;
	pt.x = pt1.x + (-3 * pt1.x + 3 * pt2.x) * u + (3 * pt1.x - 6 * pt2.x + 3 * pt3.x)*u*u + (-pt1.x + 3 * pt2.x - 3 * pt3.x + pt4.x)*u*u*u;
	pt.y = pt1.y + (-3 * pt1.y + 3 * pt2.y) * u + (3 * pt1.y - 6 * pt2.y + 3 * pt3.y)*u*u + (-pt1.y + 3 * pt2.y - 3 * pt3.y + pt4.y)*u*u*u;
	if (pt.x > fAniLength)
		pt.x = pt.x - fAniLength;
	return pt;
}