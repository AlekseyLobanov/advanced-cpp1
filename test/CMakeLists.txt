# build service
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/include)


add_subdirectory(allocator)
add_subdirectory(execute)
add_subdirectory(network)
add_subdirectory(storage)
