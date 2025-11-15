#include "Signal.h"
#include <Eigen/Dense>
#include <iostream>
#include "Experiment/include/BaseFunction.h"
#include "Experiment/include/utils.h"

int main() {
	Signal::RealSignal s1;
	s1.GenerateCoordinate(0, 1, 20);
	s1.GenerateSignal(BaseFunction::Sin);
	Eigen::VectorXd x = Eigen::VectorXd::LinSpaced(100, 0, 1);
	utils::time_it("Sin(x)", BaseFunction::Sin, x);
	s1.Print();
	return 0;
}