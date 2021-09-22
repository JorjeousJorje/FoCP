#pragma once
#include <memory>
#include "SolveMethods.h"


template<class SolveMethod>
class Solver {
	std::unique_ptr<SolveMethod> _solveMethod { new SolveMethod };
public:

	std::optional<double> Solve(Utils::FunctionType iFunc, const double iUlpPrecision = 10) {

		SetFunction(*_solveMethod, iFunc);
		auto result = _solveMethod->FindRoot(iUlpPrecision);

		if(result.has_value()) {
			return result.value();
		}
		return std::nullopt;
	}
};
