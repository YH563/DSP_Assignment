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

# 创建pybind11模块（用于Python绑定）
pybind11_add_module(VisualizationPy MODULE
    src/python_wrapper.cpp  # 注意：使用相同的源文件
)

# 设置pybind11模块的包含目录
target_include_directories(VisualizationPy PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/eigen
)

# 链接pybind11模块所需的库
target_link_libraries(VisualizationPy PRIVATE
    Visualization
    pybind11::module
)

# 设置输出目录和属性
set_target_properties(VisualizationPy PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/python
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/python
    # 在Windows上生成.pyd文件而不是.dll
    SUFFIX ".pyd"
    PREFIX ""
)