/*
 * NearestNeighborInterpolator.h
 *
 *  Created on: 09/12/2012
 *      Author: Ignacio Mellado-Bataller
 */

#ifndef NEARESTNEIGHBORINTERPOLATOR_H_
#define NEARESTNEIGHBORINTERPOLATOR_H_

#include <atlante.h>
#include "../Interpolator.h"

namespace intempo {

template<class _SampleT> class NearestNeighborInterpolator : public virtual Interpolator<_SampleT> {
public:
	inline NearestNeighborInterpolator() : Interpolator<_SampleT>() {}
	inline NearestNeighborInterpolator(TimeSignal<_SampleT> &signal) : Interpolator<_SampleT>(signal) {}

	virtual _SampleT getValue(cvg_double time);
	inline virtual SubspaceType getSubspace() { return SUBSPACE_WHOLE; }
};

}

#include "../../../sources/interpolation/constant/NearestNeighborInterpolator.hh"

#endif /* NEARESTNEIGHBORINTERPOLATOR_H_ */
