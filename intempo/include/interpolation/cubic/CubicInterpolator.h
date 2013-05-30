/*
 * CubicInterpolator.h
 *
 *  Created on: 29/11/2012
 *      Author: Ignacio Mellado-Bataller
 */

#ifndef CUBICINTERPOLATOR_H_
#define CUBICINTERPOLATOR_H_

#include "../Interpolator.h"

namespace intempo {

typedef enum { CSPLINE_FINITE_DIFF, CSPLINE_CATMULL_ROM } CubicInterpolationMethod;

template<class _SampleT, SubspaceType _SubspaceT = SUBSPACE_WHOLE, CubicInterpolationMethod _Method = CSPLINE_CATMULL_ROM> class CubicInterpolator : public virtual Interpolator<_SampleT> {
public:
	inline CubicInterpolator() : Interpolator<_SampleT>() {}
	inline CubicInterpolator(TimeSignal<_SampleT> &signal) : Interpolator<_SampleT>(signal) {}

	virtual _SampleT getValue(cvg_double t);
	virtual SubspaceType getSubspace() { return _SubspaceT; }
};

template<class _SampleT> class CubicInterpolator<_SampleT, SUBSPACE_WHOLE, CSPLINE_FINITE_DIFF> : public virtual Interpolator<_SampleT> {
public:
	inline CubicInterpolator() : Interpolator<_SampleT>() {}
	inline CubicInterpolator(TimeSignal<_SampleT> &signal) : Interpolator<_SampleT>(signal) {}

	virtual _SampleT getValue(cvg_double t);
	virtual SubspaceType getSubspace() { return SUBSPACE_WHOLE; }
};

template<class _SampleT> class CubicInterpolator<_SampleT, SUBSPACE_SPHERICAL, CSPLINE_CATMULL_ROM> : public virtual Interpolator<_SampleT> {
public:
	inline CubicInterpolator() : Interpolator<_SampleT>() {}
	inline CubicInterpolator(TimeSignal<_SampleT> &signal) : Interpolator<_SampleT>(signal) {}
	virtual inline void setSignal(TimeSignal<_SampleT> &signal) { Interpolator<_SampleT>::setSignal(signal); preprocessingDone = false; }

	virtual _SampleT getValue(cvg_double t);
	virtual SubspaceType getSubspace() { return SUBSPACE_SPHERICAL; }

private:
	cvg_bool preprocessingDone;
};

template<class _SampleT> class CubicInterpolator<_SampleT, SUBSPACE_SPHERICAL, CSPLINE_FINITE_DIFF> : public virtual Interpolator<_SampleT> {
	friend class CubicInterpolator<_SampleT, SUBSPACE_SPHERICAL, CSPLINE_CATMULL_ROM>;
public:
	inline CubicInterpolator() : Interpolator<_SampleT>() {}
	inline CubicInterpolator(TimeSignal<_SampleT> &signal) : Interpolator<_SampleT>(signal) {}
	virtual inline void setSignal(TimeSignal<_SampleT> &signal) { Interpolator<_SampleT>::setSignal(signal); preprocessingDone = false; }

	virtual _SampleT getValue(cvg_double t);
	virtual SubspaceType getSubspace() { return SUBSPACE_SPHERICAL; }

protected:
	static _SampleT squad(cvg_double normalizedT, const _SampleT &q0, const _SampleT &q1, const _SampleT &s0, const _SampleT &s1);
private:
	cvg_bool preprocessingDone;
};

}

#include "../../../sources/interpolation/cubic/CubicInterpolator.hh"

#endif /* CUBICINTERPOLATOR_H_ */
