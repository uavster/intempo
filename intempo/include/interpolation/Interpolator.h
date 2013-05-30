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
