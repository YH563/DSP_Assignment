#ifndef SIGNAL_H
#define SIGNAL_H

#include <Eigen/Dense>
#include <complex>
#include <functional>
#include <cmath>
#include <vector>
#include <string>

namespace Signal {
	// 实信号
	class RealSignal {
	public:
		using VectorXd = Eigen::VectorXd;
		using Callback = std::function<VectorXd(const VectorXd&)>;

		// 构造函数
		RealSignal() = default;
		explicit RealSignal(int size): data_(size), coordinate_(size) {}
		RealSignal(RealSignal& other) : data_(other.data_), coordinate_(other.coordinate_) { ifCoordinate_ = true; }

		// 基本信号生成
		void GenerateSignal(Callback func, double begin, double end, size_t length);
		void GenerateSignal(Callback func, double sampleRate, int pointsNumber, double begin = 0.0);
		void GenerateSignal(Callback func, VectorXd& coordinate);
		void GenerateSignal(Callback func);

		// 单独设置信号和坐标
		void SetData(const VectorXd& data) { data_ = data; }
		void SetCoordinate(const VectorXd& coordiante) { coordinate_ = coordiante; ifCoordinate_ = true; }
		void GenerateCoordinate(double begin, double end, int pointsNumber);

		// 重载运算符
		RealSignal operator+(const RealSignal& other) const;
		RealSignal operator-(const RealSignal& other) const;
		RealSignal operator*(const RealSignal& other) const;
		RealSignal operator/(const RealSignal& other) const;

		RealSignal& operator+=(const RealSignal& other) ;
		RealSignal& operator-=(const RealSignal& other) ;
		RealSignal& operator*=(const RealSignal& other) ;
		RealSignal& operator/=(const RealSignal& other) ;

		// 获取信号基本信息
		VectorXd& GetData() { return data_; }
		VectorXd& GetCoordinate() { return coordinate_; }
		const VectorXd& GetData() const { return data_; }
		const VectorXd& GetCoordinate() const { return coordinate_; }
		int Size() { return data_.size(); }
		double Max() { return data_.maxCoeff(); }
		double Min() { return data_.minCoeff(); }
		double Mean() { return data_.mean(); }

		// 输出信号
		void Print() const;
		void Output2CSV(std::string fileName);

	private:
		VectorXd data_;  // 信号
		VectorXd coordinate_;  // 坐标
		bool ifCoordinate_ = false;  // 是否有坐标
		double sampleRate;  // 采样率
	};

	// 复频域信号
	class FrequencySiganl {
	public:
		using VectorCd = Eigen::VectorXcd;
		using VectorXd = Eigen::VectorXd;

		// 构造函数
		FrequencySiganl() = default;
		explicit FrequencySiganl(int size): data_(size), coordinate_(size) {}
		explicit FrequencySiganl(FrequencySiganl& other): data_(other.data_), coordinate_(other.coordinate_) {}

		// 设置信号与坐标
		void SetData(const VectorCd& data) { data_ = data; }
		void SetCoordinate(const VectorXd& coord) { coordinate_ = coord; }
		void SetFrequencyAxis(double startFreq, double endFreq, int numPoints);
		void SetFrequencyAxis(const VectorXd& freqs);

		// 获取基本信息
		const VectorCd& GetData() const { return data_; }
		const VectorXd& GetCoordinate() const { return coordinate_; }
		VectorCd& GetData() { return data_; }
		VectorXd& GetCoordinate() { return coordinate_; }
		VectorXd GetMagnitude() const { return data_.array().abs(); }
		VectorXd GetPhase() const { return data_.array().arg(); }
		VectorXd GetReal() const { return data_.real(); }
		VectorXd GetImag() const { return data_.imag(); }

	private:
		VectorCd data_;
		VectorXd coordinate_;
	};
}
#endif 