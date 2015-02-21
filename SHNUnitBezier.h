//
//  SHNUnitBezier.h
//  SHNUnitBezier
//

#ifndef __SHNUnitBezier__
#define __SHNUnitBezier__

typedef struct {
	double cx;
	double bx;
	double ax;
	
	double cy;
	double by;
	double ay;
} SHNUnitBezier;

const SHNUnitBezier SHNUnitBezierLinear;

const SHNUnitBezier SHNUnitBezierEase;
const SHNUnitBezier SHNUnitBezierEaseIn;
const SHNUnitBezier SHNUnitBezierEaseOut;
const SHNUnitBezier SHNUnitBezierEaseInOut;

/**
 * Create a unit bezier with polynomial coefficients pre-calculated based on the control points
 *
 * @param	p1x		First control point x [0.0 - 1.0]
 * @param	p1y		First control point y [0.0 - 1.0]
 * @param	p2x		Last control point x [0.0 - 1.0]
 * @param	p2y		Last control point y [0.0 - 1.0]
 */
SHNUnitBezier SHNUnitBezierMake(double p1x, double p1y, double p2x, double p2y);

/**
 * Solve bezier
 *
 * @param	bezier		Unit Bezier
 * @param	x
 * @param	epsilon
 */
double SHNUnitBezierSolve(SHNUnitBezier bezier, double x, double epsilon);

/**
 * Solve bezier using time progress and duration
 *
 * @param	bezier			Unit Bezier
 * @param	timeProgress	Progress in the animation [0.0 - 1.0]
 * @param	duration		Animation duration
 *
 * @return Solve valued between 0.0 and 1.0
 */
double SHNUnitBezierSolveWithDuration(SHNUnitBezier bezier, double timeProgress, double duration);

/**
 * Interpolate between the from and to values
 *
 * @param	bezier			Unit Bezier
 * @param	timeProgress	Progress in the animation [0.0 - 1.0]
 * @param	duration		Animation duration
 * @param	from			From value
 * @param	to				To value
 *
 * @return Interpolated value between from and to
 */
double SHNUnitBezierInterpolate(SHNUnitBezier bezier, double timeProgress, double duration, double from, double to);

#endif