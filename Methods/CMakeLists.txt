add_library(ProcessingMethods STATIC mainMethod.cpp)

target_include_directories(ProcessingMethods PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/Includes
	)

target_link_libraries(ProcessingMethods PRIVATE GeometryComponents)
