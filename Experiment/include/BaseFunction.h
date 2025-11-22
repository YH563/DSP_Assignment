#pragma once

#include <Eigen/Dense>

#define PI 3.1415926535897932
#define TWO_PI 2 * PI

namespace BaseFunction {
	using VectorXd = Eigen::VectorXd;
    using MatrixXd = Eigen::MatrixXd;
	using VectorXc = Eigen::VectorXcd;
	using Complex = std::complex<double>;

	VectorXd Constant(const VectorXd& x, double c);
	VectorXd Sin(const VectorXd& x);
	VectorXd Cos(const VectorXd& x);
	VectorXd Exp(const VectorXd& x);
	VectorXd Random(const VectorXd& x);

	VectorXc ComplexExp(const VectorXd& x);
	VectorXc ComplexConstant(const VectorXd& x, Complex c);
}
