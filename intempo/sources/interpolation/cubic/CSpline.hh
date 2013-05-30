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



