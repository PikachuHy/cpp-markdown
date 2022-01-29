find_package(GTest REQUIRED)
enable_testing()
#find_package(GTest CONFIG REQUIRED)
add_executable(test_parser test_parser.cpp)
target_link_libraries(test_parser PRIVATE MarkdownParser gtest::gtest)
# fatal error C1189: #error:  The C++ Standard Library forbids macroizing the keyword "private".
# Enable warning C4005 to find the forbidden define.
target_compile_definitions(test_parser PRIVATE -D_XKEYCHECK_H)
add_test(NAME test_parser COMMAND test_parser)
#include(GoogleTest)
#gtest_discover_tests(test_parser)