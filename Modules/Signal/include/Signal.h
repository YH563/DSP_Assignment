#pragma once

#include <Eigen/Dense>
#include <complex>
#include <functional>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#define PI 3.1415926535897932
#define TWO_PI 2 * PI

namespace Signal {
	using VectorXd = Eigen::VectorXd;
	using VectorXc = Eigen::VectorXcd;
	using MatrixXd = Eigen::MatrixXd;

	// 实信号
	class RealSignal {
	public:
		
		using Callback = std::function<VectorXd(const VectorXd&)>;

		// 构造函数
		RealSignal() = default;
		explicit RealSignal(int size): data_(size), coordinate_(size) {}
		RealSignal(RealSignal& other) : data_(other.data_), coordinate_(other.coordinate_), sampleRate(other.sampleRate)
		{ ifCoordinate_ = true; }

		// 基本信号生成
		void GenerateSignal(Callback func, double begin, double end, size_t length);
		void GenerateSignal(Callback func, double sampleRate, int pointsNumber, double begin = 0.0);
		void GenerateSignal(Callback func, VectorXd& coordinate);
		void GenerateSignal(Callback func);

		// 单独设置信号和坐标
		void SetData(const VectorXd& data) { data_ = data; }
		void SetCoordinate(const VectorXd& coordiante) { 
			coordinate_ = coordiante; 
			ifCoordinate_ = true; 
			sampleRate = (double)1 / (coordiante[1] - coordiante[0]); }
		void GenerateCoordinate(double begin, double end, int pointsNumber);

		// 重载运算符
		RealSignal operator+(const RealSignal& other) const;
		RealSignal operator-(const RealSignal& other) const;
		RealSignal operator*(const RealSignal& other) const;
		RealSignal operator*(const MatrixXd& matrix) const;
		friend RealSignal operator*(const MatrixXd& matrix, const RealSignal& signal);
		RealSignal operator/(const RealSignal& other) const;

		bool operator==(const RealSignal& other) const;
		bool operator!=(const RealSignal& other) const;

		RealSignal& operator+=(const RealSignal& other) ;
		RealSignal& operator-=(const RealSignal& other) ;
		RealSignal& operator*=(const RealSignal& other) ;
		RealSignal& operator/=(const RealSignal& other) ;

		// 获取信号基本信息
		VectorXd& GetData() { return data_; }
		VectorXd& GetCoordinate() { return coordinate_; }
		const VectorXd& GetData() const { return data_; }
		const VectorXd& GetCoordinate() const { return coordinate_; }
		int Size() const { return data_.size(); }
		double Max() const { return data_.maxCoeff(); }
		double Min() const { return data_.minCoeff(); }
		double Mean() const { return data_.mean(); }

		// 输出信号
		void Print() const;
		void Output2CSV(std::string fileName);

		// 检查是否可以计算
		bool Check2Compute(const RealSignal& other) const;

	private:
		VectorXd data_;  // 信号
		VectorXd coordinate_;  // 坐标
		bool ifCoordinate_ = false;  // 是否有坐标
		double sampleRate = 1.0;  // 采样率

	};

	// 复频域信号
	class FrequencySignal {
	public:

		// 构造函数
		FrequencySignal() = default;
		explicit FrequencySignal(int size): data_(size), coordinate_(size) {}
		explicit FrequencySignal(FrequencySignal& other): data_(other.data_), coordinate_(other.coordinate_) {}

		// 设置信号与坐标
		void SetData(const VectorXc& data) { data_ = data; }
		void SetCoordinate(const VectorXd& coord) { coordinate_ = coord; }
		void GenerateCoordinate(double begin, double end, int pointsNumber);
		void GenerateCoordinate(double sampleRate, int pointsNumber);
		void GenerateCoordinate(int pointsNumber);
		void ShiftCoordinate();
		void iShiftCoordinate();

		// 转换为实信号
		RealSignal MagnitudeSignal() const;
        RealSignal PhaseSignal() const;

		// 获取基本信息
		const VectorXc& GetData() const { return data_; }
		const VectorXd& GetCoordinate() const { return coordinate_; }
		VectorXc& GetData() { return data_; }
		VectorXd& GetCoordinate() { return coordinate_; }
		VectorXd GetMagnitude() const { return data_.array().abs(); }
		VectorXd GetPhase() const { return data_.array().arg(); }
		VectorXd GetReal() const { return data_.real(); }
		VectorXd GetImag() const { return data_.imag(); }
        int Size() { return data_.size(); }

		// 打印信息
        void Print() const;
	private:
		VectorXc data_;
		VectorXd coordinate_;
		bool ifShifted_ = false;  // 是否已经平移
	};
}