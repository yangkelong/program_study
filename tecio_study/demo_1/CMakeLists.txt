cmake_minimum_required(VERSION 3.15...3.31)

project(
  WritePlt
  VERSION 1.0
  LANGUAGES CXX
)

# 设置 TECIO 库的安装目录
# 在 Windows 系统中，路径分隔符应使用正斜杠 / 或双反斜杠 \\，而不是单反斜杠 \
# set(TECIO_DIR "C:/Program Files/Tecplot/Tecplot 360 EX 2019 R1/")
set(TECIO_DIR ${PROJECT_SOURCE_DIR}/tecio/)

# 添加可执行文件
add_executable(my_target multiplepolygons.cpp)

# 查找 TECIO 库
# 注意：这里假设库文件在 TECIO_DIR/lib 目录下，并且库文件名为 tecio.lib（Windows）或 libtecio.a（Linux）
find_library(tecio_LIBRARY NAMES tecio PATHS ${TECIO_DIR}/lib NO_DEFAULT_PATH)

# 为目标添加包含目录
target_include_directories(my_target PRIVATE ${TECIO_DIR}/include)

# 链接 TECIO 库
target_link_libraries(my_target PRIVATE ${tecio_LIBRARY})