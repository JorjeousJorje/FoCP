#pragma once
#include <optional>
#include <iostream>


template<double LeftBoundary, double RightBoundary>
class DichotomyMethod {

	double _leftBoundary{ LeftBoundary };
	double _rightBoundary{ RightBoundary };
	double _toleranceUnit{ std::numeric_limits<double>::epsilon() };
public:

	template<class Function>
	std::optional<double> Solve(Function iFunc, const int iUlpPrecision = 10) {
		if (ValidateFunction(iFunc).has_value()) {

			auto midPoint = 0.0;
			while (_rightBoundary - _leftBoundary > iUlpPrecision * _toleranceUnit) {
				midPoint = (_leftBoundary + _rightBoundary) / 2.0;

				if (iFunc(_leftBoundary) * iFunc(midPoint) < 0.0)
					_rightBoundary = midPoint;
				else
					_leftBoundary = midPoint;
			}

			const auto resultRoot = midPoint;
			return resultRoot;
		}
		return std::nullopt;
	}
private:

	template<class Function>
	std::optional<bool> ValidateFunction(Function iFunc) const {
		auto validateResult = iFunc(_leftBoundary) * iFunc(_rightBoundary);
		if (validateResult < 0.0) {
			return std::optional{ true };
		}
		std::cout << "Invalid function!" << std::endl;
		return std::nullopt;
	}
};


