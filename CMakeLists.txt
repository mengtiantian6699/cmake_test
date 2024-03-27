# 若版本不够提醒用户升级到新的版本
cmake_minimum_required(VERSION 3.6)
SET (CMAKE_C_COMPILER             "/usr/bin/clang") # 填写绝对路径
SET (CMAKE_C_FLAGS                "-Wall -std=c99")
SET (CMAKE_C_FLAGS_DEBUG          "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

SET (CMAKE_CXX_COMPILER            "/usr/bin/clang++") # 填写绝对路径
SET (CMAKE_CXX_FLAGS                "-Wall")
SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

# 设置项目名称，非必要但是都应加上
project(test)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置项目的版本号
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)

#1. 使用 configure_file 生成 version.h 文件 还需要测试
configure_file(
    ${PROJECT_SOURCE_DIR}/version.h.in
    ${PROJECT_SOURCE_DIR}/include/version.h
)
#2.变量的设置方法 1 option(PRINTING "Enable solver printing" OFF) 变量名+描述+数值
#                2 set(PRINTING ON) 变量名+数值

#3.宏定义定义之后代码中可用
#4.PRINTING ON则if (PRINTING)为真  OFF if (PRINTING)为假的
set(PRINTING  ON)
if (PRINTING)
    add_compile_definitions(PRINTING)
endif()
    message( "printing is defined ${PRINTING}")


set(EMBEDDED OFF)
#4.(DEFINED EMBEDDED) 只要定义则为真 不管定义是ON还是OFF
if (DEFINED EMBEDDED)
    message(STATUS "embedded is defined")

else()
    message(STATUS "embedded not defined")
    message(FATAL_ERROR " embedded not defined fatal error test!!!")
endif()
# 
#5. 使用 osqp_configure.h.in 生成 osqp_configure.h 文件 
# 适应set设置变量的名称为ON时 则在osqp_configure.h生成相应的宏定义
#set设置变量的名称为OFF时 则在osqp_configure.h不会生成相应的宏定义
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/configure/osqp_configure.h.in
               ${CMAKE_CURRENT_SOURCE_DIR}/include/osqp_configure.h
               NEWLINE_STYLE LF)

#6endif() 是简单的结束条件语句块的标识符。它不会指定任何特定的条件。当 CMake 遇到 endif() 时，它将结束当前的条件语句块。
# endif(FORTRAN) 结束以 if(FORTRAN) 开始的条件语句块。它指定了条件，表示结束的是一个特定条件的语句块。但只结束指定条件的语句块，而不是所有条件语句块。
if(FORTRAN)
    message("Inside the FORTRAN condition.")
endif(FORTRAN)

if(FORTRAN)
    message("Inside the FORTRAN condition.")
endif()

#6. 设置库文件和可执行文件的存放目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

#7头文件添加路径
include_directories(${CMAKE_SOURCE_DIR}/include)
#8库文件路径
link_directories(${CMAKE_SOURCE_DIR}/lib)


#9立刻寻找src和include下的cmakelists文件并执行
#相应的文件夹下必须有CMakeLists.txt否则报错
add_subdirectory (src)
add_subdirectory (include)

#10添加宏定义
# 区别在于第二种情况中MATLAB宏不仅被定义了，还被赋予了一个特定的值，而第一种情况中MATLAB宏只是被定义了，但没有具体的值
add_definitions(-DMATLAB)
add_definitions(-DMATLAB=R2017b)
#11 ENABLE_FLAG可以通过  cmake -DENABLE_FLAG=ON .. 在编译时传参
if(ENABLE_FLAG)
    # 当 ENABLE_FLAG 被定义时执行的操作
    message("ENABLE_FLAG is defined.")
else()
    # 当 ENABLE_FLAG 未被定义时执行的操作
    message("ENABLE_FLAG is not defined.")
endif()
#12 如果 EMBEDDED 是一个字符串变量，你应该使用 if (NOT (EMBEDDED STREQUAL "1")) 来检查是否等于字符串 "1"。
#而如果 EMBEDDED 是一个数值型或布尔型变量，你应该使用 if (NOT (EMBEDDED EQUAL 1)) 来检查是否等于数值 1。

#在 CMake 中，变量的类型是动态的，它们没有明确的类型声明。变量的类型取决于赋给它们的值的类型。所以在 CMake 中，你无法显式地定义一个变量是字符串类型还是布尔类型。
#set(EMBEDDED "true")  # EMBEDDED 是字符串类型
#set(EMBEDDED TRUE)  # EMBEDDED 是布尔类型

if (NOT (EMBEDDED EQUAL 1))
endif()
if (NOT (EMBEDDED STREQUAL "1"))
endif()
# 13 在这个 CMake 脚本中，你首先定义了一个变量 osqp_src，用于存储源文件的路径。然后，根据条件是否为嵌入式系统，你可能会添加另一个源文件到 osqp_src 变量中。
# 最后，你将 osqp_src 变量传递给了父目录，以便在其他地方使用
set(
    osqp_src
    "${CMAKE_CURRENT_SOURCE_DIR}/auxil.c"
)
if (NOT (EMBEDDED EQUAL 1))
    list(
      APPEND
      osqp_src
      "${CMAKE_CURRENT_SOURCE_DIR}/kkt.c"
    )
endif()

set(
  osqp_src
  "${osqp_src}"
  PARENT_SCOPE
)
#14 生成静态库
add_library (asstatic STATIC ${src_file} ${include_file})
set_target_properties(asstatic PROPERTIES OUTPUT_NAME ass)

#15 生成静态库
add_library (asdynamic SHARED  ${src_file} ${include_file})
set_target_properties(asdynamic PROPERTIES OUTPUT_NAME ass)


add_library (asdynamic_test SHARED  ${src_file} ${include_file})
set_target_properties(asdynamic_test PROPERTIES OUTPUT_NAME asd)



#16 生成可执行文件
# 可执行文件可以包含头文件但是不用里面的函数则可以 不用链接库文件
add_executable(cmake_test src/cmake.cpp) # 生成可执行文件

#17 链接库文件 
# 可执行文件中使用了库中的函数则应当链接库文件
# 当前cmakelists中生成的库文件 也需要指定其路径才能链接 
# 不指定库文件的路径则找不到所连接的库。
target_link_libraries(cmake_test asd)
#18 如果指定的路径不对则 安装在/usr/local/lib/
install(TARGETS asstatic
        EXPORT  ${PROJECT_NAME}
         ARCHIVE       DESTINATION  ${CMAKE_CURRENT_SOURCE_DIR}/install_path
      )

# install(TARGETS asdynamic_test
#         EXPORT  ${PROJECT_NAME}
#         LIBRARY       DESTINATION  ${CMAKE_CURRENT_SOURCE_DIR}/install_path
#         ARCHIVE       DESTINATION  ${CMAKE_CURRENT_SOURCE_DIR}/install_path
#         RUNTIME       DESTINATION  ${CMAKE_CURRENT_SOURCE_DIR}/bin_install)

install(TARGETS asdynamic
        EXPORT  ${PROJECT_NAME}
        LIBRARY       DESTINATION  ${CMAKE_CURRENT_SOURCE_DIR}/install_path
  )

install(TARGETS cmake_test
        EXPORT  ${PROJECT_NAME}
        RUNTIME       DESTINATION  ${CMAKE_CURRENT_SOURCE_DIR}/bin_install)







