add_executable(GeometryServer server.cpp)

target_include_directories(GeometryServer PRIVATE
	${CMAKE_SOURCE_DIR}/Includes
	${CMAKE_SOURCE_DIR}/Methods
	${nlohmann_json_SOURCE_DIR}
	${httplib_SOURCE_DIR}
	)

target_link_libraries(GeometryServer PRIVATE
	GeometryComponents
	ProcessingMethods
	pthread
	)
