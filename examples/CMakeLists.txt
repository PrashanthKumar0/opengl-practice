project(opengl_practice)

file(GLOB main_files */main.cpp)


foreach(example_source_file ${main_files})
    string(REGEX REPLACE \\/ ";" example_source_file_path ${example_source_file})
    list(GET example_source_file_path -2 example_source_file_dirname)
    string(REPLACE " " "_" target_name ${example_source_file_dirname})

    # message("--- Target Name : ${target_name}")

    add_executable(${target_name} ${example_source_file})
    target_link_libraries(${target_name} opengl_practice)
    
endforeach(example_source_file ${main_files})
