#include "BaseFunction.h"

namespace BaseFunction {
	VectorXd Constant(const VectorXd& x, double c){return VectorXd::Constant(x.size(), c);}
	VectorXd Sin(const VectorXd& x) { return Eigen::sin(x.array()); }
	VectorXd Cos(const VectorXd& x) { return Eigen::cos(x.array()); }
	VectorXd Exp(const VectorXd& x) { return Eigen::exp(x.array()); }
	VectorXd Random(const VectorXd& x){ return VectorXd::Random(x.size()); }

	VectorXc ComplexExp(const VectorXd& x) { return (x.array() * Complex(0, 1)).exp(); }
	VectorXc ComplexConstant(const VectorXd& x, Complex c){return VectorXc::Constant(x.size(), c);}
}