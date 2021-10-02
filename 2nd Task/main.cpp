#include <cmath>
#include <iostream>
#include <sciplot/sciplot.hpp>

#include "Utils.h"
#include "Solver.h"

using namespace sciplot;
using namespace Utils;

constexpr double U0 = 1;
constexpr double a = 1;
//constexpr double rootStartingPoint = -999.5;
//constexpr double leftBoundary = -999.8;
//constexpr double rightBoundary = -800.0;

constexpr double rootStartingPoint = -0.5;
constexpr double leftBoundary = -0.99;
constexpr double rightBoundary = 0.0;

double WaveFunction(const double x) {
	return -std::sqrt(-U0 / x - 1.0)
		+ 1.0 / std::tan(std::sqrt(2.0 * a * a * U0 * (1.0 + x / U0)));
}

constexpr auto currentFunc = WaveFunction;

Plot plot;

void setupPlot() {
	plot.size(800, 500);
	plot.xrange(leftBoundary, rightBoundary + 2.0);
}

void plotFunc() {
	auto x = GenerateLinspace(leftBoundary, rightBoundary + 2.0, 1000);
	auto y = GenerateFunctionValues(x, currentFunc);

	plot.drawCurve(x, GenerateZeroArray(x.size())).
				lineWidth(1).
				lineColor("black").
				label("");

	plot.drawCurve(x, y).
				lineWidth(2).
				label("Wave Function").
				lineColor("blue");
}

void plotRoot(const double iRoot, const int iLineWidth, const std::string& iLabel, const std::string& iColor) {
	plot.drawCurveWithPoints(Vec{ iRoot }, Vec{ 0.0 }).
				lineWidth(iLineWidth).
				label(iLabel + std::to_string(iRoot)).
				lineColor(iColor);
}

template<class Solver>
std::optional<double> calculateRoot() {
	Solver solver{};


	const auto result = solver.Solve(currentFunc, 10e3);

	if (result.has_value()) {
		return result.value();
	}
	std::cout << "no root found" << std::endl;
	return std::nullopt;
	
}



int main() {

	setupPlot();
	plotFunc();

	const auto result_d = calculateRoot<Solver<DichotomyMethod<-1.0, 0.0>>>();
	if (result_d.has_value()) {
		plotRoot(result_d.value(), 10, "Dichotomy root: ", "red");
	}

	const auto result_s = calculateRoot<Solver<SimpleIterationsMethod<-0.5>>>();
	if (result_s.has_value()) {
		plotRoot(result_s.value(), 7, "Simple iterations root: ", "purple");
	}

	const auto result_nw = calculateRoot<Solver<NewtonMethod<-0.5>>>();
	if (result_nw.has_value()) {
		plotRoot(result_nw.value(), 3, "Newton method root: ", "yellow");
	}

	plot.show();



	return 0;

}
