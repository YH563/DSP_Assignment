add_library(SignalTransform STATIC
    "src/SignalTransform.cpp"
 "include/SignalTransform.h")

target_include_directories(SignalTransform PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(SignalTransform PUBLIC eigen)
target_link_libraries(SignalTransform PUBLIC Signal)
target_link_libraries(SignalTransform PUBLIC Experiment)