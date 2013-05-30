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
 * Bezier.h
 *
 *  Created on: 29/11/2012
 *      Author: Ignacio Mellado-Bataller
 *
 *  Description: Bezier curve solution with the De Casteljau method.
 *
 *  Notes: The template parameter _SampleT defines the sample type.
 *  Sample types are required to provide + and * operators.
 *  A faster specialization is provided for 4-point curves.
 *  The free parameter, i.e. time, is in normalized units: [0, 1]
 */

#ifndef BEZIER_H_
#define BEZIER_H_

#include <vector>
#include <list>

namespace intempo {

template<class _SampleT, int _NPoints = -1> class Bezier {
public:
	// Control points are passed later
	Bezier();

	// Control points are passed in a vector
	Bezier(const std::vector<_SampleT> &points);
	void setControlPoints(const std::vector<_SampleT> &points);
	// Control points are passed in a list
	Bezier(const std::list<_SampleT> &points);
	void setControlPoints(const std::list<_SampleT> &points);
	// Control points are passed in any container with iterators, size(), begin() and end()
	template<class _ContainerT> Bezier(const _ContainerT &points);
	template<class _ContainerT> void setControlPoints(const _ContainerT &points);
	// Control points are passed as an array
	Bezier(cvg_int numPoints, const _SampleT *points);
	void setControlPoints(cvg_int numPoints, const _SampleT *points);
	// Control points are passed as an array of pointers to the points
	Bezier(cvg_int numPoints, const _SampleT **points);
	void setControlPoints(cvg_int numPoints, const _SampleT **points);

	_SampleT getControlPoint(cvg_uint index);

	_SampleT solve(cvg_double time);

protected:
	template<class _ContainerT> void init(const _ContainerT &points);
	void init(cvg_int numPoints, const _SampleT *points);
	void init(cvg_int numPoints, const _SampleT **points);
	void solveRecursive(cvg_double t);
private:
	std::vector<_SampleT> points;
	cvg_int numAux;
	std::vector<_SampleT> aux;
};

template<class _SampleT> class Bezier<_SampleT, 4> {
public:
	// Control points are passed later
	Bezier();

	// Control points are passed in a vector
	Bezier(const std::vector<_SampleT> &points);
	void setControlPoints(const std::vector<_SampleT> &points);
	// Control points are passed in a list
	Bezier(const std::list<_SampleT> &points);
	void setControlPoints(const std::list<_SampleT> &points);
	// Control points are passed in any container with iterators, size(), begin() and end()
	template<class _ContainerT> Bezier(const _ContainerT &points);
	template<class _ContainerT> void setControlPoints(const _ContainerT &points);
	// Control points are passed as an array
	Bezier(const _SampleT *points);
	void setControlPoints(const _SampleT *points);
	// Control points are passed as an array of pointers to the points
	Bezier(const _SampleT **points);
	void setControlPoints(const _SampleT **points);
	// Control points are passed explicitly as parameters
	Bezier(const _SampleT &p0, const _SampleT &p1, const _SampleT &p2, const _SampleT &p3);
	void setControlPoints(const _SampleT &p0, const _SampleT &p1, const _SampleT &p2, const _SampleT &p3);

	_SampleT getControlPoint(cvg_uint index);

	_SampleT solve(cvg_double time);

protected:
	template<class _ContainerT> void init(const _ContainerT &points);
	void init(const _SampleT *points);
	void init(const _SampleT **points);
	void init(const _SampleT &p0, const _SampleT &p1, const _SampleT &p2, const _SampleT &p3);
private:
	_SampleT points[4];
};

}

#include "../../../sources/interpolation/cubic/Bezier.hh"

#endif /* BEZIER_H_ */
