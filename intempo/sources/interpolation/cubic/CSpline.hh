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
 * CSpline.hh
 *
 *  Created on: 29/11/2012
 *      Author: Ignacio Mellado-Bataller
 */

#define template_def	template<class _SampleT>
#define CSpline_		CSpline<_SampleT>

namespace intempo {

template_def CSpline_::CSpline(const _SampleT &p0, const _SampleT &v0, const _SampleT &p1, const _SampleT &v1) {
	setControlPoints(p0, v0, p1, v1);
}

template_def void CSpline_::setControlPoints(const _SampleT &p0, const _SampleT &v0, const _SampleT &p1, const _SampleT &v1) {
	bezier.setControlPoints(p0, p0 + v0 * (1.0 / 3.0), p1 - v1 * (1.0 / 3.0), p1);
}

}

#undef CSpline_
#undef template_def



