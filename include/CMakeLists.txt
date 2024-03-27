set(
    include_file
    ${CMAKE_CURRENT_SOURCE_DIR}/add.h
)
list(APPEND include_file  ${CMAKE_CURRENT_SOURCE_DIR}/subtraction.h)


set(include_file ${include_file} PARENT_SCOPE)