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
