#include <cmath>
#include <iostream>
#include <sciplot/sciplot.hpp>

#include "Utils.h"
#include "Solver.h"

using namespace sciplot;
using namespace Utils;

double U0 = 1000;
double a = 10;

double WaveFunction(const double x) {
	return -std::sqrt(-U0 / x - 1.0)
		+ 1.0 / std::tan(std::sqrt(2.0 * a * a * U0 * (1.0 + x / U0)));
}

constexpr auto currentFunc = WaveFunction;
constexpr double rootStartingPoint = -4.7;
constexpr double leftBoundary = -20.0;
constexpr double rightBoundary = -2.0;

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

void plotRoots(const double si_root, const double nw_root, const double di_root) {
	plot.drawCurveWithPoints(Vec{ si_root }, Vec{ 0.0 }).
				lineWidth(10).
				label("Simple iterations root").
				lineColor("red");

	plot.drawCurveWithPoints(Vec{ nw_root }, Vec{ 0.0 }).
				lineWidth(7).
				label("Newton root").
				lineColor("purple");

	plot.drawCurveWithPoints(Vec{ di_root }, Vec{ 0.0 }).
				lineWidth(3).
				label("Dichotomy root").
				lineColor("yellow");
}

void calculateRoot() {
	Solver<DichotomyMethod<rootStartingPoint, rightBoundary>> di_solver;
	Solver<SimpleIterationsMethod<rootStartingPoint>> si_solver;
	Solver<NewtonMethod<rootStartingPoint>> nw_solver;


	const auto di_result = di_solver.Solve(currentFunc, 10e3);
	const auto si_result = si_solver.Solve(currentFunc, 10e3);
	const auto nw_result = nw_solver.Solve(currentFunc, 10e3);

	if (si_result.has_value()) {
		plotRoots(si_result.value(), nw_result.value(), di_result.value());
	}
	else
		std::cout << "no root found" << std::endl;
}



int main() {

	setupPlot();
	plotFunc();
	calculateRoot();

	plot.show();

	return 0;

}
