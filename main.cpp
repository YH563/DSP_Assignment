#include "Signal.h"
#include <Eigen/Dense>
#include <iostream>
#include "Experiment/include/BaseFunction.h"
#include "Experiment/include/utils.h"
#include "Modules/SignalTransform/include/SignalTransform.h"

int main() {
	Signal::RealSignal s1;
	s1.GenerateSignal(BaseFunction::Sin, 20.0, 1 << 4);
	s1.Print();
	Signal::FrequencySignal result = utils::time_it("FFT", SignalTransform::FFT, s1);
	//result.Print();
	Signal::RealSignal inv_result = utils::time_it("IFFT", SignalTransform::IFFT, result);
	inv_result.Print();
    return 0;
}