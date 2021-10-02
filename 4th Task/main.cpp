#include <iostream>
#include <sciplot/sciplot.hpp>
#include <colorconsole/color.hpp>

#include "BesselCalculator.h"
#include <iomanip>
#include <numeric>
#include <numbers>
#include <cmath>

using namespace Utils;
using namespace std::numbers;
using namespace sciplot;


int main() {

	const auto segmentUnderStudy = GenerateLinspace(0.0, 2.0 * pi_v<double>, 10000);


	std::vector<double> besselValues{};
	std::vector<double> besselDerivativeValues{};

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

		besselValues.push_back(bessel_1);
		besselDerivativeValues.push_back(bessel_0_derivative);
	}

	Plot plot;


	//plot.drawCurve(segmentUnderStudy, besselValues).
	//	lineWidth(2).
	//	label("Bessel_1 Function");


	std::vector<double> result(besselValues.size());

	for(auto i = 0u; i < besselDerivativeValues.size(); ++i) {
		result[i] = besselDerivativeValues[i] + besselValues[i];
	}

	plot.drawCurve(segmentUnderStudy, result).
		lineWidth(2).
		label("Bessel_0 + Bessel_1");

	plot.drawCurve(segmentUnderStudy, GenerateZeroArray(segmentUnderStudy.size())).
		lineWidth(1).
		lineColor("black").
		label("");

	plot.size(800, 500);
	plot.show();

}
