# CMakeList.txt: 顶层 CMake 项目文件
cmake_minimum_required(VERSION 3.15)  # 升级到更新的版本

# 如果支持，请为 MSVC 编译器启用热重载。
if(POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("DSP_CPP" LANGUAGES CXX)  # 明确指定语言

# 在project()之后设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # 禁用编译器特定扩展

# 设置默认构建类型为Release（在project()之后设置更可靠）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build" FORCE)
endif()

# 设置构建类型选项
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")

# 设置输出目录（使用生成器表达式以支持多配置生成器）
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 设置编译器特定优化标志
include(CheckCXXCompilerFlag)

# 全局编译定义
add_compile_definitions(_USE_MATH_DEFINES)  # 启用数学常数

# 编译器特定优化
if(MSVC)
    # MSVC优化标志
    add_compile_options(
        "$<$<CONFIG:Release>:/O2>"           # 最大优化（速度）
        "$<$<CONFIG:Release>:/Ob2>"          # 激进内联
        "$<$<CONFIG:Release>:/Ot>"           # 偏好快速代码
        "$<$<CONFIG:Release>:/fp:fast>"      # 快速浮点模型
        "$<$<CONFIG:Release>:/arch:AVX2>"    # AVX2指令集
        "$<$<CONFIG:Debug>:/Od>"             # 禁用优化（调试）
        "$<$<CONFIG:Debug>:/RTC1>"           # 运行时检查
        "$<$<CONFIG:Debug>:/Zi>"             # 调试信息
    )
else()
    # GCC/Clang优化标志
    add_compile_options(
        "$<$<CONFIG:Release>:-O3>"           # 最高优化级别
        "$<$<CONFIG:Release>:-march=native>" # 针对本地CPU优化
        "$<$<CONFIG:Release>:-ffast-math>"   # 快速数学（对FFT很重要！）
        "$<$<CONFIG:Release>:-funroll-loops>"# 循环展开
        "$<$<CONFIG:Release>:-ftree-vectorize>" # 自动向量化
        "$<$<CONFIG:Debug>:-O0>"             # 无优化
        "$<$<CONFIG:Debug>:-g>"              # 调试信息
    )
    
    # 检查并添加可用标志
    check_cxx_compiler_flag(-ffinite-math-only HAVE_FFINITE_MATH)
    if(HAVE_FFINITE_MATH)
        add_compile_options("$<$<CONFIG:Release>:-ffinite-math-only>")
    endif()
endif()

# 设置Python路径
set(Python3_EXECUTABLE "D:/miniconda/envs/escnn_env/python.exe")

# 查找Python
find_package(Python3 REQUIRED COMPONENTS Interpreter Development.Module)

# 验证找到的Python
if(Python3_FOUND)
    message(STATUS "Python3 executable: ${Python3_EXECUTABLE}")
    message(STATUS "Python3 version: ${Python3_VERSION}")
    message(STATUS "Python3 include dirs: ${Python3_INCLUDE_DIRS}")
    message(STATUS "Python3 library: ${Python3_LIBRARIES}")
else()
    message(FATAL_ERROR "Python3 not found in the specified conda environment")
endif()

# 查找pybind11（使用更现代的获取方式）
find_package(pybind11 CONFIG QUIET)
if(NOT pybind11_FOUND)
    message(STATUS "pybind11 not found, fetching from GitHub...")
    include(FetchContent)
    FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11.git
        GIT_TAG        v2.10.4  # 使用更新的稳定版本
    )
    FetchContent_MakeAvailable(pybind11)
endif()

# 创建Eigen接口库
add_library(eigen INTERFACE)
target_include_directories(eigen INTERFACE 
    ${CMAKE_SOURCE_DIR}/third_party/eigen
)

# 为Eigen添加编译定义以提升性能
target_compile_definitions(eigen INTERFACE 
    EIGEN_NO_DEBUG           # 在Release模式禁用Eigen的调试
    EIGEN_MPL2_ONLY          # 只使用MPL2许可的代码
    EIGEN_MAX_ALIGN_BYTES=32 # 设置合适的对齐
)

# 包含子项目（按依赖顺序）
add_subdirectory("Modules/Signal")
add_subdirectory("Modules/SignalTransform") 
add_subdirectory("Modules/Visualization")
add_subdirectory("Experiment")

# 添加可执行文件
add_executable(${PROJECT_NAME} main.cpp)

# 设置目标属性以最大化性能
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# 链接库（按依赖顺序）
target_link_libraries(${PROJECT_NAME}
    PRIVATE 
        Signal
        SignalTransform  
        Visualization
        Experiment
        eigen  # Eigen放在最后
)

# 添加性能测试目标（可选）
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_target(performance-test
        COMMAND ${PROJECT_NAME} --benchmark
        DEPENDS ${PROJECT_NAME}
        COMMENT "Running performance benchmarks"
        VERBATIM
    )
endif()

# 安装目标（可选）
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    CONFIGURATIONS Release
)

# 在配置结束时打印总结
message(STATUS "")
message(STATUS "Configuration Summary:")
message(STATUS "  Project: ${PROJECT_NAME}")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  C++ compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  Optimization level: $<IF:$<CONFIG:Release>,Aggressive,Debug>")
message(STATUS "  Python: ${Python3_VERSION}")
message(STATUS "  Eigen: ${CMAKE_SOURCE_DIR}/third_party/eigen")
message(STATUS "")