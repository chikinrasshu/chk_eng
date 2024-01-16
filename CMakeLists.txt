cmake_minimum_required(VERSION 3.27)
project(chk_eng C)

find_package(glfw3 CONFIG REQUIRED)

add_executable(chk_eng src/main.c
        src/common.h
        src/log.c
        src/log.h
        src/window.c
        src/window.h
        src/file.c
        src/file.h
        src/wav.c
        src/wav.h)
target_compile_features(chk_eng PRIVATE c_std_11)

target_link_libraries(chk_eng PRIVATE glfw)


add_custom_command(TARGET chk_eng PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_SOURCE_DIR}/data" $<TARGET_FILE_DIR:chk_eng>/data
)
