add_library(Experiment STATIC
    src/BaseFunction.cpp
 include/BaseFunction.h  "include/utils.h")

target_include_directories(Experiment PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Experiment PUBLIC eigen)