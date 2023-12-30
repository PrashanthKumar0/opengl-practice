project(opengl_practice)

file(GLOB lib_source_files *.cpp)

# message("Found Files : ${files}")

add_library(opengl_practice ${lib_source_files})
target_include_directories(opengl_practice PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(opengl_practice PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(opengl_practice glfw glad glm lib_stb)
