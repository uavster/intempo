/*
 * CubicInterpolator.hh
 *
 *  Created on: 29/11/2012
 *      Author: Ignacio Mellado-Bataller
 */

/* -- Default subspace (whole space) --
 * Default method: Derivatives at the end-points are computed by the Catmull-Rom method
 */

#include <list>
#include "include/interpolation/cubic/CSpline.h"
#include "include/interpolation/linear/LinearInterpolator.h"

#define template_def 			template<class _SampleT, SubspaceType _SubspaceT, CubicInterpolationMethod _Method>
#define CubicInterpolator_		CubicInterpolator<_SampleT, _SubspaceT, _Method>

namespace intempo {

template_def _SampleT CubicInterpolator_::getValue(cvg_double t) {
	typename TimeSignal<_SampleT>::KeyPoint keypoints[4];
	Interpolator<_SampleT>::getSignal()->getNeighborKeyPoints(t, 4, keypoints);

	typename TimeSignal<_SampleT>::KeyPoint *k0, *k1, *k2, *k3;
	k0 = &keypoints[0]; k1 = &keypoints[1]; k2 = &keypoints[2]; k3 = &keypoints[3];

	// Catmull-Rom method
	_SampleT v0 = 	(k2->value - k0->value) * (1.0 / (k2->time - k0->time));
	_SampleT v1 = 	(k3->value - k1->value) * (1.0 / (k3->time - k1->time));

	cvg_double dt = k2->time - k1->time;
	cvg_double normalizedTime = (t - k1->time) / dt;
	// Create spline with points and normalized derivatives (speeds)
	CSpline<_SampleT> cspline(k1->value, v0 * dt, k2->value, v1 * dt);
	return cspline.solve(normalizedTime);
}

#undef CubicInterpolator_
#undef template_def

/* -- Whole space --
 * Finite Difference specialization: Derivatives at the end-points are computed by the Finite Difference method
 */

#define template_def 			template<class _SampleT>
#define CubicInterpolator_		CubicInterpolator<_SampleT, SUBSPACE_WHOLE, CSPLINE_FINITE_DIFF>

template_def _SampleT CubicInterpolator_::getValue(cvg_double t) {
	typename TimeSignal<_SampleT>::KeyPoint keypoints[4];
	Interpolator<_SampleT>::getSignal()->getNeighborKeyPoints(t, 4, keypoints);

	typename TimeSignal<_SampleT>::KeyPoint *k0, *k1, *k2, *k3;
	k0 = &keypoints[0]; k1 = &keypoints[1]; k2 = &keypoints[2]; k3 = &keypoints[3];

	// Finite Difference method
	_SampleT v0 = 	(k2->value - k1->value) * (0.5 / (k2->time - k1->time)) +
					(k1->value - k0->value) * (0.5 / (k1->time - k0->time));

	_SampleT v1 = 	(k3->value - k2->value) * (0.5 / (k3->time - k2->time)) +
					(k2->value - k1->value) * (0.5 / (k2->time - k1->time));

	cvg_double dt = k2->time - k1->time;
	cvg_double normalizedTime = (t - k1->time) / dt;
	// Create spline with points and normalized derivatives (speeds)
	CSpline<_SampleT> cspline(k1->value, dt * v0, k2->value, dt * v1);
	return cspline.solve(normalizedTime);
}

#undef CubicInterpolator_
#undef template_def

/* -- Spherical subspace --
 * Finite Difference specialization: Derivatives at the end-points are computed by the Finite Difference method
 */

#define template_def 			template<class _SampleT>
#define CubicInterpolator_		CubicInterpolator<_SampleT, SUBSPACE_SPHERICAL, CSPLINE_FINITE_DIFF>

template_def _SampleT CubicInterpolator_::getValue(cvg_double t) {
	if (!preprocessingDone) {
		LinearInterpolator<_SampleT, SUBSPACE_SPHERICAL>::preprocess(Interpolator<_SampleT>::getSignal());
		// TODO: preprocessingDone should be set to false every time the time signal is changed. An event producer-listener scheme is needed for that.
		preprocessingDone = true;
	}

	typename TimeSignal<_SampleT>::KeyPoint keypoints[4];
	Interpolator<_SampleT>::getSignal()->getNeighborKeyPoints(t, 4, keypoints);

	typename TimeSignal<_SampleT>::KeyPoint *k0, *k1, *k2, *k3;
	k0 = &keypoints[0]; k1 = &keypoints[1]; k2 = &keypoints[2]; k3 = &keypoints[3];

	cvg_double dt = k2->time - k1->time;
	cvg_double normalizedTime = (t - k1->time) / dt;

	_SampleT k1Inv = k1->value.inverse();
	_SampleT tag1 = k1Inv.hProduct(k2->value).log();
	_SampleT tag0 = k1Inv.hProduct(k0->value).log();
	_SampleT s1 = k1->value.hProduct(((tag0 * (k2->time - k1->time) + tag1 * (k1->time - k0->time)) * (-0.5) / (k2->time - k0->time)).exp());
	_SampleT k2Inv = k2->value.inverse();
	_SampleT tag3 = k2Inv.hProduct(k3->value).log();
	_SampleT tag2 = k2Inv.hProduct(k1->value).log();
	_SampleT s2 = k2->value.hProduct(((tag2 * (k3->time - k2->time) + tag3 * (k2->time - k1->time)) * (-0.5) / (k3->time - k1->time)).exp());

//	_SampleT s1 = k1->value.hProduct(((k1->value.inverse().hProduct(k0->value).log() * (k2->time - k1->time)) * (-0.5) / (k2->time - k0->time)).exp());
//	_SampleT s2 = k2->value.hProduct(((k2->value.inverse().hProduct(k3->value).log() * (k2->time - k1->time)) * (-0.5) / (k3->time - k1->time)).exp());

	return squad(normalizedTime, k1->value, k2->value, s1, s2);
}

template_def _SampleT CubicInterpolator_::squad(cvg_double normalizedT, const _SampleT &q0, const _SampleT &q1, const _SampleT &s0, const _SampleT &s1) {
	return LinearInterpolator<_SampleT, SUBSPACE_SPHERICAL>::slerp(
			2 * normalizedT * (1 - normalizedT),
			LinearInterpolator<_SampleT, SUBSPACE_SPHERICAL>::slerp(normalizedT, q0, q1),
			LinearInterpolator<_SampleT, SUBSPACE_SPHERICAL>::slerp(normalizedT, s0, s1)
			);
}

#undef CubicInterpolator_
#undef template_def

/* -- Spherical subspace --
 * Catmull-Rom specialization: Derivatives at the end-points are computed by the Catmull-Rom method
 */

#define template_def 			template<class _SampleT>
#define CubicInterpolator_		CubicInterpolator<_SampleT, SUBSPACE_SPHERICAL, CSPLINE_CATMULL_ROM>

template_def _SampleT CubicInterpolator_::getValue(cvg_double t) {
	if (!preprocessingDone) {
		LinearInterpolator<_SampleT, SUBSPACE_SPHERICAL>::preprocess(Interpolator<_SampleT>::getSignal());
		// TODO: preprocessingDone should be set to false every time the time signal is changed. An event producer-listener scheme is needed for that.
		preprocessingDone = true;
	}

	typename TimeSignal<_SampleT>::KeyPoint keypoints[4];
	Interpolator<_SampleT>::getSignal()->getNeighborKeyPoints(t, 4, keypoints);

	typename TimeSignal<_SampleT>::KeyPoint *k0, *k1, *k2, *k3;
	k0 = &keypoints[0]; k1 = &keypoints[1]; k2 = &keypoints[2]; k3 = &keypoints[3];

	cvg_double dt = k2->time - k1->time;
	cvg_double normalizedTime = (t - k1->time) / dt;

	_SampleT s1 = k1->value.hProduct(((k1->value.inverse().hProduct(k0->value).log() * (k2->time - k1->time)) * (-0.5) / (k2->time - k0->time)).exp());
	_SampleT s2 = k2->value.hProduct(((k2->value.inverse().hProduct(k3->value).log() * (k2->time - k1->time)) * (-0.5) / (k3->time - k1->time)).exp());

	return CubicInterpolator<_SampleT, SUBSPACE_SPHERICAL, CSPLINE_FINITE_DIFF>::squad(normalizedTime, k1->value, k2->value, s1, s2);
}

}

#undef CubicInterpolator_
#undef template_def
