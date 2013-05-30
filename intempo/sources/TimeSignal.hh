/*
 * TimeSignal.cpp
 *
 *  Created on: 27/11/2012
 *      Author: Ignacio Mellado-Bataller
 */

#include <list>

namespace intempo {

#define TIME_SIGNAL_TIME_INC_OUTSIDE_BOUNDS		1.0

#define template_def	template<class _T>
#define TimeSignal_		TimeSignal<_T>

template_def TimeSignal_::TimeSignal() {
	dirty = false;
	currentKeyPoint = keypoints.end();
}

template_def TimeSignal_::~TimeSignal() {
}

template_def void TimeSignal_::sort(cvg_bool defer) {
	if (!defer) {
		keypoints.sort();
		if (currentKeyPoint == keypoints.end()) currentKeyPoint = keypoints.begin();
	}
	dirty = defer;
}

template_def void TimeSignal_::addKeyPoint(cvg_double time, const _T &value, cvg_bool deferredSort) {
	addKeyPoint(KeyPoint(time, value));
}

template_def void TimeSignal_::addKeyPoint(const KeyPoint &keyPoint, cvg_bool deferredSort) {
	keypoints.push_back(keyPoint);
	sort(deferredSort);
}

template_def void TimeSignal_::addKeyPoints(::std::list<KeyPoint> &keyPoints, cvg_bool deferredSort) {
	typename ::std::list<_T>::iterator it;
	for(typename ::std::list<KeyPoint>::iterator it = keyPoints.begin(); it != keyPoints.end(); it++)
		keypoints.push_back(*it);
	sort(deferredSort);
}

template_def void TimeSignal_::removeKeyPoint(cvg_double time) {
	for (typename ::std::list<KeyPoint>::iterator it = keypoints.begin(); it != keypoints.end(); it++) {
		if (it->time == time) {
			// Relocate the current key point
			if (currentKeyPoint == it) {
				currentKeyPoint++;
				if (currentKeyPoint == keypoints.end()) {
					currentKeyPoint = it;
					if (currentKeyPoint == keypoints.begin()) currentKeyPoint = keypoints.end();
					else currentKeyPoint--;
				}
			}
			keypoints.erase(it);
			return;
		}
	}
}

template_def void TimeSignal_::removeAllKeyPoints() {
	keypoints.clear();
	currentKeyPoint = keypoints.end();
}

template_def void TimeSignal_::getNeighborKeyPoints(cvg_double time, cvg_int numNeighbors, KeyPoint *neighbors) {
	if (keypoints.size() == 0) throw cvgException("[TimeSignal::getNeighborKeyPoints] No keypoints in this signal");

	if (keypoints.size() == 1) {
		cvg_double t = time - TIME_SIGNAL_TIME_INC_OUTSIDE_BOUNDS * (numNeighbors / 2 - 1);
		for (cvg_int i = 0; i < numNeighbors; i++) {
			neighbors[i] = keypoints.front();
			neighbors[i].time = t;
			t += TIME_SIGNAL_TIME_INC_OUTSIDE_BOUNDS;
		}
		return;
	}

	if (dirty) sort(false);

	// Time is inside bounds
	if (time >= keypoints.begin()->time && time <= keypoints.back().time) {

		// Find nearest key point
		if (time > currentKeyPoint->time) {
			while(currentKeyPoint != keypoints.end() && time > currentKeyPoint->time) currentKeyPoint++;
			if (currentKeyPoint == keypoints.end()) currentKeyPoint--;
			else {
				// Select closest key point in time between next and previous
				typename ::std::list<KeyPoint>::iterator it = currentKeyPoint;
				it--;
				if (fabs(time - it->time) < fabs(currentKeyPoint->time - time)) {
					currentKeyPoint--;
				}
			}
		} else if (time < currentKeyPoint->time) {
			while(currentKeyPoint != keypoints.begin() && time < currentKeyPoint->time) currentKeyPoint--;
			// Select closest key point in time between next and previous
			typename ::std::list<KeyPoint>::iterator it = currentKeyPoint;
			it++;
			if (fabs(it->time - time) < fabs(time - currentKeyPoint->time)) {
				currentKeyPoint++;
			}
		}

		// Select the output vector index that corresponds to the closest key point, so the current time is as centered as possible in the interval
		cvg_int midIndex;
		if (time >= currentKeyPoint->time)
			midIndex = ceil(numNeighbors / 2.0) - 1;
		else
			midIndex = floor(numNeighbors / 2.0);

		// Copy previous key points to the output buffer
		typename ::std::list<KeyPoint>::iterator it = currentKeyPoint;
		cvg_double inc = 0.0;
		for (cvg_int i = midIndex - 1; i >= 0; i--) {
			if (it == keypoints.begin()) it = keypoints.end();
			else if (it != keypoints.end()) it--;

			if (it != keypoints.end()) {
				neighbors[i] = *it;
			} else {
				neighbors[i] = keypoints.front();
				inc -= TIME_SIGNAL_TIME_INC_OUTSIDE_BOUNDS;
				neighbors[i].time += inc;
			}
		}
		// Copy current and next key points to the output buffer
		it = currentKeyPoint;
		inc = 0.0;
		for (cvg_int i = midIndex; i < numNeighbors; i++) {
			if (it != keypoints.end()) {
				neighbors[i] = *it;
			} else {
				neighbors[i] = keypoints.back();
				inc += TIME_SIGNAL_TIME_INC_OUTSIDE_BOUNDS;
				neighbors[i].time += inc;
			}

			if (it != keypoints.end()) it++;
		}

	} else {

		// Time is out of bounds. Generate time vector maintaining the time sequence.
		if (time < keypoints.begin()->time) {
			currentKeyPoint = keypoints.begin();
			cvg_double t = time - TIME_SIGNAL_TIME_INC_OUTSIDE_BOUNDS * (numNeighbors / 2 - 1);
			typename ::std::list<KeyPoint>::iterator it = keypoints.begin();
			cvg_bool gotOffset = false; cvg_double offset = 0.0; cvg_int offsetIndex = 0;
			for (cvg_int i = 0; i < numNeighbors; i++) {
				neighbors[i] = *it;
				if (t < keypoints.begin()->time) {
					neighbors[i].time = t;
					t += TIME_SIGNAL_TIME_INC_OUTSIDE_BOUNDS;
				} else {
					if (!gotOffset) { offset = keypoints.begin()->time - t; offsetIndex = i; gotOffset = true; }
					it++;
				}
			}
			if (gotOffset) for (cvg_int i = 0; i < offsetIndex; i++) neighbors[i].time += offset;
		} else {
			currentKeyPoint = --keypoints.end();
			cvg_double t = time + TIME_SIGNAL_TIME_INC_OUTSIDE_BOUNDS * (numNeighbors / 2.0 - 1.0);
			typename ::std::list<KeyPoint>::iterator it = --keypoints.end();
			cvg_bool gotOffset = false; cvg_double offset = 0.0; cvg_int offsetIndex = 0;
			for (cvg_int i = (cvg_int)numNeighbors - 1; i >= 0; i--) {
				neighbors[i] = *it;
				if (t > keypoints.back().time) {
					neighbors[i].time = t;
					t -= TIME_SIGNAL_TIME_INC_OUTSIDE_BOUNDS;
				} else {
					if (!gotOffset) { offset = keypoints.back().time - t; offsetIndex = i; gotOffset = true; }
					it--;
				}
			}
			if (gotOffset) for (cvg_int i = offsetIndex + 1; i < numNeighbors; i++) neighbors[i].time += offset;
		}

	}
}

template_def cvg_bool TimeSignal_::getKeyPoint(cvg_double time, TimeSignal_::KeyPoint *kp) {
	for (typename std::list<KeyPoint>::iterator it = keypoints.begin(); it != keypoints.end(); it++) {
		if (it->time == time) { 
			if (kp != NULL) (*kp) = (*it);
			return true; 
		}
	}
	return false;
}

#undef TIME_SIGNAL_TIME_INC_OUTSIDE_BOUNDS
#undef template_def
#undef TimeSignal_

}
