cmake_minimum_required(VERSION 3.10)
project(GeometryProcessor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Автоматическая загрузка зависимостей
#include(FetchContent)

# Загрузка httplib
#FetchContent_Declare(
#httplib
#	URL https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h
#	)
#FetchContent_MakeAvailable(httplib)

# Загрузка nlohmann/json
#FetchContent_Declare(
#	nlohmann_json
#	URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.hpp
#	)
#FetchContent_MakeAvailable(nlohmann_json)

# Подключаем подпроекты
add_subdirectory(Includes)
add_subdirectory(Methods)
add_subdirectory(Server)
add_subdirectory(Client)

# Добавляем цель для очистки Build
add_custom_target(clean_all
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/*
	COMMENT "Очистка папки Build"
	)
