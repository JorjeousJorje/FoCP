#pragma once
#pragma once
#pragma once
#include <optional>
#include "SimpleIterationsMethod.h"

template<double StartPoint, double DerivativePrecision = 0.0001>
class NewtonMethod : public SimpleIterationsMethod<StartPoint, DerivativePrecision> {
	using SimpleIterationsMethod<StartPoint>::_function;
	using SimpleIterationsMethod<StartPoint>::_derivativePrecision;


	double CalculateNextStep(const double iX) override {
		auto derivative = Utils::ComputeDerivative(_function, iX, _derivativePrecision);
		return iX - _function(iX) / derivative;
	}

};

