#pragma once

#include "CauchyProblemSolvingMethod.h"

class SecondOrderRKMethod : public CauchyProblemSolvingMethod {
	double _alpha;
	double _oneOver2Alpha{ 1.0 / (2.0 * _alpha) };
public:
	SecondOrderRKMethod(const double alpha) : _alpha{alpha}{}

	sciplot::Vec Solve(const InitialCondition& iInitCond, const sciplot::Vec& iTime, const Utils::FunctionType& iFunc) override {
		sciplot::Vec oSolution(iTime.size());
		oSolution[iInitCond.y0] = iInitCond.x0;

		for (std::size_t i = 0u; i < iTime.size() - 1; ++i) {
			const auto step = iTime[i + 1u] - iTime[i];

			const auto forecast = oSolution[i] + _alpha * step * iFunc(oSolution[i]);
			oSolution[i + 1u] = oSolution[i] + step * ((1 - _oneOver2Alpha) * iFunc(oSolution[i]) + _oneOver2Alpha * iFunc(forecast));
		}

		return oSolution;
	}
};