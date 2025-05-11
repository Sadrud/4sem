/*!
 * @file tests.cpp
 * @brief Функция для генерации случайных точек.
 * 
 * Этот файл содержит код, который генерирует случайные точки.
 */

#include <random>
#include <vector>
#include "../Methods/mainMethod.cpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

/*!
 * @brief Функция создает вектор случайных точек для тестирования программы.
 * @param[in] size, diapozon, points Количество точек, диапазон расположения точек и указатель на массив точек.
 * @return Возвращает JSON, который будет передаваться серверу.
 */
json createJSON (int size, int diapozon, std::vector<Point>* points) {
	//Генерируем случайные числа
	std::mt19937 gen(std::time(nullptr));
	std::uniform_int_distribution<int> dist(1, diapozon);

	std::vector<int> vec;
	//Заполняем вектор рандомными значениями
	for (size_t i = 0; i < size; ++i)
		vec.push_back(dist(gen));

	//Создаем из вектора чисел, вектор точек
	for (int i = 0; i < (vec.size()/2); i++) {
		Point a(vec[2*i], vec[2*i + 1]);
		points->push_back(a);
	}

	// Преобразуем точки в JSON
	json request_json;
	for (const auto& p : *points)
		request_json["points"].push_back({{"x", p.x}, {"y", p.y}});

	return request_json;
}
