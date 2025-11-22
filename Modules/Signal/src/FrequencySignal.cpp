#include "Signal.h"

namespace Signal {
	void FrequencySignal::GenerateCoordinate(double begin, double end, int pointsNumber) {
		coordinate_ = VectorXd::LinSpaced(pointsNumber, begin, end);
	}

	void FrequencySignal::GenerateCoordinate(double sampleRate, int pointsNumber) {
		coordinate_.resize(pointsNumber);
		double step = sampleRate / (double)pointsNumber;
		for (int i=0;i<pointsNumber;i++) {
			coordinate_[i] = - sampleRate / 2.0 + i * step;
		}
	}

	void FrequencySignal::GenerateCoordinate(int pointsNumber) {
		coordinate_.resize(pointsNumber);
		double step = TWO_PI / (double)pointsNumber;
		for (int i = 0; i < pointsNumber; i++) {
			coordinate_[i] = - PI + i * step;
		}
	}

	RealSignal FrequencySignal::MagnitudeSignal() const {
		RealSignal magnitudeSignal;
		magnitudeSignal.SetData(this->GetMagnitude());
		magnitudeSignal.GenerateCoordinate(0, this->size()-1, this->size());
		return magnitudeSignal;
	}

	RealSignal FrequencySignal::PhaseSignal() const {
		RealSignal phaseSignal;
		phaseSignal.SetData(this->GetPhase());
		phaseSignal.GenerateCoordinate(0, this->size() - 1, this->size());
		return phaseSignal;
	}

	void FrequencySignal::Print(PrintType type) const {
		std::cout << "Coordinate:\n" << coordinate_.transpose() << std::endl;
		switch (type)
		{
		case Signal::FrequencySignal::Magnitude:
			std::cout << "Magnitude:\n" << data_.array().abs().transpose() << std::endl;
			break;
		case Signal::FrequencySignal::Phase:
			std::cout << "Phase:\n" << data_.array().arg().transpose() << std::endl;
			break;
		case Signal::FrequencySignal::Both:
			std::cout << "Complex Data:\n" << data_.transpose() << std::endl;
			break;
		default:
			break;
		}
	}
}