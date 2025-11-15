#ifndef SIGNAL_H
#define SIGNAL_H

#include<Eigen/Dense>
#include<complex>
#include <functional>
#include <cmath>
#include <vector>

namespace Signal {
	// 实信号
	class RealSignal {
	public:
		using VectorXd = Eigen::VectorXd;

		// 构造函数
		RealSignal() = default;
		explicit RealSignal(int size): data_(size), coordinate_(size) {}
		RealSignal(RealSignal& other) : data_(other.data_), coordinate_(other.coordinate_) {}

		// 基本信号生成
		static RealSignal sin(double amplitude, double frequency, double phase, double sampleRate, double begin, double end);
		static RealSignal cos(double amplitude, double frequency, double phase, double sampleRate, double begin, double end);
		static RealSignal constant(double amplitude, double sampleRate, double begin, double end);

		// 重载运算符
		std::vector<double>& operator[](int index) { return std::vector<double>({ data_[index], coordinate_[index] }); }
		const std::vector<double>& operator[](int index) const { return std::vector<double>({ data_[index], coordinate_[index] }); }

	private:
		VectorXd data_;  // 信号
		VectorXd coordinate_;  // 坐标
	};

	// 复频域信号
	class ComplexSiganl {
	public:
		using VectorCd = Eigen::VectorXcd;
		using VectorXd = Eigen::VectorXd;

		// 构造函数
		ComplexSiganl() = default;
		explicit ComplexSiganl(int size): data_(size), coordinate_(size) {}
		explicit ComplexSiganl(ComplexSiganl& other): data_(other.data_), coordinate_(other.coordinate_) {}

		// 基本信号生成


		// 重载运算符
		std::complex<double>& operator[](int index) { return data_[index]; }
		const std::complex<double>& operator[](int index) const { return data_[index]; }

	private:
		VectorCd data_;
		VectorXd coordinate_;
	};
}
#endif 