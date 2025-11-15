add_library(Signal STATIC
    src/RealSignal.cpp
    "src/FrequencySignal.cpp"
 include/Signal.h )

target_include_directories(Signal PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Signal PUBLIC eigen)