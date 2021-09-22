#pragma once
#include "RootSearchMethod.h"


template<double LeftBoundary, double RightBoundary>
class DichotomyMethod : public RootSearchMethod<LeftBoundary> {

	using RootSearchMethod<LeftBoundary>::_startPoint;
	using RootSearchMethod<LeftBoundary>::_toleranceUnit;
	using RootSearchMethod<LeftBoundary>::_function;

	double _rightBoundary{ RightBoundary };
public:

	std::optional<double> FindRoot(const double iUlpPrecision = 10) override {
		if (ValidateFunction().has_value()) {


			auto midPoint = 0.0;
			while (_rightBoundary - _startPoint > iUlpPrecision * _toleranceUnit) {
				midPoint = (_startPoint + _rightBoundary) / 2.0;

				if (_function(_startPoint) * _function(midPoint) < 0.0)
					_rightBoundary = midPoint;
				else
					_startPoint = midPoint;
			}

			const auto resultRoot = midPoint;
			return resultRoot;
		}
		return std::nullopt;
	}
private:

	std::optional<bool> ValidateFunction() const {
		auto validateResult = _function(_startPoint) * _function(_rightBoundary);
		if (validateResult < 0.0) {
			return std::optional{ true };
		}
		std::cout << typeid(*this).name();
		std::cout << ": Invalid function!" << std::endl;
		return std::nullopt;
	}
};


