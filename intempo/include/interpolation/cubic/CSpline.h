/*

Intempo - C++ template library for signal interpolation

Copyright (C) 2012-2013  Ignacio Mellado-Bataller

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

*/

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
