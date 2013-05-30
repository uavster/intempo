Intempo
=======
Intempo is an interpolation C++ template library with many different interpolation methods.

With Intempo, you can do things like:

    #include <intempo.h>
    using namespace intempo;
    ...
    TimeSignal<double> mySignal;
    mySignal.addKeyPoint(0.0, 1.2);	// Signal value is 1.2 at 0.0
    mySignal.addKeyPoint(1.0, 4.3); // Signal value is 4.3 at 1.0
    
    CubicInterpolator<double> ci(signal);
    double someValueInBetween = ci.getValue(2.8);

In fact, you can interpolate whatever objects that have definitions for operators * and +. If you use Atlante's Vector3 objects, for instance, you can do:

    TimeSignal<Vector3> mySignal;
    mySignal.addKeyPoint(0.0, Vector3(0, 0, 0));
    mySignal.addKeyPoint(1.0, Vector3(1, 0 ,0));
    mySignal.addKeyPoint(2.0, Vector3(0, 1, 0));
    
    LinearInterpolator<double> li(signal);
    // Resample signal in [-0.5, 2.5) with sampling period 0.1
    for (double time = -0.5; time < 2.5; time += 0.1) {
        Vector3 sample = li.getValue(time);
        // Do something with the sample
        ...
    }

With Intempo, you can also interpolate things in a spherical subspace of radius 1. This is especially useful to interpolate rotations with quaternions. For instance, using Atlante's Quaternion, you can do:

    TimeSignal<Quaternion> mySignal;
    mySignal.addKeyPoint(0.0, Vector3(0, 0, 0));
    mySignal.addKeyPoint(1.0, Vector3(1, 0 ,0));
    mySignal.addKeyPoint(2.0, Vector3(0, 1, 0));
    
    CubicInterpolator<Quaternion, SUBSPACE_SPHERICAL> ci(signal);
    // Resample signal in [-0.5, 2.5) with sampling period 0.1
    for (double time = -0.5; time < 2.5; time += 0.1) {
        Quaternion sample = ci.getValue(time);
        // Do something with the sample
        ...
    }

The CubicInterpolator defaults to the Catmull-Rom method, but you can also use it with the Finite Differences method by specifying a second template parameter:

    CubicInterpolator<Quaternion, SUBSPACE_SPHERICAL, CSPLINE_FINITE_DIFF> ci(signal);

The best way to learn how to use Intempo is by browsing the examples folder.

Making your objects interpolable
--------------------------------
For a sample class to be interpolable, they must define operators for sum (+) and multiplication (*):

- \+ : The sum operator will add two objects of the class and return the result as another object of the same class.
- \* : The multiplication operator will multiply an object of the class and a double and return the result as another object of the class.

In addition, **only if you need to interpolate in the spherical subspace**, the following additional methods must be defined for signal samples:

- hProduct(sample) : It performs the hamiltonian product between the object and another sample and returns the result as a sample
- inverse() : It returns the inverse of the object as another sample
- log() : It returns the natural logarithm of the object as another sample
- exp() : It returns the exponential of the object as another sample

Installing Intempo
------------------
1. If you don't have Atlante in your system, install it first from https://github.com/uavster/atlante
2. Install Intempo with CMake as you would normally do:

        mkdir build
        cd build
        cmake ..
        sudo make install

Using Intempo in your project
------------------------------
You can use Intempo in your code by just adding `#include <intempo.h>` but, first, you must add the package to your project depending on what you are using to compile it.

### With CMake
As you would do to use any other package, add packages ATLANTE and INTEMPO to your CMakeLists.txt. This can be done with the follwing lines:

    find_package(ATLANTE)
    include_directories(${ATLANTE_INCLUDE_DIRS})
    link_libraries(${ATLANTE_LIBRARIES})
    
    find_package(INTEMPO)
    include_directories(${INTEMPO_INCLUDE_DIRS})

###With your own makefiles
You can add packages ATLANTE and INTEMPO to your command line with pkg-config.

Add this to your compiler command line:

    `pkg-config --cflags atlante` `pkg-config --cflags intempo`

Add this to your linker command line:

    `pkg-config --libs atlante`

Contact
-------
If you have any suggestion, please go to http://uavster.com/contact

Contributors
------------
[Ignacio M. Bataller](https://github.com/uavster): Original project creator and maintainer
