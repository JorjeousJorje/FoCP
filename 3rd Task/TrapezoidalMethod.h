#pragma once
#include <cmath>

class TrapezoidalMethod {

public:
	double _precisionOrder{ 4.0 };

	template<class Function>
	double operator()(Function iFunc, const double iX0, const double iX1) {
		return  std::abs(iX0 - iX1) * (iFunc(iX0) + iFunc(iX1)) / 2.0;
	}
};