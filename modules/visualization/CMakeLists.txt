add_library(visualization STATIC
    src/plot.cpp
)

target_include_directories(visualization PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(visualization PUBLIC eigen)