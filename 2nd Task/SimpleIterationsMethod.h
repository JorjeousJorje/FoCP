#pragma once
#pragma once
#include "RootSearchMethod.h"
#include "Utils.h"

template<double StartPoint, double DerivativePrecision = 0.0001, double StartLambda = -0.01>
class SimpleIterationsMethod : public RootSearchMethod<StartPoint>{

	double _startLambda{ StartLambda };

protected:
	using RootSearchMethod<StartPoint>::_startPoint;
	using RootSearchMethod<StartPoint>::_toleranceUnit;
	using RootSearchMethod<StartPoint>::_function;
	double _derivativePrecision{ DerivativePrecision };

public:

	std::optional<double> FindRoot(const double iUlpPrecision = 10) override {

		if(Check—onvergence()) {
			auto startPoint = _startPoint;
			auto resultRoot = _startPoint;

			while (std::abs(CalculateNextStep(startPoint) - resultRoot) > iUlpPrecision * this->_toleranceUnit) {
				resultRoot = CalculateNextStep(startPoint);
				startPoint = resultRoot;
			}

			return std::optional{ resultRoot };
		}

		return std::nullopt;
	}
private:

	virtual double CalculateNextStep(const double iX) {

		return iX - _startLambda * _function(iX);
	}

	bool Check—onvergence() {

		const auto dFSquared = Utils::ComputeDerivative(_function, _startPoint, _derivativePrecision) * 
									 Utils::ComputeDerivative(_function, _startPoint, _derivativePrecision);
		const auto d2F = Utils::Compute2ndDerivative(_function, _startPoint, _derivativePrecision);

		if (std::abs(_function(_startPoint) * d2F) < dFSquared) {
			return true;
		}
		std::cout << typeid(*this).name();
		std::cout << " won't converge!" << std::endl;
		return false;
	}


};

