#pragma once
#include <optional>
#include <sciplot/sciplot.hpp>
#include "2nd Task/Utils.h"


struct InitialCondition {
	double x0;
	std::size_t y0;
};

class CauchyProblemSolvingMethod {



public:

	virtual ~CauchyProblemSolvingMethod() = default;
	virtual sciplot::Vec Solve(const InitialCondition& iInitCond, const sciplot::Vec&, const Utils::FunctionType&) = 0;
};
