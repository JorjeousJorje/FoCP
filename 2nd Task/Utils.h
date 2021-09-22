#pragma once
#include <sciplot/Vec.hpp>
#include <limits>
#include <algorithm>

namespace Utils
{
	using FunctionType = std::function<double(double)>;



	template<class T>
	std::enable_if_t<!std::numeric_limits<T>::is_integer, bool>
		AlmostEqual(T x, T y, const double ulp = 10.0) {
		return std::fabs(x - y) <= std::numeric_limits<T>::epsilon() * std::fabs(x + y) * ulp
			|| std::fabs(x - y) < DBL_MIN;
	}


	template <typename T0, typename T1>
	sciplot::Vec GenerateLinspace(T0 iX0, T1 iX1, const std::size_t iIntervalCount) {
		sciplot::Vec oLinspace(iIntervalCount + 1);
		auto step = (iX1 - iX0) / static_cast<double>(iIntervalCount);
		for (std::size_t i = 0; i <= iIntervalCount; ++i) {
			oLinspace[i] = iX0 + static_cast<double>(i) * step;
		}

		return oLinspace;
	}

	template <typename T0, typename T1>
	sciplot::Vec GenerateLinspaceWithStep(T0 iX0, T1 iX1, const double iStep) {
		auto numSteps = static_cast<std::size_t>((iX1 - iX0) / iStep);
		return GenerateLinspace(iX0, iX1, numSteps);
	}

	template<class Function>
	sciplot::Vec GenerateFunctionValues(sciplot::Vec& iX, Function iFunc) {
		sciplot::Vec oFunctionValues(iX.size() );

		std::transform(std::begin(iX), std::end(iX),
						std::begin(oFunctionValues), iFunc);
		return oFunctionValues;
	}

	template<class Function>
	double ComputeDerivative(Function Func, const double iX, const double iDelta = 0.001) {
		return (Func(iX + iDelta) - Func(iX)) / iDelta;
	}

	template<class Function>
	double Compute2ndDerivative(Function Func, const double iX, const double iDelta = 0.001) {

		return (ComputeDerivative(Func, iX + iDelta, iDelta) - ComputeDerivative(Func, iX, iDelta)) / iDelta;
	}


	template<class Function>
	sciplot::Vec ComputeDerivativeValues(const sciplot::Vec& iX, Function iFunc, const double iDelta = 0.001) {
		sciplot::Vec oDerivativeValues(iX.size());

		auto DerivativeFunction = [&](const double _iX) {return (iFunc(_iX + iDelta) - iFunc(_iX)) / iDelta; };
		std::transform(std::begin(iX), std::end(iX),
						std::begin(oDerivativeValues), DerivativeFunction);

		return oDerivativeValues;
	}


	inline sciplot::Vec GenerateZeroArray(const std::size_t iCount) {
		sciplot::Vec oValues(iCount);
		std::fill(std::begin(oValues), std::end(oValues), 0.0);
		return oValues;
	}


	inline sciplot::Vec GenerateNumberArray(const std::size_t iCount, const double iNumber) {
		sciplot::Vec oValues(iCount);
		std::fill(std::begin(oValues), std::end(oValues), iNumber);
		return oValues;
	}
}
