#include "Signal.h"

namespace Signal {
	void FrequencySignal::GenerateCoordinate(double begin, double end, int pointsNumber) {
		coordinate_ = VectorXc::LinSpaced(pointsNumber, begin, end);
	}

	void FrequencySignal::GenerateCoordinate(double sampleRate, int pointsNumber) {
		coordinate_ = VectorXc::LinSpaced(pointsNumber, 0, sampleRate);
	}

	void FrequencySignal::GenerateCoordinate(int pointsNumber) {
		coordinate_ = VectorXc::LinSpaced(pointsNumber, 0, (double)(TWO_PI / pointsNumber));
	}

	void FrequencySignal::ShiftCoordinate() {
		if (ifShifted_) {
			std::string warningMsg = "Coordinate has already been shifted.";
			std::cerr << warningMsg << std::endl;
			return;
		}

		int N = coordinate_.size();
		int mid = N / 2;
		for (int i = 0; i < mid; i++) {

		}
	}

	void FrequencySignal::iShiftCoordinate() {

	}

	RealSignal FrequencySignal::MagnitudeSignal() const {
		RealSignal magnitudeSignal;
		magnitudeSignal.SetData(this->GetMagnitude());
		magnitudeSignal.SetCoordinate(this->GetCoordinate());
		return magnitudeSignal;
	}

	RealSignal FrequencySignal::PhaseSignal() const {
		RealSignal phaseSignal;
		phaseSignal.SetData(this->GetPhase());
		phaseSignal.SetCoordinate(this->GetCoordinate());
		return phaseSignal;
	}
}