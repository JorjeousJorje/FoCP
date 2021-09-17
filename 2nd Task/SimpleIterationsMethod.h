#pragma once
#pragma once
#include <optional>


template<double StartPoint, double StartLambda = -0.01>
class SimpleIterationsMethod {

	double _startPoint{ StartPoint };
	double _startLambda{ StartLambda };
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

		return iCurrentPoint - _startLambda * iFunc(iCurrentPoint);
	}


};

