#include <iostream>
#include <colorconsole/color.hpp>
#include "BesselCalculator.h"
#include <iomanip>
#include <numeric>
#include <numbers>
#include <cmath>


using namespace Utils;
using namespace std::numbers;

int main() {

	const auto segmentUnderStudy = GenerateLinspaceWithStep(0.0, 2.0 * pi_v<double>, 0.01);

	for (const auto x : segmentUnderStudy) {
		const auto bessel_1 = BesselCalculator::CalculateBessel<SimpsonMethod>(x, 1, 1000);
		const auto bessel_0_derivative = BesselCalculator::CalculateBesselDerivative<SimpsonMethod>(x, 0, 1000, 10e-6);
		std::cout << "at " + dye::light_purple("x = " + std::to_string(x) + " ");
		std::cout << dye::light_aqua(std::abs(bessel_1 + bessel_0_derivative)) << " less than 10e-10: ";

		if (std::abs(bessel_1 + bessel_0_derivative) < 10e-10) {
			std::cout << dye::light_green("true!") << std::endl;
		} else {
			std::cout << dye::red("false!") << std::endl;
		}
	}

}
