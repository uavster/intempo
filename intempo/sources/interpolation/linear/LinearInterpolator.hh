/*
 * LinearInterpolator.hh
 *
 *  Created on: 28/11/2012
 *      Author: Ignacio Mellado-Bataller
 */

#define template_def 			template<class _T, SubspaceType _SubspaceT>
#define LinearInterpolator_		LinearInterpolator<_T, _SubspaceT>

#define SLERP_THRESHOLD			1e-6

namespace intempo {

template_def _T LinearInterpolator_::getValue(cvg_double t) {
	typename TimeSignal<_T>::KeyPoint keypoints[2];
	Interpolator<_T>::getSignal()->getNeighborKeyPoints(t, 2, keypoints);
	cvg_double normalizedTime = (t - keypoints[0].time) / (keypoints[1].time - keypoints[0].time);
	return lerp(normalizedTime, keypoints[0].value, keypoints[1].value);
}

template_def _T LinearInterpolator_::lerp(cvg_double normalizedT, const _T &kp0, const _T &kp1) {
	return kp0 + (kp1 - kp0) * normalizedT;
}

#undef LinearInterpolator_
#undef template_def

#define template_def 			template<class _T>
#define LinearInterpolator_		LinearInterpolator<_T, SUBSPACE_SPHERICAL>

template_def _T LinearInterpolator_::getValue(cvg_double t) {
	if (!preprocessingDone) {
		preprocess(Interpolator<_T>::getSignal());
		preprocessingDone = true;
	}

	typename TimeSignal<_T>::KeyPoint keypoints[2];
	Interpolator<_T>::getSignal()->getNeighborKeyPoints(t, 2, keypoints);
	cvg_double normalizedTime = (t - keypoints[0].time) / (keypoints[1].time - keypoints[0].time);
	return slerp(normalizedTime, keypoints[0].value, keypoints[1].value);
}

template_def _T LinearInterpolator_::slerp(cvg_double normalizedT, const _T &kp0, const _T &kp1) {
	cvg_double a = acos(kp0 * kp1);

	cvg_double w0, w1;
	if (fabs(a) >= SLERP_THRESHOLD) {
		cvg_double invSinA = 1.0 / sin(a);
		w0 = sin((1.0 - normalizedT) * a) * invSinA;
		w1 = sin(normalizedT * a) * invSinA;
	}
	else {
		w0 = 1.0 - normalizedT;
		w1 = normalizedT;
	}

	return kp0 * w0 + kp1 * w1;
}

template_def void LinearInterpolator_::preprocess(TimeSignal<_T> *ts) {
	typename std::list<typename TimeSignal<_T>::KeyPoint>::iterator it, nit;
	for (it = ts->getKeyPoints().begin(); it != --ts->getKeyPoints().end(); it++) {
		nit = ++it; it--;
		if (nit->value * it->value < 0.0)
			nit->value = -nit->value;
	}
}

}

#undef LinearInterpolator_
#undef template_def

#undef SLERP_THRESHOLD
