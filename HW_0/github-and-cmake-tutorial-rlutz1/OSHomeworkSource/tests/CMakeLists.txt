include_directories(${hw_DIR})
include_directories(${src_DIR})

add_executable(unit_tests unit_tests.cpp)
target_link_libraries(unit_tests homework)
add_test(UnitTests ./unit_tests)
