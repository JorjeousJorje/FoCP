#pragma once
#include <memory>
#include "SolveMethods.h"


template<class SolveMethod>
class Solver {
	std::unique_ptr<SolveMethod> _solveMethod { new SolveMethod };
public:

	template<class Function>
	std::optional<double> Solve(Function iFunc, const int iUlpPrecision = 10) {
		auto result = _solveMethod->Solve(iFunc, iUlpPrecision);
		if(result.has_value()) {
			return result.value();
		}
		return std::nullopt;
	}
};
