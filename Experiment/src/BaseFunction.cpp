#include "BaseFunction.h"

namespace BaseFunction {
	VectorXd Constant(const VectorXd& x, double c){return VectorXd::Constant(x.size(), c);}
	VectorXd Sin(const VectorXd& x) { return Eigen::sin(x.array()); }
	VectorXd Cos(const VectorXd& x) { return Eigen::cos(x.array()); }
	VectorXd Exp(const VectorXd& x) { return Eigen::exp(x.array()); }
}