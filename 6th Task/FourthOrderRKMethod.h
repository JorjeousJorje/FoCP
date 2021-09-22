#pragma once

#include "CauchyProblemSolvingMethod.h"

class FourthOrderRKMethod : public CauchyProblemSolvingMethod {
public:

	sciplot::Vec Solve(const InitialCondition& iInitCond, const sciplot::Vec& iTime, const Utils::FunctionType& iFunc) override {
		sciplot::Vec oSolution(iTime.size());
		oSolution[iInitCond.y0] = iInitCond.x0;

		for (std::size_t i = 0u; i < iTime.size() - 1; ++i) {
			const auto step = iTime[i + 1u] - iTime[i];

			const auto k1 = iFunc(oSolution[i]);
			const auto k2 = iFunc(oSolution[i] + step * k1 / 2.0);
			const auto k3 = iFunc(oSolution[i] + step * k2 / 2.0);
			const auto k4 = iFunc(oSolution[i] + step * k3);

			oSolution[i + 1u] = oSolution[i] + step * (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
		}

		return oSolution;
	}
};