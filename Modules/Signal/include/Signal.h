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
#define IMAG std::complex<double>(0, 1)

namespace Signal {
	using VectorXd = Eigen::VectorXd;
	using VectorXc = Eigen::VectorXcd;
	using MatrixXd = Eigen::MatrixXd;
	using Complex = std::complex<double>;

	class RealSignal;  // 前向声明
	class FrequencySignal;  // 前向声明

	// 实信号
	class RealSignal {
	public:
		
		using Callback = std::function<VectorXd(const VectorXd&)>;

		// 构造函数
		RealSignal() = default;
		explicit RealSignal(int size) : data_(size), coordinate_(size) { data_.setZero(); GenerateCoordinate(0, size-1, size); }
		RealSignal(const RealSignal& other) : data_(other.data_), coordinate_(other.coordinate_), sampleRate(other.sampleRate)
		{ ifCoordinate_ = true; }

		// 基本信号生成
		void GenerateSignal(Callback func, double begin, double end, size_t length);
		void GenerateSignal(Callback func, double sampleRate, size_t length);
		void GenerateSignal(Callback func, VectorXd& coordinate);
		void GenerateSignal(Callback func);

		// 单独设置信号和坐标
		void SetData(const VectorXd& data) { data_ = data; }
		void SetCoordinate(const VectorXd& coordiante) { 
			coordinate_ = coordiante; 
			ifCoordinate_ = true; 
			sampleRate = (double)1 / (coordiante[1] - coordiante[0]); }
		void GenerateCoordinate(double begin, double end, int pointsNumber);
		void GenerateCoordinate(int pointsNumber);

		// 重载运算符
		RealSignal operator+(const RealSignal& other) const;
		RealSignal operator-(const RealSignal& other) const;
		RealSignal operator*(const RealSignal& other) const;
		friend RealSignal operator*(const MatrixXd& matrix, const RealSignal& signal);  // 左乘矩阵
		RealSignal operator/(const RealSignal& other) const;

		RealSignal operator+(double scalar) const;
		RealSignal operator-(double scalar) const;
		RealSignal operator*(double scalar) const;
		RealSignal operator/(double scalar) const;

		bool operator==(const RealSignal& other) const;
		bool operator!=(const RealSignal& other) const;

		RealSignal& operator+=(const RealSignal& other) ;
		RealSignal& operator-=(const RealSignal& other) ;
		RealSignal& operator*=(const RealSignal& other) ;
		RealSignal& operator/=(const RealSignal& other) ;

		double& operator[](int index) { return data_[index]; }
		const double& operator[](int index) const { return data_[index]; }

		// 获取信号基本信息
		VectorXd& GetData() { return data_; }
		VectorXd& GetCoordinate() { return coordinate_; }
		const VectorXd& GetData() const { return data_; }
		const VectorXd& GetCoordinate() const { return coordinate_; }
		double GetSampleRate() const { return sampleRate; }
		int size() const { return data_.size(); }
		double max() const { return data_.maxCoeff(); }
		double min() const { return data_.minCoeff(); }
		double mean() const { return data_.mean(); }

		// 输出信号
		void Print() const;
		void Output2CSV(std::string fileName);

		// 检查是否可以计算
		bool Check2Compute(const RealSignal& other) const;

		// 补0序列
		RealSignal& ResizeZeroPadding(int newSize);

		// 转换为复频域信号
        FrequencySignal Real2Complex() const;

	private:
		VectorXd data_;  // 信号
		VectorXd coordinate_;  // 坐标
		bool ifCoordinate_ = false;  // 是否有坐标
		double sampleRate = 1.0;  // 采样率

	};

	// 复频域信号
	class FrequencySignal {
	public:
		enum PrintType{Magnitude, Phase, Both};

		// 构造函数
		FrequencySignal() = default;
		explicit FrequencySignal(int size) : data_(size), coordinate_(size) { coordinate_.Zero(size); }
		FrequencySignal(const FrequencySignal& other) : data_(other.data_), coordinate_(other.coordinate_) {}

		// 设置信号与坐标
		void SetData(const VectorXc& data) { data_ = data; }
		void SetCoordinate(const VectorXd& coord) { coordinate_ = coord; }
		void GenerateCoordinate(double begin, double end, int pointsNumber);
		void GenerateCoordinate(double sampleRate, int pointsNumber);
		void GenerateCoordinate(int pointsNumber);

		// 转换为实信号
		RealSignal MagnitudeSignal() const;
        RealSignal PhaseSignal() const;

		// 重载运算符
		Complex& operator[](int index) { return data_[index]; }
		const Complex& operator[](int index) const { return data_[index]; }

		// 获取基本信息
		const VectorXc& GetData() const { return data_; }
		const VectorXd& GetCoordinate() const { return coordinate_; }
		VectorXc& GetData() { return data_; }
		VectorXd& GetCoordinate() { return coordinate_; }
		VectorXd GetMagnitude() const { return data_.array().abs(); }
		VectorXd GetPhase() const { return data_.array().arg(); }
		VectorXd GetReal() const { return data_.real(); }
		VectorXd GetImag() const { return data_.imag(); }
        int size() const { return data_.size(); }

		// 打印信息
        void Print(PrintType type = Both) const;
	private:
		VectorXc data_;
		VectorXd coordinate_;
	};
}