# ======================================================================== #
# FFFFFFFFFFFF
# FFFFFFFFFFFF
# FFFFFFFFFFFF
# FFFFFFFFFFFF
# ======================================================================== #
# 额外三方库 gdt cgal boost eigen
# D:\backup\source\repos\cgal_demo1\Project5



cmake_minimum_required(VERSION 3.15...3.31)

project(
  CGAL_test
  VERSION 1.0
  LANGUAGES CXX
)


# ------------------------------------------------------------------
# first, include gdt project to do some general configuration stuff
# ------------------------------------------------------------------
set(gdt_dir ${PROJECT_SOURCE_DIR}/external/gdt/)
# ------------------------------------------------------------------
# import gdt submodule
# ------------------------------------------------------------------
include_directories(${gdt_dir})
# EXCLUDE_FROM_ALL 子目录下的子项目不会被 build
add_subdirectory(${gdt_dir} EXCLUDE_FROM_ALL)
# Eigen
include_directories(${PROJECT_SOURCE_DIR}/external/eigen-3.4.0)
# boost("header only library", no need link)
include_directories(${PROJECT_SOURCE_DIR}/external/boost_1_78_0)
# CGAL("header only library", no need link)
# linux 下 cgal 头文件放入 /usr/local/include/CGAL/~  编译器会默认加入该搜索路径
# 或者都使用项目路径下的 ${PROJECT_SOURCE_DIR}/external/cgal/CGAL
set(cgal_dir ${PROJECT_SOURCE_DIR}/external/cgal-5.6.1/)
include_directories(${cgal_dir}/include)

# 添加可执行文件
add_executable(convex_hull_3d convex_hull_3d.cpp )
add_executable(convex_hull_3d_dynamic convex_hull_3d_dynamic.cpp )
add_executable(diff_wall_points_test diff_wall_points_test.cpp )
add_executable(line_triangle_intersect line_triangle_intersect.cpp )

# windows下 cgal 需要一些额外库: gmp
if(WIN32)
    # gmp
    # auxiliary\gmp\lib
    set(gmp_dir ${cgal_dir}/auxiliary/gmp/)
    include_directories(${gmp_dir}/include)
    target_link_libraries(convex_hull_3d PUBLIC 
      ${gmp_dir}/lib/libgmp-10.lib
      ${gmp_dir}/lib/libmpfr-4.lib
      )

    target_link_libraries(convex_hull_3d_dynamic PUBLIC 
      ${gmp_dir}/lib/libgmp-10.lib
      ${gmp_dir}/lib/libmpfr-4.lib
      )

    target_link_libraries(diff_wall_points_test PUBLIC 
      ${gmp_dir}/lib/libgmp-10.lib
      ${gmp_dir}/lib/libmpfr-4.lib
      )
    
    target_link_libraries(line_triangle_intersect PUBLIC 
    ${gmp_dir}/lib/libgmp-10.lib
    ${gmp_dir}/lib/libmpfr-4.lib
    )  
endif()


