# Создаем статическую библиотеку из компонентов
add_library(GeometryComponents STATIC
	Node.cpp
	Edge.cpp
	Point.cpp
	Vertex.cpp
	Polygon.cpp
	)

target_include_directories(GeometryComponents PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
