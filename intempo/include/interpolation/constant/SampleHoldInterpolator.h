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
