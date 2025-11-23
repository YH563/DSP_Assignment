#include <Eigen/Dense>
#include "../../Signal/include/Signal.h"
#include <memory>

namespace VisualizationCore {
	using namespace Signal;
	namespace pybind11 {
		class scoped_interpreter;
		class module_;
		class object;
	}

	// 传递信号数据
	struct SignalData
	{
		VectorXd x;
		VectorXd y;
		std::string label;
		std::string subTitle;

		SignalData() = default;
		SignalData(const VectorXd& x, const VectorXd& y, const std::string& label, const std::string& subTitle) :
            		x(x), y(y), label(label), subTitle(subTitle) {}
	};

	// 绘图管理
	class PlotManager {
	public:
        PlotManager();
		~PlotManager();
	};
}