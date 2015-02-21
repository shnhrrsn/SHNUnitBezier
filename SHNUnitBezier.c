//
//  SHNUnitBezier.m
//  SHNUnitBezier
//

// Derived from https://trac.webkit.org/browser/trunk/Source/WebCore/platform/graphics/UnitBezier.h?rev=147219

#import "SHNUnitBezier.h"
#include <math.h>

// Calculate the polynomial coefficients, implicit first and last control points are (0,0) and (1,1).
#define _SHNUnitBezierMake(p1x, p1y, p2x, p2y) (SHNUnitBezier){\
	.cx = 3.0 * p1x,\
	.bx = 3.0 * (p2x - p1x) - (3.0 * p1x),\
	.ax = 1.0 - (3.0 * p1x) - (3.0 * (p2x - p1x) - (3.0 * p1x)),\
\
	.cy = 3.0 * p1y,\
	.by = 3.0 * (p2y - p1y) - (3.0 * p1y),\
	.ay = 1.0 - (3.0 * p1y) - (3.0 * (p2y - p1y) - (3.0 * p1y))\
}

const SHNUnitBezier SHNUnitBezierLinear = _SHNUnitBezierMake(0.0, 0.0, 1.0, 1.0);

const SHNUnitBezier SHNUnitBezierEase = _SHNUnitBezierMake(0.25, 0.1, 0.25, 0.1);
const SHNUnitBezier SHNUnitBezierEaseIn = _SHNUnitBezierMake(0.42f, 0.0, 1.0, 1.0);
const SHNUnitBezier SHNUnitBezierEaseOut = _SHNUnitBezierMake(0.0, 0.0, 0.58f, 1.0);
const SHNUnitBezier SHNUnitBezierEaseInOut = _SHNUnitBezierMake(0.42f, 0.0, 0.58f, 1.0);

SHNUnitBezier SHNUnitBezierMake(double p1x, double p1y, double p2x, double p2y) {
	return _SHNUnitBezierMake(p1x, p1y, p2x, p2y);
}


static inline double SHNUnitBezierSampleCurveX(SHNUnitBezier bezier, double t) {
	// `ax t^3 + bx t^2 + cx t' expanded using Horner's rule.
	return ((bezier.ax * t + bezier.bx) * t + bezier.cx) * t;
}

static inline double SHNUnitBezierSampleCurveY(SHNUnitBezier bezier, double t) {
	return ((bezier.ay * t + bezier.by) * t + bezier.cy) * t;
}

static inline double SHNUnitBezierSampleCurveDerivativeX(SHNUnitBezier bezier, double t) {
	return (3.0 * bezier.ax * t + 2.0 * bezier.bx) * t + bezier.cx;
}

// Given an x value, find a parametric value it came from.
double SHNUnitBezierSolveCurveX(SHNUnitBezier bezier, double x, double epsilon) {
	double t0;
	double t1;
	double t2;
	double x2;
	double d2;
	int i;
	
	// First try a few iterations of Newton's method -- normally very fast.
	for (t2 = x, i = 0; i < 8; i++) {
		x2 = SHNUnitBezierSampleCurveX(bezier, t2) - x;
		if (fabs (x2) < epsilon)
			return t2;
		d2 = SHNUnitBezierSampleCurveDerivativeX(bezier, t2);
		if (fabs(d2) < 1e-6)
			break;
		t2 = t2 - x2 / d2;
	}
	
	// Fall back to the bisection method for reliability.
	t0 = 0.0;
	t1 = 1.0;
	t2 = x;
	
	if (t2 < t0)
		return t0;
	if (t2 > t1)
		return t1;
	
	while (t0 < t1) {
		x2 = SHNUnitBezierSampleCurveX(bezier, t2);
		if (fabs(x2 - x) < epsilon)
			return t2;
		if (x > x2)
			t0 = t2;
		else
			t1 = t2;
		t2 = (t1 - t0) * .5 + t0;
	}
	
	// Failure.
	return t2;
}

double SHNUnitBezierSolve(SHNUnitBezier bezier, double x, double epsilon) {
	return SHNUnitBezierSampleCurveY(bezier, SHNUnitBezierSolveCurveX(bezier, x, epsilon));
}

static inline double SHNUnitBezierSolveEpsilonForDuration(double duration) {
	return 1.0 / (200 * duration);
}

double SHNUnitBezierSolveWithDuration(SHNUnitBezier bezier, double timeProgress, double duration) {
	return SHNUnitBezierSolve(bezier, timeProgress, SHNUnitBezierSolveEpsilonForDuration(duration));
}

double SHNUnitBezierInterpolate(SHNUnitBezier bezier, double timeProgress, double duration, double from, double to) {
	return (from + SHNUnitBezierSolveWithDuration(bezier, timeProgress, duration) * (to - from));
}
