
add_library(lib_stb INTERFACE)
# add current source dir to enable stb/std_image.h type include
target_include_directories(lib_stb INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
