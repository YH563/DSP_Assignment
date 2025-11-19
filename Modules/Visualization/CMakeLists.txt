add_library(Visualization STATIC
    src/python_wrapper.cpp
    include/python_wrapper.h
)

target_include_directories(Visualization PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
