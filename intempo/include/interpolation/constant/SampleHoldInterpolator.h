/*
 * SampleHoldInterpolator.h
 *
 *  Created on: 09/12/2012
 *      Author: Ignacio Mellado-Bataller
 */

#ifndef SAMPLEHOLDINTERPOLATOR_H_
#define SAMPLEHOLDINTERPOLATOR_H_

#include <atlante.h>
#include "../Interpolator.h"

namespace intempo {

template<class _SampleT> class SampleHoldInterpolator : public virtual Interpolator<_SampleT> {
public:
	inline SampleHoldInterpolator() : Interpolator<_SampleT>() {}
	inline SampleHoldInterpolator(TimeSignal<_SampleT> &signal) : Interpolator<_SampleT>(signal) {}

	virtual _SampleT getValue(cvg_double time);
	inline virtual SubspaceType getSubspace() { return SUBSPACE_WHOLE; }
};

}

#include "../../../sources/interpolation/constant/SampleHoldInterpolator.hh"

#endif /* SAMPLEHOLDINTERPOLATOR_H_ */
