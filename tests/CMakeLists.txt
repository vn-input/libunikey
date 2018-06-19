add_executable(tests EXCLUDE_FROM_ALL main.cpp)
target_link_libraries(tests unikey)
target_include_directories(tests PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_custom_command(TARGET tests POST_BUILD COMMAND tests)
