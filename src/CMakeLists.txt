add_library(unikey STATIC unikey.cpp)
add_dependencies(unikey ukengine)
target_include_directories(unikey PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../ukengine)
add_custom_command(TARGET unikey POST_BUILD COMMAND ar ARGS r libunikey.a ../ukengine/CMakeFiles/ukengine.dir/*.o)
