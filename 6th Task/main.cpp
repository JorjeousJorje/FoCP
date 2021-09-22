#include <cmath>
#include <iostream>
#include <sciplot/sciplot.hpp>

#include "SolvingMethods.h"
#include "2nd Task/Utils.h"


using namespace Utils;
using namespace sciplot;

int main() {

	const auto t = GenerateLinspace(0.0, 3.0, 1000);
	constexpr auto f = [](const double x) { return -x; };
	const auto eulerSolution = EulerMethod{}.Solve({ 1.0, 0 }, t, f);
	const auto secondOrderRK_05 = SecondOrderRKMethod{0.5}.Solve({ 1.0, 0 }, t, f);
	const auto secondOrderRK_1 = SecondOrderRKMethod{ 1.0 }.Solve({ 1.0, 0 }, t, f);
	const auto secondOrderRK_075 = SecondOrderRKMethod{ 0.75 }.Solve({ 1.0, 0 }, t, f);
	const auto fourthOrderRK = FourthOrderRKMethod{}.Solve({ 1.0, 0 }, t, f);


	const auto analyticalSolution = std::exp(-t);

	Plot plot;

	//plot.drawCurve(t, analyticalSolution - eulerSolution).
	//		lineWidth(2).
	//		label("Euler solution");

	plot.drawCurve(t, analyticalSolution - secondOrderRK_1).
			lineWidth(2).
			label("RK2 solution with alpha = 1");

	plot.drawCurve(t, analyticalSolution - secondOrderRK_05).
			lineWidth(2).
			label("RK2 solution with alpha = 0.5");

	plot.drawCurve(t, analyticalSolution - secondOrderRK_075).
			lineWidth(2).
			label("RK2 solution with alpha = 0.75");

	plot.drawCurve(t, analyticalSolution - fourthOrderRK).
			lineWidth(2).
			label("RK4 solution");

	plot.size(800, 500);
	plot.show();

	return 0;
}