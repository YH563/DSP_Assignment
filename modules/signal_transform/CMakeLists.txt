add_library(signal_transform STATIC
    src/Fourier.cpp
 "include/Fourier.h")

target_include_directories(signal_transform PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(signal_transform PUBLIC eigen)
target_link_libraries(signal_transform PUBLIC Signal)