
#include <cmath>
#include <iostream>
#include <sciplot/sciplot.hpp>

#include "2nd Task/Utils.h"


using namespace Utils;
using namespace sciplot;

double interpolateLagrange(const Vec& iYValues, const Vec& iXValues, const double iX) {
	double result = 0;
	for (auto i = 0u; i < iXValues.size(); ++i) {

		double term = iYValues[i];
		for (auto j = 0u; j < iXValues.size(); ++j) {

			if (i != j) 
				term *= (iX - iXValues[j]) / (iXValues[i] - iXValues[j]);
		}
		result += term;
	}
	return result;
}

int main() {
	const auto nArray = GenerateLinspaceWithStep(4, 15, 1);


	std::vector<std::pair<Vec, Vec>> resultSequences{};
	for(const auto n : nArray) {
		auto kArray = GenerateLinspaceWithStep(0, n, 1);


		Vec xSequence(kArray.size());

		for (auto i = 0u; i < kArray.size(); ++i) {
			xSequence[i] = 1.0 + kArray[i] / n;
		}

		auto ySequence = std::log(xSequence);
		resultSequences.emplace_back(xSequence , ySequence);
	}

	Plot plot;
	for(const auto& [x, yToInterpolate]: resultSequences) {


		const auto xValues = GenerateLinspace(x[0], x[x.size() - 1], 1000);
		const auto yValues = std::log(xValues);

		Vec interpolatedY(yValues.size());
		for (auto i = 0u; i < xValues.size(); ++i) {
			interpolatedY[i] = interpolateLagrange(yToInterpolate, x, xValues[i]);
		}

		plot.drawCurve(xValues, interpolatedY - yValues).
			lineWidth(2).
			label("Pn(x) - Ln(x) with n = " + std::to_string(yToInterpolate.size() - 1));
	}

	plot.size(800, 500);
	plot.show();


	return 0;

}