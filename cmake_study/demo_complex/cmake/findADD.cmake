# 在指定目录下寻找头文件和动态库文件的位置，可以指定多个目标路径
# note: NAMES PATHS 均可以省略
# 在指定目录中搜索 libadd.h 的目录路径并赋值给变量 ADD_INCLUDE_DIR
find_path(ADD_INCLUDE_DIR NAMES libadd.h PATHS /usr/include/ /usr/local/include ${CMAKE_SOURCE_DIR}/ModuleMode)
# 在指定目录中搜索 libNAMES.so or libNAMES.a or NAMES.lib NAMES.dll
find_library(ADD_LIBRARY NAMES add PATHS /usr/lib/add /usr/local/lib/add ${CMAKE_SOURCE_DIR}/ModuleMode)
if (ADD_INCLUDE_DIR AND ADD_LIBRARY)
    set(ADD_FOUND TRUE)
endif (ADD_INCLUDE_DIR AND ADD_LIBRARY)
