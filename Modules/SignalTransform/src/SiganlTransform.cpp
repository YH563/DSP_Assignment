#include "SiganlTransform.h"

namespace SiganlTransform {
	using namespace Signal;

	// 辅助函数：循环卷积矩阵
	MatrixXd CycleConvMatrix(const RealSignal& x) {

	}

	// 线性卷积
	RealSignal LinearConv(const RealSignal& x, const RealSignal& y) {

	}

	// 循环卷积
	RealSignal CycleConv(const RealSignal& x, const RealSignal& y, int* length) {
		x.Check2Compute(y);
		int n = (length == nullptr) ? x.Size() : *length;
        RealSignal result(n);
		MatrixXd M = CycleConvMatrix(y);
        result = M * x;
		return result;
	}

	// 离散傅里叶变换
	FrequencySignal DFT(const RealSignal& signal) {

	}
}