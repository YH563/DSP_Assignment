#include "Signal.h"
#include <iostream>
#include <fstream>


namespace Signal {
	void RealSignal::GenerateCoordinate(double begin, double end, int pointsNumber) {
		coordinate_ = VectorXd::LinSpaced(pointsNumber, begin, end);
		ifCoordinate_ = true;
	}

	// 基本函数信号生成
	void RealSignal::GenerateSignal(Callback func, double begin, double end, size_t length) {
		this->GenerateCoordinate(begin, end, int(length));
		this->SetData(func(this->GetCoordinate()));
	}

	void RealSignal::GenerateSignal(Callback func, double sampleRate, int pointsNumber, double begin) {
		this->sampleRate = sampleRate;
		this->GenerateCoordinate(begin, begin + (pointsNumber - 1) * 1.0 / sampleRate, pointsNumber);
		this->SetData(func(this->GetCoordinate()));
	}

	void RealSignal::GenerateSignal(Callback func, VectorXd& coordinate) {
		this->SetCoordinate(coordinate);
		this->SetData(func(coordinate));
	}

	void RealSignal::GenerateSignal(Callback func) {
		if (!func) {
			throw std::invalid_argument("Callback function cannot be null!");
		}
		if (!ifCoordinate_) {
            std::string errorMsg = "The coordinate is not set!";
            throw std::invalid_argument(errorMsg);
		}
        this->SetData(func(this->GetCoordinate()));
	}

	// 重载运算符
	RealSignal RealSignal::operator+(const RealSignal& other) const {
		if (data_.size() != other.data_.size()) {
			std::string errorMsg = "The two signals must have the same length!";
			throw std::invalid_argument(errorMsg);
		}
		if (coordinate_ != other.coordinate_) {
			std::string errorMsg = "Error: The two signals have different coordinates!";
			throw std::invalid_argument(errorMsg);
		}
		RealSignal result(data_.size());
		result.GenerateCoordinate(coordinate_[0], coordinate_[coordinate_.size() - 1], data_.size());
		result.SetData(data_ + other.data_);
		return result;
	}

	RealSignal RealSignal::operator-(const RealSignal& other) const {
		if (data_.size() != other.data_.size()) {
			std::string errorMsg = "The two signals must have the same length!";
			throw std::invalid_argument(errorMsg);
		}
		if (coordinate_ != other.coordinate_) {
			std::string errorMsg = "Error: The two signals have different coordinates!";
			throw std::invalid_argument(errorMsg);
		}
		RealSignal result(data_.size());
		result.GenerateCoordinate(coordinate_[0], coordinate_[coordinate_.size() - 1], data_.size());
		result.SetData(data_ - other.data_);
		return result;
	}

	RealSignal RealSignal::operator*(const RealSignal& other) const {
		if (data_.size() != other.data_.size()) {
			std::string errorMsg = "The two signals must have the same length!";
			throw std::invalid_argument(errorMsg);
		}
		if (coordinate_ != other.coordinate_) {
			std::string errorMsg = "Error: The two signals have different coordinates!";
			throw std::invalid_argument(errorMsg);
		}
		RealSignal result(data_.size());
		result.GenerateCoordinate(coordinate_[0], coordinate_[coordinate_.size() - 1], data_.size());
		result.SetData(data_ * other.data_);
		return result;
	}

	RealSignal RealSignal::operator/(const RealSignal& other) const {
		if (data_.size() != other.data_.size()) {
			std::string errorMsg = "The two signals must have the same length!";
			throw std::invalid_argument(errorMsg);
		}
		if (coordinate_ != other.coordinate_) {
			std::string errorMsg = "Error: The two signals have different coordinates!";
			throw std::invalid_argument(errorMsg);
		}
		RealSignal result(data_.size());
		result.GenerateCoordinate(coordinate_[0], coordinate_[coordinate_.size() - 1], data_.size());
		result.SetData(VectorXd(data_.array() / other.data_.array()));
		return result;
	}

	RealSignal& RealSignal::operator+=(const RealSignal& other) {
		if (data_.size() != other.data_.size()) {
			std::string errorMsg = "The two signals must have the same length!";
			throw std::invalid_argument(errorMsg);
		}
		if (coordinate_ != other.coordinate_) {
			std::string errorMsg = "Error: The two signals have different coordinates!";
			throw std::invalid_argument(errorMsg);
		}
		*this = *this + other;
		return *this;
	}

	RealSignal& RealSignal::operator-=(const RealSignal& other) {
		if (data_.size() != other.data_.size()) {
			std::string errorMsg = "The two signals must have the same length!";
			throw std::invalid_argument(errorMsg);
		}
		if (coordinate_ != other.coordinate_) {
			std::string errorMsg = "Error: The two signals have different coordinates!";
			throw std::invalid_argument(errorMsg);
		}
		*this = *this - other;
		return *this;
	}

	RealSignal& RealSignal::operator*=(const RealSignal& other) {
		if (data_.size() != other.data_.size()) {
			std::string errorMsg = "The two signals must have the same length!";
			throw std::invalid_argument(errorMsg);
		}
		if (coordinate_ != other.coordinate_) {
			std::string errorMsg = "Error: The two signals have different coordinates!";
			throw std::invalid_argument(errorMsg);
		}
		*this = *this * other;
		return *this;
	}

	RealSignal& RealSignal::operator/=(const RealSignal& other) {
		if (data_.size() != other.data_.size()) {
			std::string errorMsg = "The two signals must have the same length!";
			throw std::invalid_argument(errorMsg);
		}
		if (coordinate_ != other.coordinate_) {
			std::string errorMsg = "Error: The two signals have different coordinates!";
			throw std::invalid_argument(errorMsg);
		}
		*this = *this / other;
		return *this;
	}

	// 输出信号
	void RealSignal::Print() const {
		std::cout << "Coordinate:\n" << coordinate_.transpose() << std::endl;
		std::cout << "Data:\n" << data_.transpose() << std::endl;
	}

	void RealSignal::Output2CSV(std::string fileName) {
		Eigen::MatrixXd outputMatrix(this->Size(), 2);
		outputMatrix.col(0) = coordinate_;
		outputMatrix.col(1) = data_;
		Eigen::IOFormat CSVFormat(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", "\n");
		std::ofstream file(fileName);
		if (file.is_open()) {
			file << outputMatrix.format(CSVFormat);
			file.close();
			std::cout << "数据已保存到"<< fileName << std::endl;
		}
	}
}