add_executable(GeometryClient client.cpp)

target_include_directories(GeometryClient PRIVATE
	${CMAKE_SOURCE_DIR}/Includes
	${nlohmann_json_SOURCE_DIR}
	${httplib_SOURCE_DIR}
	)

target_link_libraries(GeometryClient PRIVATE
	GeometryComponents
	pthread
	)
