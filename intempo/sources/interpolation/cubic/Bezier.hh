/*
 * Bezier.hh
 *
 *  Created on: 29/11/2012
 *      Author: Ignacio Mellado-Bataller
 */

/*
 * General template implementation
 */

#define template_def	template<class _SampleT, int _NPoints>
#define Bezier_			Bezier<_SampleT, _NPoints>

#include <algorithm>

namespace intempo {

template_def Bezier_::Bezier() {
}

template_def Bezier_::Bezier(const std::vector<_SampleT> &points) {
	init<std::vector<_SampleT> >(points);
}

template_def Bezier_::Bezier(const std::list<_SampleT> &points) {
	init<std::list<_SampleT> >(points);
}

template_def template<class _ContainerT> Bezier_::Bezier(const _ContainerT &points) {
	init<_ContainerT>(points);
}

template_def Bezier_::Bezier(cvg_int numPoints, const _SampleT *points) {
	init(numPoints, points);
}

template_def Bezier_::Bezier(cvg_int numPoints, const _SampleT **points) {
	init(numPoints, points);
}

template_def void Bezier_::setControlPoints(const std::vector<_SampleT> &points) {
	init<std::vector<_SampleT> >(points);
}

template_def void Bezier_::setControlPoints(const std::list<_SampleT> &points) {
	init<std::list<_SampleT> >(points);
}

template_def template<class _ContainerT> void Bezier_::setControlPoints(const _ContainerT &points) {
	init<_ContainerT>(points);
}

template_def void Bezier_::setControlPoints(cvg_int numPoints, const _SampleT *points) {
	init(numPoints, points);
}

template_def void Bezier_::setControlPoints(cvg_int numPoints, const _SampleT **points) {
	init(numPoints, points);
}

template_def template<class _ContainerT> void Bezier_::init(const _ContainerT &points) {
	this->points.resize(points.size());
	this->aux.resize(points.size());
	std::copy(points.begin(), points.end(), this->points.begin());
}

template_def void Bezier_::init(cvg_int numPoints, const _SampleT *points) {
	this->points.resize(numPoints);
	this->aux.resize(points.size());
	for (cvg_int i = 0; i < numPoints; i++) this->points[i] = points[i];
}

template_def void Bezier_::init(cvg_int numPoints, const _SampleT **points) {
	this->points.resize(numPoints);
	this->aux.resize(points.size());
	for (cvg_int i = 0; i < numPoints; i++) this->points[i] = *points[i];
}

template_def _SampleT Bezier_::getControlPoint(cvg_uint index) {
	if (index >= points.size()) throw cvgException("[Bezier<>] getControlPoint()] Control point index out of bounds");
	return points[index];
}

template_def _SampleT Bezier_::solve(cvg_double t) {
	numAux = aux.size();
	aux = points;
	solveRecursive(t);
	return aux[0];
}

template_def void Bezier_::solveRecursive(cvg_double t) {
	if (numAux == 1) return;

	numAux--;
	for (cvg_int i = 0; i < numAux; i++)
		aux[i] = (1 - t) * aux[i] + t * aux[i + 1];

	solveRecursive(t);
}

#undef Bezier_
#undef template_def

/*
 * Template partial specialization for 4 points
 */

#define template_def	template<class _SampleT>
#define Bezier_			Bezier<_SampleT, 4>

template_def Bezier_::Bezier() {
}

template_def Bezier_::Bezier(const std::vector<_SampleT> &points) {
	init(points[0], points[1], points[2], points[3]);
}

template_def Bezier_::Bezier(const std::list<_SampleT> &points) {
	init(points);
}

template_def template<class _ContainerT> Bezier_::Bezier(const _ContainerT &points) {
	init(points);
}

template_def Bezier_::Bezier(const _SampleT &p0, const _SampleT &p1, const _SampleT &p2, const _SampleT &p3) {
	init(p0, p1, p2, p3);
}

template_def Bezier_::Bezier(const _SampleT *samples) {
	init(samples);
}

template_def Bezier_::Bezier(const _SampleT **samples) {
	init(samples);
}

template_def void Bezier_::setControlPoints(const std::vector<_SampleT> &points) {
	init(points[0], points[1], points[2], points[3]);
}

template_def void Bezier_::setControlPoints(const std::list<_SampleT> &points) {
	init(points);
}

template_def template<class _ContainerT> void Bezier_::setControlPoints(const _ContainerT &points) {
	init(points);
}

template_def void Bezier_::setControlPoints(const _SampleT &p0, const _SampleT &p1, const _SampleT &p2, const _SampleT &p3) {
	init(p0, p1, p2, p3);
}

template_def void Bezier_::setControlPoints(const _SampleT *samples) {
	init(samples);
}

template_def void Bezier_::setControlPoints(const _SampleT **samples) {
	init(samples);
}

template_def void Bezier_::init(const _SampleT &p0, const _SampleT &p1, const _SampleT &p2, const _SampleT &p3) {
	this->points[0] = p0;
	this->points[1] = p1;
	this->points[2] = p2;
	this->points[3] = p3;
}

template_def void Bezier_::init(const _SampleT *points) {
	this->points[0] = points[0];
	this->points[1] = points[1];
	this->points[2] = points[2];
	this->points[3] = points[3];
}

template_def void Bezier_::init(const _SampleT **points) {
	this->points[0] = *points[0];
	this->points[1] = *points[1];
	this->points[2] = *points[2];
	this->points[3] = *points[3];
}

template_def template<class _ContainerT> void Bezier_::init(const _ContainerT &points) {
	const _SampleT *p[4];
	typename _ContainerT::const_iterator it = points.begin();
	p[0] = &(*it);
	p[1] = &(*(++it));
	p[2] = &(*(++it));
	p[3] = &(*(++it));
	init(p);
}

template_def _SampleT Bezier_::getControlPoint(cvg_uint index) {
	if (index >= 4) throw cvgException("[Bezier<,4>] getControlPoint()] Control point index out of [0, 3]");
	return points[index];
}

template_def _SampleT Bezier_::solve(cvg_double t) {
    _SampleT a1 = (1 - t) * points[0] + t * points[1];
    _SampleT a2 = (1 - t) * points[1] + t * points[2];
    _SampleT a3 = (1 - t) * points[2] + t * points[3];
    _SampleT b1 = (1 - t) * a1 + t * a2;
    _SampleT b2 = (1 - t) * a2 + t * a3;
    return (1 - t) * b1 + t * b2;
}

}

#undef Bezier_
#undef template_def
