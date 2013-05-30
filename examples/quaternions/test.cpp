#include <intempo.h>
#include <atlante.h>

#include <string>
#include <iostream>
#include <iomanip>

using namespace intempo;

int main() {
	// Create the signal and add key points
	TimeSignal<Quaternion> signal;
	// Add each keypoint with time and value
	signal.addKeyPoint(0.0, Quaternion(Vector3(1, 0, 0), 0.0));
	signal.addKeyPoint(0.5, Quaternion(Vector3(0, 1, 0), M_PI / 2));
	signal.addKeyPoint(1.5, Quaternion(Vector3(0, 0, 1), M_PI / 4));
	
	// Create interpolators for the signal

	// ---- Order 0 interpolators ----

	// Nearest Neighbor interpolator
	NearestNeighborInterpolator<Quaternion> nni(signal);

	// Sample and Hold interpolator
	SampleHoldInterpolator<Quaternion> shi(signal);
	
	// ---- Order 1 interpolators ----

	// Linear interpolator, spherical subspace
	LinearInterpolator<Quaternion, SUBSPACE_SPHERICAL> li_s(signal);

	// ---- Order 2 interpolators ----
	
	// Cubic interpolator (default subspace is SUBSPACE_WHOLE, default method is CSPLINE_CATMULL_ROM)
	CubicInterpolator<Quaternion, SUBSPACE_SPHERICAL> ci_s_cr(signal);

	// Cubic interpolator in the whole space with Finite Differences method
	CubicInterpolator<Quaternion, SUBSPACE_SPHERICAL, CSPLINE_FINITE_DIFF> ci_s_fd(signal);

	Interpolator<Quaternion> *interpolators[] = { &shi, &nni, &li_s, &ci_s_cr, &ci_s_fd };
	std::string names[] = 	{ 	
				"Sample and Hold", "Nearest Neighbor", 
				"Linear (spherical subspace)",
				"Cubic (spherical subspace, Catmull-Rom)",
				"Cubic (spherical subspace, Finite Differences)"
				};

	for (int i = 0; i < sizeof(interpolators) / sizeof(Interpolator<Quaternion> *); i++) {
		std::cout << names[i] << ":" << std::endl;
		for (double time = -0.5; time < 2.0; time += 0.125) {
			if (time > -0.5) std::cout << std::endl;
			std::cout << "(t=" << std::setw(6) << time << ")\t" << interpolators[i]->getValue(time);
			if (signal.getKeyPoint(time)) std::cout << "\t[key point]";
		}
		std::cout << std::endl << std::endl;
	}
	
	return 0;
}
