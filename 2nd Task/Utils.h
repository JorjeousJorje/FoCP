#pragma once
#include <sciplot/Vec.hpp>

using namespace sciplot;
namespace Utils
{

	template <typename T0, typename T1, typename U = double>
	Vec GenerateLinspace(T0 iX0, T1 iX1, std::size_t iIntervalCount)
	{
		Vec oLinspace(iIntervalCount + 1);
		auto step = (iX1 - iX0) / static_cast<double>(iIntervalCount);
		for (std::size_t i = 0; i <= iIntervalCount; ++i) {
			oLinspace[i] = iX0 + static_cast<double>(i) * step;
		}

		return oLinspace;
	}

	template<class Function>
	Vec GenerateFunctionValues(Vec& iX, Function iFunc) {
		Vec oFunctionValues(iX.size() );

		std::transform(std::begin(iX), std::end(iX),
						std::begin(oFunctionValues), iFunc);
		return oFunctionValues;
	}

	template<class Function>
	double ComputeDerivative(Function Func, const double iX, const double iDelta = 0.001) {
		return (Func(iX + iDelta) - Func(iX)) / iDelta;
	}


	template<class Function>
	Vec ComputeDerivativeValues(const Vec& iX, Function iFunc, const double iDelta = 0.001) {
		Vec oDerivativeValues(iX.size());

		auto DerivativeFunction = [&](const double _iX) {return (iFunc(_iX + iDelta) - iFunc(_iX)) / iDelta; };
		std::transform(std::begin(iX), std::end(iX),
						std::begin(oDerivativeValues), DerivativeFunction);

		return oDerivativeValues;
	}


	inline Vec GenerateZeroArray(const std::size_t iCount) {
		Vec oValues(iCount);
		std::fill(std::begin(oValues), std::end(oValues), 0.0);
		return oValues;
	}


	inline Vec GenerateNumberArray(const std::size_t iCount, const double iNumber) {
		Vec oValues(iCount);
		std::fill(std::begin(oValues), std::end(oValues), iNumber);
		return oValues;
	}
}
