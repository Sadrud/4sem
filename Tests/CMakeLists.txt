add_library(ProcessingTests STATIC tests.cpp)

target_include_directories(ProcessingTests PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/Includes
	)

target_link_libraries(ProcessingTests PRIVATE GeometryComponents)
