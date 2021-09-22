#pragma once
#include <iostream>
#include <numeric>
#include <optional>
#include <memory>
#include "Utils.h"


template<class SolveMethod>
class Solver;


template<double StartPoint>
class RootSearchMethod {

protected:
	Utils::FunctionType _function;
	double _toleranceUnit{ std::numeric_limits<double>::epsilon() };
	double _startPoint{ StartPoint };

public:

	virtual ~RootSearchMethod() = default;
	virtual std::optional<double> FindRoot(double iUlpPrecision) = 0;

private:

	friend Solver;
	friend void SetFunction(RootSearchMethod& iMethod, Utils::FunctionType function) {
		iMethod._function = std::move(function);
	}

};