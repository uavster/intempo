/*
 * CSpline.h
 *
 *  Created on: 28/11/2012
 *      Author: Ignacio Mellado-Bataller
 *
 *  Description: Cubic Hermite spline.
 *  Notes: The free parameter, i.e. time, is in normalized units: [0, 1]
 */

#ifndef CSPLINE_H_
#define CSPLINE_H_

#include "Bezier.h"

namespace intempo {

template<class _SampleT> class CSpline {
public:
	// p0, v0: position and velocity at t=0.0; p1, v1: position and velocity at t=1.0
	CSpline(const _SampleT &p0, const _SampleT &v0, const _SampleT &p1, const _SampleT &v1);
	void setControlPoints(const _SampleT &p0, const _SampleT &v0, const _SampleT &p1, const _SampleT &v1);

	// Start point is at 0.0 and end point is at 1.0
	inline _SampleT solve(cvg_double time) { return bezier.solve(time); }

private:
	Bezier<_SampleT, 4> bezier;
};

}

#include "../../../sources/interpolation/cubic/CSpline.hh"

#endif /* CSPLINE_H_ */
