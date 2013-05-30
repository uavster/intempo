#include <intempo.h>
#include <string>
#include <iostream>
#include <iomanip>

using namespace intempo;

int main() {
	// Create the signal and add key points
	TimeSignal<double> signal;
	signal.addKeyPoint(0.0, -1.0);
	signal.addKeyPoint(0.5, 0.0);
	signal.addKeyPoint(1.0, 1.5);
	signal.addKeyPoint(2.0, -0.4);
	signal.addKeyPoint(2.5, 0.8);
	
	// Create interpolators for the signal

	// ---- Order 0 interpolators ----

	// Nearest Neighbor interpolator
	NearestNeighborInterpolator<double> nni(signal);

	// Sample and Hold interpolator
	SampleHoldInterpolator<double> shi(signal);
	
	// ---- Order 1 interpolators ----

	// Linear interpolator (default subspace is SUBSPACE_WHOLE)
	LinearInterpolator<double> li_w(signal);

	// ---- Order 2 interpolators ----
	
	// Cubic interpolator (default subspace is SUBSPACE_WHOLE, default method is CSPLINE_CATMULL_ROM)
	CubicInterpolator<double> ci_w_cr(signal);

	// Cubic interpolator in the whole space with Finite Differences method
	CubicInterpolator<double, SUBSPACE_WHOLE, CSPLINE_FINITE_DIFF> ci_w_fd(signal);

	Interpolator<double> *interpolators[] = { &shi, &nni, &li_w, &ci_w_cr, &ci_w_fd };
	std::string names[] = 	{ 	
				"Sample and Hold", "Nearest Neighbor", 
				"Linear",
				"Cubic (Catmull-Rom)",
				"Cubic (Finite Differences)"
				};

	for (int i = 0; i < sizeof(interpolators) / sizeof(Interpolator<double> *); i++) {
		std::cout << names[i] << ":" << std::endl;
		for (double time = -0.5; time < 3.0; time += 0.125) {
			if (time > -0.5) std::cout << std::endl;
			std::cout << "(t=" << std::setw(6) << time << ")\t" << interpolators[i]->getValue(time);
			if (signal.getKeyPoint(time)) std::cout << "\t[key point]";
		}
		std::cout << std::endl << std::endl;
	}
	
	return 0;
}
