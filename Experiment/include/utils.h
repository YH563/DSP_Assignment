#include <chrono>

namespace utils {
    // 计算函数执行时间
    template <typename Func, typename... Args>
    auto time_it(const char* func_name, Func&& func, Args&&... args) -> decltype(func(args...)) {
        auto start = std::chrono::high_resolution_clock::now();
        // 执行被绑定的成员函数（或普通函数）
        auto result = std::forward<Func>(func)(std::forward<Args>(args)...);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "函数 " << func_name << " 执行耗时: " << duration.count() << " ms" << std::endl;
        return result;
    }
}
