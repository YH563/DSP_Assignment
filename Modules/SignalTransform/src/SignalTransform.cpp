#include "SignalTransform.h"


namespace SignalTransform {
	using namespace Signal;

	// 线性卷积
	RealSignal LinearConv(const RealSignal& x, const RealSignal& y) {
		int n1 = x.size();
		int n2 = y.size();
		int n = n1 + n2 - 1;
        RealSignal result(n);
		result.GenerateCoordinate(0, n - 1, n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n2; j++) {
				if (i - j >= 0 && i - j < n1) {
					result[i] += x[i - j] * y[j];
				}
			}
		}
		return result;
	}

	// 循环卷积
	RealSignal CycleConv(const Signal::RealSignal& x, const Signal::RealSignal& y, int* length) {
		x.Check2Compute(y);
		unsigned int n = (length == nullptr) ? x.size() : *length;
        RealSignal result(n);
		result.SetCoordinate(x.GetCoordinate());
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				result[i] += x[j] * y[(i - j + n) % n];
			}
		}
		return result;
	}

	// 离散傅里叶变换
	FrequencySignal DFT(const Signal::RealSignal& signal) {
		FrequencySignal result = signal.Real2Complex();
		int N = result.size();
		MatrixXc DFT_matrix(N, N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				DFT_matrix(i, j) = std::exp(-TWO_PI * IMAG * (double)(i * j) / (double)N);
			}
		}
		result.SetData(DFT_matrix * result.GetData());
		return result;
	}

	// 快速傅里叶变换
	FrequencySignal FFT(const Signal::RealSignal& signal) {
		FrequencySignal result = signal.Real2Complex();
		int N = result.size();
		utils::BitReverse(result);
		for (int size = 2; size <= N; size *= 2)
		{
			Complex w0 = std::exp(- TWO_PI * IMAG / (double)size);
			for (int i = 0; i < N; i += size) {
				Complex w = IMAG;
				int half_size = size / 2;
				for (int j=i;j<i+half_size; j++) {
					Complex u = result[j];
					Complex v = w * result[j + half_size];
					result[j] = result[j] + v;
					result[j + half_size] = u - v;
					w *= w0;
				}
			}
		}
		return result;
	}

	RealSignal IFFT(const Signal::FrequencySignal& signal) {
		FrequencySignal result = signal;
		int N = result.size();
		utils::BitReverse(result);
		for (int size = 2; size <= N; size *= 2)
		{
			Complex w0 = std::exp(TWO_PI * IMAG / (double)size);
			for (int i = 0; i < N; i += size) {
				Complex w = Complex(1, 0);
				int half_size = size / 2;
				for (int j = i; j < i + half_size; j++) {
					Complex u = result[j];
					Complex v = w * result[j + half_size];
					result[j] = result[j] + v;
					result[j + half_size] = u - v;
					w *= w0;
				}
			}
		}
		return result.MagnitudeSignal() * (1 / (double)N);
	}

}