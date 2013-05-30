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
 * LinearInterpolator.h
 *
 *  Created on: 28/11/2012
 *      Author: Ignacio Mellado-Bataller
 */

#include "../cubic/CubicInterpolator.h"
#include "../Interpolator.h"

#ifndef LINEARINTERPOLATOR_H_
#define LINEARINTERPOLATOR_H_

namespace intempo {

template<class _T, SubspaceType _SubspaceT = SUBSPACE_WHOLE> class LinearInterpolator : public virtual Interpolator<_T> {
public:
	inline LinearInterpolator() : Interpolator<_T>() {}
	inline LinearInterpolator(TimeSignal<_T> &signal) : Interpolator<_T>(signal) {}

	virtual _T getValue(cvg_double t);
	virtual inline SubspaceType getSubspace() { return _SubspaceT; }

protected:
	static _T lerp(cvg_double normalizedT, const _T &kp0, const _T &kp1);
};

template<class _T> class LinearInterpolator<_T, SUBSPACE_SPHERICAL> : public virtual Interpolator<_T> {
	template<class _SampleT, SubspaceType _SubspaceT, CubicInterpolationMethod _Method> friend class CubicInterpolator;
public:
	inline LinearInterpolator() : Interpolator<_T>() {}
	inline LinearInterpolator(TimeSignal<_T> &signal) : Interpolator<_T>(signal) { }
	virtual inline void setSignal(TimeSignal<_T> &signal) { Interpolator<_T>::setSignal(signal); preprocessingDone = false; }

	virtual _T getValue(cvg_double t);
	virtual inline SubspaceType getSubspace() { return SUBSPACE_SPHERICAL; }

protected:
	static _T slerp(cvg_double normalizedT, const _T &kp0, const _T &kp1);
	static void preprocess(TimeSignal<_T> *ts);
private:
	cvg_bool preprocessingDone;
};

}

#include "../../../sources/interpolation/linear/LinearInterpolator.hh"

#endif /* LINEARINTERPOLATOR_H_ */
