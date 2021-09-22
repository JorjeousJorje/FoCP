#include <iostream>
#include <colorconsole/color.hpp>
#include <numbers>

#include "Integrator.h"

constexpr std::size_t minNumIntervals = 2;
constexpr std::size_t maxNumIntervals = 256;

double Func1(const double iX) {
	return 1.0 / (1.0 + iX * iX);
}

double Func2(const double iX) {
	return std::pow(iX, 1.0 / 3.0) * std::exp(std::sin(iX));
}

template<class IntegrationMethod, class Function>
void CalculateIntegral(Function iFunc, const double iLeftBound, const double iRightBound) {

	std::cout << std::endl;
	std::cout << ">>> " << dye::green("Integrating using ") << dye::aqua(typeid(IntegrationMethod).name())
			  << std::endl << std::endl;

	for(auto step = minNumIntervals; step <= maxNumIntervals; step *= 2) {
		auto xValues = Utils::GenerateLinspace(iLeftBound, iRightBound, step);

		auto result = Integrator::IntegrateFunc<IntegrationMethod>(xValues, iFunc);
		std::cout << "Result with step count of " << step << " = " << result << std::endl;
	}
}

template<class IntegrationMethod, class Function>
void CalculateIntegralUsingRudge(Function iFunc, const double iLeftBound, const double iRightBound) {

	std::cout << std::endl;
	std::cout << dye::purple(" Rudge method: ") << std::endl;
	std::cout << ">>> " << dye::green("Integrating using ") << dye::aqua(typeid(IntegrationMethod).name())
		<< std::endl << std::endl;

	for (auto step = minNumIntervals; step <= maxNumIntervals; step *= 2) {
		auto xValuesLessSteps = Utils::GenerateLinspace(iLeftBound, iRightBound, step);
		auto xValuesMoreSteps = Utils::GenerateLinspace(iLeftBound, iRightBound, 3u * step);

		auto result = Integrator::IntegrateFunc<IntegrationMethod>(xValuesLessSteps, xValuesMoreSteps, iFunc);
		std::cout << "Result with step count of " << step << " = " << result << std::endl;
	}
}


int main() {


	bool useRudge = true;

	if (useRudge) {
		CalculateIntegralUsingRudge<SimpsonMethod>(Func1, -1.0, 1.0);
		std::cout << dye::purple("Analytical result: ");
		std::cout << std::numbers::pi_v<double> / 2.0 << std::endl;

		CalculateIntegralUsingRudge<TrapezoidalMethod>(Func1, -1.0, 1.0);
		std::cout << dye::purple("Analytical result: ");
		std::cout << std::numbers::pi_v<double> / 2.0 << std::endl;
	}
	else {
		CalculateIntegral<SimpsonMethod>(Func1, -1.0, 1.0);
		std::cout << dye::purple("Analytical result: ");
		std::cout << std::numbers::pi_v<double> / 2.0 << std::endl;

		CalculateIntegral<TrapezoidalMethod>(Func1, -1.0, 1.0);
		std::cout << dye::purple("Analytical result: ");
		std::cout << std::numbers::pi_v<double> / 2.0 << std::endl;
	}


	// CalculateIntegralUsingRudge<SimpsonMethod>(Func2, 0.0, 1.0);
	// CalculateIntegralUsingRudge<TrapezoidalMethod>(Func2, 0.0, 1.0);



}