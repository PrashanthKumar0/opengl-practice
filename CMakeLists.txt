cmake_minimum_required(VERSION 3.28.0)

project(opengl_practice VERSION 0.0.1)

# set c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


# build vendor
add_subdirectory(vendor)

# build opengl_practice library
add_subdirectory(src)


option(BUILD_EXAMPLES "Build Examples?" ON)

if(BUILD_EXAMPLES)
    # build examples
    message("Will Build Examples")
    add_subdirectory(examples)

endif(BUILD_EXAMPLES)