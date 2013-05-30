/*
 * NearestNeighborInterpolator.hh
 *
 *  Created on: 09/12/2012
 *      Author: Ignacio Mellado-Bataller
 */

#define template_def					template<class _SampleT>
#define NearestNeighborInterpolator_	NearestNeighborInterpolator<_SampleT>

namespace intempo {

template_def _SampleT NearestNeighborInterpolator_::getValue(cvg_double time) {
	typename TimeSignal<_SampleT>::KeyPoint keypoints[2];
	Interpolator<_SampleT>::getSignal()->getNeighborKeyPoints(time, 2, keypoints);
	if (time - keypoints[0].time < keypoints[1].time - time) return keypoints[0].value;
	else return keypoints[1].value;
}

}

#undef NearestNeighborInterpolator_
#undef template_def


