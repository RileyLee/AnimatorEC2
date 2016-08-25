#include "CRcurveevaluator.h"
#include <cassert>
using namespace Animator;
using namespace std;

void CRCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float& fAniLength,
	const bool& bWrap,
	const float default_val) const
{
	std::vector<Point> tempCtrlPts;
	int iCtrlPtCount = ptvCtrlPts.size();
	ptvEvaluatedCurvePts.clear();
	tempCtrlPts.clear();

	if (!bWrap){
		tempCtrlPts.push_back(ptvCtrlPts[0]);
		tempCtrlPts.insert(tempCtrlPts.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
		tempCtrlPts.push_back(ptvCtrlPts[iCtrlPtCount - 1]);
	}
	else{
		tempCtrlPts.insert(tempCtrlPts.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
		tempCtrlPts.push_back(Point(ptvCtrlPts[0].x + fAniLength, ptvCtrlPts[0].y));
		tempCtrlPts.push_back(Point(ptvCtrlPts[1].x + fAniLength, ptvCtrlPts[1].y));
		if (iCtrlPtCount == 2)
			tempCtrlPts.push_back(Point(ptvCtrlPts[0].x + fAniLength * 2, ptvCtrlPts[0].y));
		else
			tempCtrlPts.push_back(Point(ptvCtrlPts[2].x + fAniLength, ptvCtrlPts[2].y));
	}


	if (!bWrap){
		for (int i = 1; i < iCtrlPtCount; i = i + 1)
			catmullRom(tempCtrlPts, i - 1, ptvEvaluatedCurvePts, fAniLength);

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
	else{
		for (int i = 0; i < iCtrlPtCount; i = i + 1)
			catmullRom(tempCtrlPts, i, ptvEvaluatedCurvePts, fAniLength);
	}
}


bool CRCurveEvaluator::flatness(const Animator::Point& pt1, const Animator::Point& pt2, const Animator::Point& pt3, const Animator::Point& pt4, const float epsilon) const{
	float val;
	val = abs(pt2.y - pt1.y) + abs(pt3.y - pt2.y) + abs(pt4.y - pt3.y);
	val = val / abs(pt4.y - pt1.y);
	return val>(1 + epsilon);
}

Point CRCurveEvaluator::bezier(const Animator::Point& pt1, const Animator::Point& pt2, const Animator::Point& pt3, const Animator::Point& pt4, double u) const{
	Point pt;
	pt.x = pt1.x + (-3 * pt1.x + 3 * pt2.x) * u + (3 * pt1.x - 6 * pt2.x + 3 * pt3.x)*u*u + (-pt1.x + 3 * pt2.x - 3 * pt3.x + pt4.x)*u*u*u;
	pt.y = pt1.y + (-3 * pt1.y + 3 * pt2.y) * u + (3 * pt1.y - 6 * pt2.y + 3 * pt3.y)*u*u + (-pt1.y + 3 * pt2.y - 3 * pt3.y + pt4.y)*u*u*u;
	return pt;
}

void CRCurveEvaluator::catmullRom(const std::vector<Point>& ptvCtrlPts, const int i, std::vector<Point>& ptvEvaluatedCurvePts, const float& fAniLength) const{
	Point v1, v2, v3, v4, pt1, pt2, pt3, pt4, pt;
	int CtrlPtCount = ptvCtrlPts.size();
	float prevX,upperboundX;
	pt1 = ptvCtrlPts[i];
	pt2 = ptvCtrlPts[i + 1];
	pt3 = ptvCtrlPts[i + 2];
	pt4 = ptvCtrlPts[i + 3];

	v1.x = pt2.x;
	v2.x = -pt1.x / 6 + pt2.x + pt3.x / 6;
	v3.x = pt2.x / 6 + pt3.x - pt4.x / 6;
	v4.x = pt3.x;

	v1.y = pt2.y;
	v2.y = -pt1.y / 6 + pt2.y + pt3.y / 6;
	v3.y = pt2.y / 6 + pt3.y - pt4.y / 6;
	v4.y = pt3.y;


	upperboundX = v4.x;
	prevX = v1.x;

	for (float u = 0; u <= 1.0000; u = u + 0.01){
		pt = bezier(v1, v2, v3, v4, u);
		
		if ((pt.x - prevX>0) && pt.x<upperboundX){
			prevX = pt.x;
			if (pt.x > fAniLength) {
				pt.x = pt.x - fAniLength;
			}
			ptvEvaluatedCurvePts.push_back(pt);
		}
			
	}
}