#include "utils.h"

namespace utils {
	using namespace Signal;

	// ¸¨Öúº¯Êı
	int BitReverseIndex(int index, int bitWidth) {
		int reversedIndex = 0;
		for (int i = 0; i < bitWidth; i++) {
			reversedIndex = (reversedIndex << 1) | (index & 1);
			i >>= 1;
		}
		return reversedIndex;
	}

	// Î»ÄæĞòËã·¨
	FrequencySignal& BitReverse(FrequencySignal& signal){
		int n = signal.Size();
		int bitWidth = 0;
		while ((1 << bitWidth) < n) bitWidth++;

		for (int i = 0; i < n; i++) {
			int j = BitReverseIndex(i, bitWidth);
			if (j > i) std::swap(signal.GetData()[i], signal.GetData()[j]);
		}

		return signal;
	}
}