#include "utils.h"

namespace utils {
	using namespace Signal;

	// 辅助函数
	int BitReverseIndex(int index, int bitWidth) {
		int reversedIndex = 0;
		for (int i = 0; i < bitWidth; i++) {
			reversedIndex = (reversedIndex << 1) | (index & 1);
			index >>= 1;
		}
		return reversedIndex;
	}

	// 位逆序算法
	FrequencySignal& BitReverse(FrequencySignal& signal){
		int n = signal.size();
		if (n <= 1) return signal;
		int bitWidth = 0;
		while ((1 << bitWidth) < n) bitWidth++;

		for (int i = 0; i < n; i++) {
			int j = BitReverseIndex(i, bitWidth);
			if (j > i) std::swap(signal.GetData()[i], signal.GetData()[j]);
		}
		return signal;
	}

	// 移频
	/*FrequencySignal& ShiftFrequency(FrequencySignal& signal) {
		if (signal.GetIfShifted()) {
			std::string warningMsg = "Coordinate has already been shifted.";
			std::cerr << warningMsg << std::endl;
			return;
		}

		int N = signal.size();
		int mid = N / 2;
		for (int i = 0; i < mid; i++) {

		}
	}*/

	// 移频回原位
	/*FrequencySignal& IShiftFrequency(FrequencySignal& signal) {

	}*/
}