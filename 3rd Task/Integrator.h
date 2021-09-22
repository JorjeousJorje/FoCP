#pragma once
#include <cassert>
#include <memory>
#include "IntegrationMethods.h"
#include "2nd Task/Utils.h"


class Integrator {
public:

	template<class IntegrationMethod, class Function>
	static double IntegrateFunc(const sciplot::Vec& iXArray, Function iFunc) {
		double sum = 0;
		for (size_t ind1 = 0, ind2 = 1; ind2 < iXArray.size(); ++ind1, ++ind2) {
			sum += IntegrationMethod{}(iFunc, iXArray[ind1], iXArray[ind2]);
		}
		return sum;
	}

	template<class IntegrationMethod, class Function>
	static double IntegrateFunc(const sciplot::Vec& iXArrayLessSteps, const sciplot::Vec& iXArrayMoreSteps, Function iFunc) {

		assert(iXArrayLessSteps.size() < iXArrayMoreSteps.size());
		assert(Utils::AlmostEqual(iXArrayLessSteps[0], iXArrayMoreSteps[0]));
		assert(Utils::AlmostEqual(iXArrayLessSteps[iXArrayLessSteps.size() - 1], 
								  iXArrayMoreSteps[iXArrayMoreSteps.size() - 1]));

		const auto method = IntegrationMethod{};

		const auto r = static_cast<double>(iXArrayMoreSteps.size()) / static_cast<double>(iXArrayLessSteps.size());
		const auto rPowered = std::pow(r, method._precisionOrder);

		double sumLessSteps = IntegrateFunc<IntegrationMethod>(iXArrayLessSteps, iFunc);
		double sumMoreSteps = IntegrateFunc<IntegrationMethod>(iXArrayMoreSteps, iFunc);

		auto resultSum = (sumLessSteps * rPowered - sumMoreSteps) / (rPowered - 1);

		return resultSum;
	}


	template<class IntegrationMethod, class Function>
	static double IntegrateFunc(const double iX0, const double iX1, const std::size_t iNumSteps, const std::size_t iNumStepsR,  Function iFunc) {

		assert(iNumSteps < iNumStepsR);
		const auto xValues = Utils::GenerateLinspace(iX0, iX1, iNumSteps);
		const auto xValuesR = Utils::GenerateLinspace(iX0, iX1, iNumStepsR);

		return IntegrateFunc<IntegrationMethod>(xValues, xValuesR, iFunc);
	}

	template<class IntegrationMethod, class Function>
	static double IntegrateFunc(const double iX0, const double iX1, const std::size_t iNumSteps,  Function iFunc) {
		auto xValues = Utils::GenerateLinspace(iX0, iX1, iNumSteps);
		return IntegrateFunc<IntegrationMethod>(xValues, iFunc);
	}
	
};