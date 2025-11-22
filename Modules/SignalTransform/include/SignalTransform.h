#pragma once

#include "Signal.h"
#include <Eigen/Dense>
#include <complex>
#include "../../../Experiment/include/utils.h"
#include "../../../Experiment/include/BaseFunction.h"

namespace SignalTransform {
	using VectorXd = Eigen::VectorXd;
	using MatrixXd = Eigen::MatrixXd;
	using VectorXc = Eigen::VectorXcd;
	using RowVectorXd = Eigen::RowVectorXd;
	using MatrixXc = Eigen::MatrixXcd;

	// 线性卷积
	Signal::RealSignal LinearConv(const Signal::RealSignal& x, const Signal::RealSignal& y);

	// 循环卷积
	Signal::RealSignal CycleConv(const Signal::RealSignal& x, const Signal::RealSignal& y, int* length = nullptr);

	// 离散傅里叶变换
	Signal::FrequencySignal DFT(const Signal::RealSignal& signal);

	// 快速傅里叶变换
	Signal::FrequencySignal FFT(const Signal::RealSignal& signal);

	// 逆傅里叶变换
	Signal::RealSignal IFFT(const Signal::FrequencySignal& signal);
}
