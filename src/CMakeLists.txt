set(
    src_file
    ${CMAKE_CURRENT_SOURCE_DIR}/add.cpp
)
list(APPEND src_file  ${CMAKE_CURRENT_SOURCE_DIR}/subtraction.cpp)


set(src_file ${src_file} PARENT_SCOPE)