#include "Signal.h"
#include <Eigen/Dense>
#include <iostream>
#include "Experiment/include/BaseFunction.h"
#include "Experiment/include/utils.h"
#include "Modules/SignalTransform/include/SignalTransform.h"

int main() {
	Signal::RealSignal s1;
	Signal::RealSignal s2;
	s1.GenerateSignal(BaseFunction::Sin, 0, 1, 10);
	s1.Print();
	s2.GenerateSignal(BaseFunction::Cos, 0, 1, 10);
	s2.Print();
	Signal::RealSignal cycleConv = SignalTransform::CycleConv(s1, s2, nullptr);
	cycleConv.Print();
}