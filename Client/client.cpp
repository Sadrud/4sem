#include <iostream>
#include <vector>
#include <httplib.h>
#include <nlohmann/json.hpp>
#include "../Methods/mainMethod.cpp"

using json = nlohmann::json;

int main() {
	// Создаем массив точек для отправки
	std::mt19937 gen(std::time(nullptr));
	std::uniform_int_distribution<int> dist(1, 1000000);

	std::vector<int> vec;
	size_t size = 10000;

	for (size_t i = 0; i < size; ++i)
		vec.push_back(dist(gen));

	std::vector<Point> points;
	for (int i = 0; i < (vec.size()/2); i++) {
		Point a(vec[2*i], vec[2*i + 1]);
		points.push_back(a);
	}

	// Преобразуем точки в JSON
	json request_json;
	for (const auto& p : points) {
		request_json["points"].push_back({{"x", p.x}, {"y", p.y}});
	}

	// Отправляем POST-запрос на сервер
	httplib::Client cli("http://127.0.0.1:8080");
	auto res = cli.Post("/process", request_json.dump(), "application/json");

	if (res && res->status == 200) {
		// Парсим ответ и выводим результат
		auto response_json = json::parse(res->body);
		for (const auto& p : response_json["hull"]) {
			points.push_back (Point (p["x"], p["y"]));
		}

		std::string folder("input");
		std::string file("first");
		printVector (folder, file, points, (size/2));
	} else {
		std::cerr << "Ошибка: " << (res ? res->body : "Нет соединения") << "\n";
	}

	return 0;
}
