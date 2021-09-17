#pragma once
#pragma once
#pragma once
#include <optional>
#include "Utils.h"

template<double StartPoint, double DerivativePrecision = 0.0001>
class NewtonMethod {

	double _startPoint{ StartPoint };
	double _derivativePrecision{ DerivativePrecision };
	double _toleranceUnit{ std::numeric_limits<double>::epsilon() };
public:

	template<class Function>
	std::optional<double> Solve(Function iFunc, const int iUlpPrecision = 10) {
		auto startPoint = _startPoint;
		auto resultRoot = _startPoint;

		while (std::abs(CalculateNextStep(iFunc, startPoint) - resultRoot) > iUlpPrecision * _toleranceUnit) {
			resultRoot = CalculateNextStep(iFunc, startPoint);
			startPoint = resultRoot;

		}

		return std::optional{ resultRoot };
	}
private:

	template<class Function>
	double CalculateNextStep(Function iFunc, const double iCurrentPoint) {
		auto derivative = Utils::ComputeDerivative(iFunc, iCurrentPoint, _derivativePrecision);
		return iCurrentPoint - iFunc(iCurrentPoint) / derivative;
	}

};

