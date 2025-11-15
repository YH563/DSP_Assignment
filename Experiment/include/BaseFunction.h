#ifndef BASEFUNCTION_H
#define BASEFUNCTION_H

#include <Eigen/Dense>

#define PI 3.1415926535897932
#define TWO_PI 2 * PI

namespace BaseFunction {

	using VectorXd = Eigen::VectorXd;
    using MatrixXd = Eigen::MatrixXd;

	VectorXd Constant(VectorXd x, double c) { return VectorXd::Constant(x.size(), c); }
	VectorXd Sin(VectorXd x) { return Eigen::sin(x.array()); }
	VectorXd Cos(VectorXd x) { return Eigen::cos(x.array()); }
	VectorXd Exp(VectorXd x) { return Eigen::exp(x.array()); } 
}

#endif // !