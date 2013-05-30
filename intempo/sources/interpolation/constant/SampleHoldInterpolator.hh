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



