#include "SignalTransform.h"

namespace SignalTransform {
	using namespace Signal;

	// 线性卷积
	//RealSignal LinearConv(const RealSignal& x, const RealSignal& y) {

	//}

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
	//FrequencySignal DFT(const RealSignal& signal) {

	//}
}