#pragma once


class SimpsonMethod {

public:
	double _precisionOrder{ 4.0 };

	template<class Function>
	double operator()(Function iFunc, const double iX0, const double iX1) {
		return (iX1 - iX0) / 6.0 * (iFunc(iX0) + 4.0 * iFunc((iX0 + iX1) / 2.0) + iFunc(iX1));
	}
};