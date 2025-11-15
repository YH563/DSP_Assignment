#ifndef FOURIER_H
#define FOURIER_H

#include "Signal.h"
#include <Eigen/Dense>
#include <complex>

namespace Fourier {
	// 离散傅里叶变换
	Signal::FrequencySiganl DFT(Signal::RealSignal signal);

	// 快速傅里叶变换
	Signal::FrequencySiganl FFT(Signal::RealSignal signal);
}

#endif 