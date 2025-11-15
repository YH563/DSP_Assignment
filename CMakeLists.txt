# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("DSP_CPP")

# 创建Eigen接口库
add_library(eigen INTERFACE)
target_include_directories(eigen INTERFACE 
    ${CMAKE_SOURCE_DIR}/third_party/eigen
)

# 包含子项目。
add_subdirectory ("modules/Signal")
add_subdirectory ("modules/signal_transform")
add_subdirectory ("modules/visualization")
add_subdirectory ("Experiment")

# 添加可执行文件并链接库
add_executable(${PROJECT_NAME} main.cpp )
target_link_libraries(${PROJECT_NAME}
    PRIVATE Signal
    PRIVATE Experiment
)

