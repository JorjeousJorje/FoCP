#include <iostream>
#include <colorconsole/color.hpp>
#include "BesselCalculator.h"
#include <iomanip>
#include <numeric>
#include <numbers>


using namespace Utils;
using namespace std::numbers;

int main() {

	const auto segmentUnderStudy = GenerateLinspaceWithStep(0.0, 2.0 * pi_v<double>, 0.01);

	for (const auto x : segmentUnderStudy) {
		const auto bessel_1 = BesselCalculator::CalculateBessel<SimpsonMethod>(x, 1, 5000, 10000);
		const auto bessel_0_derivative = BesselCalculator::CalculateBesselDerivative<SimpsonMethod>(x, 0, 5000, 10000, 10e-9);
		std::cout << dye::green("at ") + dye::purple("x = " + std::to_string(x) + " ");
		std::cout << bessel_1 + bessel_0_derivative << std::endl;
		// std::cout << std::boolalpha << AlmostEqual(bessel_1 + bessel_0_derivative, 10e-10, 5) << std::endl;
	}

}
