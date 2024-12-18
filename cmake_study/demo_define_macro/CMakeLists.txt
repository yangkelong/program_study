cmake_policy(SET CMP0048 NEW)
project(demo_test_macro VERSION 1.0.1)
# 定义宏 PPT    PI=3.14159f
# 等价于  #define PPT  		#define PI=3.14159f
add_definitions(-DPPT -DPI=3.14159f)

add_executable(main main.cpp)
# 定义宏 HAVE_PI	E=2.71828f
target_compile_definitions(main PRIVATE HAVE_PI E=2.71828f)

