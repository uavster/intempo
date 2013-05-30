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
