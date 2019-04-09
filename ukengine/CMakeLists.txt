set (SOURCES byteio.cpp
	charset.cpp
	convert.cpp
	data.cpp
	error.cpp
	inputproc.cpp
	mactab.cpp
	pattern.cpp
	ukengine.cpp
	usrkeymap.cpp
)

add_library(ukengine STATIC ${SOURCES})
if (CMAKE_COMPILER_IS_GNUCC AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 8.0)
	set_target_properties(ukengine PROPERTIES COMPILE_FLAGS "-funsigned-char")
else()
	set_target_properties(ukengine PROPERTIES COMPILE_FLAGS "-funsigned-char -Wno-invalid-source-encoding")
endif()
