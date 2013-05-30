/*
 * TimeSignal.h
 *
 *  Created on: 27/11/2012
 *      Author: Ignacio Mellado-Bataller
 */

#ifndef TIMESIGNAL_H_
#define TIMESIGNAL_H_

#include <atlante.h>
#include <list>

namespace intempo {

template<class _T> class TimeSignal {
public:
	TimeSignal();
	virtual ~TimeSignal();

	class KeyPoint {
	public:
		cvg_double time;
		_T value;

		inline KeyPoint(cvg_double time, _T value) { this->time = time; this->value = value; }
		inline KeyPoint() { this->time = 0.0; }
		inline bool operator < (const KeyPoint &kp) { return time < kp.time; }
	};

	void addKeyPoint(cvg_double time, const _T &value, cvg_bool deferredSort = true);
	void addKeyPoint(const KeyPoint &keyPoint, cvg_bool deferredSort = true);
	void addKeyPoints(std::list<KeyPoint> &keyPoints, cvg_bool deferredSort = true);
	void removeKeyPoint(cvg_double time);
	void removeAllKeyPoints();

	cvg_bool getKeyPoint(cvg_double time, KeyPoint *kp = NULL);

	// WARNING: const is omitted for flexibility, but if any key point time is changed in outer code, the list MUST be resorted
	inline std::list<KeyPoint> &getKeyPoints() { if (dirty) sort(false); return keypoints; }

	void getNeighborKeyPoints(cvg_double time, cvg_int numNeighbors, KeyPoint *neighbors);

protected:
	void sort(cvg_bool defer);
private:
	std::list<KeyPoint> keypoints;
	typename std::list<KeyPoint>::iterator currentKeyPoint;
	cvg_bool dirty;		// If true, the list needs to be sorted
};

}

#include "../sources/TimeSignal.hh"

#endif /* TIMESIGNAL_H_ */
