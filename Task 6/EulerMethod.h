#pragma once
#include "CauchyProblemSolvingMethod.h"


class EulerMethod : public CauchyProblemSolvingMethod {

	
public:

	sciplot::Vec Solve(const InitialCondition& iInitCond, const sciplot::Vec& iTime, const Utils::FunctionType& iFunc) override {
		sciplot::Vec oSolution(iTime.size());
		oSolution[iInitCond.y0] = iInitCond.x0;

		for (std::size_t i = 0u; i < iTime.size() - 1; ++i) {
			const auto step = iTime[i + 1u] - iTime[i];
			oSolution[i + 1u] = oSolution[i] + step * iFunc(oSolution[i]);
		}

		return oSolution;
	}
};