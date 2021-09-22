#pragma once
#include <numbers>
#include "3rd Task/Integrator.h"

class BesselCalculator {


public:

	template<class IntegrationMethod>
	static double CalculateBessel(const double iX, const std::size_t m, const std::size_t iNumSteps) {
		using namespace std::numbers;
		const auto xValues = Utils::GenerateLinspace(0.0, pi_v<double>, iNumSteps);

		const auto function = [=](const double t) { return std::cos(static_cast<double>(m) * t - iX * std::sin(t)); };				
		const auto besselValue = 1.0 / pi_v<double> * Integrator::IntegrateFunc<IntegrationMethod>(xValues, function);

		return besselValue;
	}

	template<class IntegrationMethod>
	static double CalculateBessel(const double iX, const std::size_t m, const std::size_t iNumSteps, const std::size_t iNumStepsR) {
		using namespace std::numbers;
		const auto xValuesLessSteps = Utils::GenerateLinspace(0.0, pi_v<double>, iNumSteps);
		const auto xValuesMoreSteps = Utils::GenerateLinspace(0.0, pi_v<double>, iNumStepsR);

		const auto function = [=](const double t) { return std::cos(static_cast<double>(m) * t - iX * std::sin(t)); };
		const auto besselValue = 1.0 / pi_v<double> *Integrator::IntegrateFunc<IntegrationMethod>(xValuesLessSteps, xValuesMoreSteps, function);

		return besselValue;
	}

	template<class IntegrationMethod>
	static double CalculateBesselDerivative(const double iX, 
											const std::size_t m,
											const std::size_t iNumSteps, 
											const double iDelta = 0.0001) {
		return (CalculateBessel<IntegrationMethod>(iX + iDelta, m, iNumSteps) - CalculateBessel<IntegrationMethod>(iX, m, iNumSteps)) / iDelta;

	}

	template<class IntegrationMethod>
	static double CalculateBesselDerivative(const double iX, const std::size_t m, 
											const std::size_t iNumSteps, 
											const std::size_t iNumStepR, 
											const double iDelta = 0.0001) {
		return (CalculateBessel<IntegrationMethod>(iX + iDelta, m, iNumSteps, iNumStepR) - CalculateBessel<IntegrationMethod>(iX, m, iNumSteps, iNumStepR)) / iDelta;

	}
};