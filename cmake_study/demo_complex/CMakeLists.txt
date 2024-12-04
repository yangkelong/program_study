# .cmake 学习文档

# 设置CMake的最低版本要求：
cmake_minimum_required (VERSION 2.6)
# 设置C++标准：
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置一些编译选项
set(opts
    -Wall           # 打开所有警告
    -Wextra         # 打开额外的警告
    -O2             # 优化级别
    -g              # 包含调试信息
)

# 设置 C 编译器的选项
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${opts}" CACHE STRING "Flags used by the C compiler" FORCE)
# 设置 C++ 编译器的选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${opts}" CACHE STRING "Flags used by the C++ compiler" FORCE)

# 在该命令执行完后, 一些预定义变量会被定义 eg: PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR (build dir)
# 项目名称：
project (HelloWorld)
# 设置默认构建类型
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Release" CACHE STRING
      "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

# 将项目目录下的cmake文件夹加入到CMAKE_MODULE_PATH中，让find_pakcage能够找到我们自定义的函数库
# set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
add_executable(addtest addtest.cc)
find_package(ADD)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~findADD.cmake~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 在指定目录下寻找头文件和动态库文件的位置，可以指定多个目标路径
# note: NAMES PATHS 均可以省略
# 在指定目录中搜索 libadd.h 的目录路径并赋值给变量 ADD_INCLUDE_DIR
find_path(ADD_INCLUDE_DIR NAMES libadd.h PATHS /usr/include/ /usr/local/include ${CMAKE_SOURCE_DIR}/ModuleMode)
# 在指定目录中搜索 libNAMES.so or libNAMES.a or NAMES.lib NAMES.dll
find_library(ADD_LIBRARY NAMES add PATHS /usr/lib/add /usr/local/lib/add ${CMAKE_SOURCE_DIR}/ModuleMode)
if (ADD_INCLUDE_DIR AND ADD_LIBRARY)
    set(ADD_FOUND TRUE)
endif (ADD_INCLUDE_DIR AND ADD_LIBRARY)
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

if(ADD_FOUND)
    # 向指定的目标（例如可执行文件或库）添加包含目录。这些包含目录会被添加到编译器的头文件搜索路径中，以便编译器可以找到目标所需要的头文件
    # 关于选项 PRIVATE PUBLIC INTETFACE 参照文档
    target_include_directories(my_target PRIVATE ${ADD_INCLUDE_DIR})
    # 为 target 链接库
    target_link_libraries(my_target ${ADD_LIBRARY})
else(ADD_FOUND)
    # message(FATAL_ERROR "ADD library not found")
    message("ADD library not found")
endif(ADD_FOUND)

# 从给定的文件中加载并运行CMake代码。变量的读写访问调用者的 scope（动态作用域）
include(Macros)
# Find at least a 5.0 version of FOO.
# Module模式: 在 cmake安装目录下的share/cmake-<version>/Modules目录 或 CMAKE_MODULE_PATH目录 查找 Find<LibraryName>.cmake文件
# Config模式: 通过<LibraryName>Config.cmake or <lower-case-package-name>-config.cmake 这两个文件来引入我们需要的库
# find_package(FOO 5.0 REQUIRED) 会执行 CMAKE_MODULE_PATH 路径下的 findFOO.cmake 脚本，find_package函数将参数FOO 5.0 REQUIRED 赋值给
# CMAKE_FIND_PACKAGE_NAME、 FOO_FIND_VERSION 等变量，这些变量在 findFOO.cmake 脚本中可使用
# 在 findFOO.cmake 中 会有FOO_VERSION、FOO_FOUND 变量指示找到的软件版本和是否找到（这些变量在find_package命令结束后仍然可用）, 
# 以及与软件相关的一些变量（eg：include_Path lib_Path）<LibaryName>_INCLUDE_DIR or <LibaryName>_INCLUDES <LibaryName>_LIBRARY or <LibaryName>_LIBRARIES
find_package(FOO 5.0 REQUIRED)
if(FOO_FOUND)
	message (">>> package foo ${FOO_VERSION} found!")
endif()
# Put all the runtime stuff in the same directory.  By default, CMake puts each targets'
# output into their own directory.  We want all the targets to be put in the same
# directory, and we can do this by setting these variables.
# 默认情况下 CMake放每个target（子项目？）在自己的目录下, 下面设置可以放在一起
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
message (">>> CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
set(foo_dir ${PROJECT_SOURCE_DIR}/myLib/)
message (">>> foo_dir = ${foo_dir}")
# 在 CMake 中，add_subdirectory() 命令用于指定一个子目录，该目录包含一个或多个项目的 CMake 构建文件（CMakeLists.txt）。
# 这个命令告诉 CMake 在配置时包含该子目录中的项目。执行此命令时会执行 子目录下的 CMakeLists.txt
# 1. source_dir：必需参数，指定包含 CMakeLists.txt 文件的子目录路径。这个路径可以是相对于调用 add_subdirectory() 的 CMakeLists.txt 文件的相对路径。
# 2. binary_dir：可选参数，指定构建目标（如执行文件和库文件）的构建输出目录。如果省略此参数，输出将放置在与源代码目录对应的构建目录中。
# 3. EXCLUDE_FROM_ALL：可选关键字，如果包含此关键字，子目录中的目标将不会被包含在默认的 all 目标中。这意味着在调用 make 时，这些目标不会被构建，除非显式指定目标名称。
# add_subdirectory(source_dir [binary_dir] [EXCLUDE_FROM_ALL] [SYSTEM])
add_subdirectory(${foo_dir} EXCLUDE_FROM_ALL)
add_subdirectory("./projectSub1")

# 向项目添加额外的头文件搜索路径, 例如本项目的所有头文件, 或者用到外部库时, 添加外部库的头文件目录
include_directories(${CMAKE_BINARY_DIR}/include)
include_directories($ENV{CGNS_ROOT}/include)


add_executable (HelloWorld HelloWorld.cpp)

target_link_libraries(HelloWorld mylib)
  
#set(SAMPLES_DIR "my_dir")
#~~~将一个模板文件（通常包含变量占位符）复制到另一个文件，并将其中的占位符替换为实际的变量值  #
configure_file(sampleConfig.h.in sampleConfig.h @ONLY)


set (ENV{CMAKE_PREFIX_PATH} "/test/sub")
set (VAR_A "/test/sub")
set (VAR_B ${VAR_A} "/test/sub")
set (VAR_C ${VAR_D} "/test/sub")
message (">>> value = ${VAR_A}")    # >>> value = /test/sub
message (">>> value = ${VAR_B}")    # list   >>> value = /test/sub;/test/sub
message (">>> value = ${VAR_C}")    # 第一个参数没有找到   >>> value = /test/sub

# 选项
option(FEATURE_X "Enable feature X" ON)
set(MY_LIBRARY_PATH "/usr/local/lib" CACHE PATH "Path to my library")
# 高级选项
# 将特定的缓存变量标记为高级
mark_as_advanced(MY_HIDDEN_VARIABLE)
# 使用 FORCE 关键字确保变量始终被标记为高级
mark_as_advanced(FORCE MY_INTERNAL_VARIABLE)
# 使用 CLEAR 关键字将变量从高级状态恢复
mark_as_advanced(CLEAR MY_VARIABLE)

message ("done!")

# 用于设置目标（可以是可执行文件或库）的属性。这些属性可以控制目标的构建过程、输出名称、版本信息等
# eg: 定义预处理器宏
set_target_properties( ${target_name} PROPERTIES
    COMPILE_DEFINITIONS
    "OPTIX_SAMPLE_NAME_DEFINE=${target_name};OPTIX_SAMPLE_DIR_DEFINE=${target_name}" )









