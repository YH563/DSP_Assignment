# Visualization模块 - 同时提供C++接口和Python绑定

# 首先创建静态库（用于C++内部链接）
add_library(Visualization STATIC
    src/VisualizationCore.cpp  # 纯C++可视化核心逻辑
    # 其他C++源文件...
    "include/VisualizationCore.h")

# 设置静态库的包含目录
target_include_directories(Visualization PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/eigen
)

# 链接必要的库
target_link_libraries(Visualization PUBLIC
    eigen
    Signal
    SignalTransform
)

# 在Windows上需要设置编译选项
if(WIN32)
    target_compile_definitions(Visualization PRIVATE
        _CRT_SECURE_NO_WARNINGS
    )
endif()

# 查找pybind11
include(FetchContent)
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG        v3.0.1
)
FetchContent_MakeAvailable(pybind11)

# 包含头文件目录
include_directories(include ${EIGEN3_INCLUDE_DIRS})

# 复制Python文件到构建目录
file(COPY scripts/plot.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/python)
