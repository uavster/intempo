/*
 * SampleHoldInterpolator.hh
 *
 *  Created on: 09/12/2012
 *      Author: Ignacio Mellado-Bataller
 */

#define template_def				template<class _SampleT>
#define SampleHoldInterpolator_		SampleHoldInterpolator<_SampleT>

namespace intempo {

template_def _SampleT SampleHoldInterpolator_::getValue(cvg_double time) {
	typename TimeSignal<_SampleT>::KeyPoint keypoints[2];
	Interpolator<_SampleT>::getSignal()->getNeighborKeyPoints(time, 2, keypoints);
	return keypoints[0].value;
}

}

#undef SampleHoldInterpolator_
#undef template_def



