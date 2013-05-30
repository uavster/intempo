/*
 * Interpolator.h
 *
 *  Created on: 28/11/2012
 *      Author: Ignacio Mellado-Bataller
 */

#ifndef INTERPOLATOR_H_
#define INTERPOLATOR_H_

#include "../TimeSignal.h"

namespace intempo {

typedef enum { SUBSPACE_WHOLE, SUBSPACE_SPHERICAL } SubspaceType;

template<class _T> class Interpolator {
public:
	inline Interpolator() { this->signal = NULL; }
	inline Interpolator(TimeSignal<_T> &signal) { setSignal(signal); }

	virtual inline void setSignal(TimeSignal<_T> &signal) { this->signal = &signal; }
	inline TimeSignal<_T> *getSignal() const { return signal; }

	virtual _T getValue(cvg_double time) = 0;
	virtual SubspaceType getSubspace() = 0;

private:
	TimeSignal<_T> *signal;
};

}

#endif /* INTERPOLATOR_H_ */
