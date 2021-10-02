#include <iostream>
#include <sciplot/sciplot.hpp>
#include <colorconsole/color.hpp>
#include <numbers>
#include "Integrator.h"

#include "2nd Task/Utils.h"

using namespace sciplot;
using namespace Utils;


constexpr std::size_t minNumIntervals = 2;
constexpr std::size_t maxNumIntervals = 65536;

double Func1(const double iX) {
	return 1.0 / (1.0 + iX * iX);
}

double Func2(const double iX) {
	return std::pow(iX, 1.0 / 3.0) * std::exp(std::sin(iX));
}

template<class IntegrationMethod, class Function>
Vec CalculateIntegral(Function iFunc, const double iLeftBound, const double iRightBound) {

	std::cout << std::endl;
	std::cout << ">>> " << dye::green("Integrating using ") << dye::aqua(typeid(IntegrationMethod).name())
			  << std::endl << std::endl;


	Vec oIntegralValues(static_cast<unsigned>(std::log2(maxNumIntervals)));
	for(std::size_t step = minNumIntervals, i = 0u; step <= maxNumIntervals; step *= 2, ++i) {
		auto xValues = Utils::GenerateLinspace(iLeftBound, iRightBound, step);

		auto result = Integrator::IntegrateFunc<IntegrationMethod>(xValues, iFunc);
		std::cout << "Result with step count of " << step << " = " << result << std::endl;
		oIntegralValues[i] = result;
	}

	return oIntegralValues;
}


void plotKek() {

	Plot plot;

	constexpr auto analyticalSolution = std::numbers::pi_v <double> / 2.0;
	const auto v1 = CalculateIntegral<SimpsonMethod>(Func1, -1.0, 1.0);
	std::cout << dye::purple("Analytical result: ");
	std::cout << std::numbers::pi_v<double> / 2.0 << std::endl;

	auto x = Vec{ 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 };
	plot.drawCurveWithPoints(x, analyticalSolution - v1).
		lineWidth(2).
		label("SimpsonMethod error").
		lineColor("blue");

	auto y = GenerateFunctionValues(x, [](const double x) {return 1 / (x * x * x * x); });
	plot.drawCurve(x, y).
		lineWidth(2).
		label("SimpsonMethod theoretical error").
		lineColor("green");

	const auto v2 = CalculateIntegral<TrapezoidalMethod>(Func1, -1.0, 1.0);
	std::cout << dye::purple("Analytical result: ");
	std::cout << std::numbers::pi_v<double> / 2.0 << std::endl;

	plot.drawCurveWithPoints(x, analyticalSolution - v2).
		lineWidth(2).
		label("TrapezoidalMethod error").
		lineColor("red");

	const auto y1 = GenerateFunctionValues(x, [](const double x) {return 1 / (x * x); });
	plot.drawCurve(x, y1).
		lineWidth(2).
		label("TrapezoidalMethod theoretical error").
		lineColor("purple");


	plot.ytics().logscale();
	plot.xtics().logscale();
	plot.size(800, 500);
	plot.show();
}

void plotKek1() {

	Plot plot;

	constexpr auto analyticalSolution = std::numbers::pi_v <double> / 2.0;
	const auto v1 = CalculateIntegral<SimpsonMethod>(Func2, 0.0, 1.0);
	std::cout << dye::purple("Analytical result: ");
	std::cout << std::numbers::pi_v<double> / 2.0 << std::endl;

	auto x = Vec{ 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 };


	Vec v1_(v1.size() - 1);
	for (auto i = 0u; i < v1.size() - 1; ++i) {
		v1_[i] = v1[i + 1] - v1[i];
	}

	plot.drawCurveWithPoints(x, v1_).
		lineWidth(2).
		label("SimpsonMethod error").
		lineColor("blue");

	auto y = GenerateFunctionValues(x, [](const double x) {return 1 / (x * x * x * x); });
	plot.drawCurve(x, y).
		lineWidth(2).
		label("SimpsonMethod theoretical error").
		lineColor("green");

	const auto v2 = CalculateIntegral<TrapezoidalMethod>(Func2, 0.0, 1.0);
	std::cout << dye::purple("Analytical result: ");
	std::cout << std::numbers::pi_v<double> / 2.0 << std::endl;


	Vec v2_(v1.size() - 1);
	for (auto i = 0u; i < v1.size() - 1; ++i) {
		v2_[i] = v2[i + 1] - v2[i];
	}

	plot.drawCurveWithPoints(x, v2_).
		lineWidth(2).
		label("TrapezoidalMethod error").
		lineColor("red");

	const auto y1 = GenerateFunctionValues(x, [](const double x) {return 1 / (x * x); });
	plot.drawCurve(x, y1).
		lineWidth(2).
		label("TrapezoidalMethod theoretical error").
		lineColor("purple");


	plot.ytics().logscale();
	plot.xtics().logscale();
	plot.size(800, 500);
	plot.show();
}



int main() {

	plotKek1();

}