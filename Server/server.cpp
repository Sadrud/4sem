#include <iostream>
#include <vector>
#include "httplib.h"
#include <nlohmann/json.hpp> // Для работы с JSON
#include "../Methods/mainMethod.cpp"

using json = nlohmann::json;

int main() {
	httplib::Server svr;

	// Обработчик POST-запроса для получения точек и возврата оболочки
	svr.Post("/process", [](const httplib::Request& req, httplib::Response& res) {
			try {
			// Парсим JSON из тела запроса
			auto json_data = json::parse(req.body);
			std::vector<Point> points;

			// Преобразуем JSON в вектор точек
			for (const auto& item : json_data["points"]) {
				points.push_back({item["x"], item["y"]});
			}

			// Вычисляем выпуклую оболочку
			Polygon* hull = insertionHull2(points.data(), points.size());

			// Формируем JSON-ответ
			json response_json;

			response_json["hull"].push_back({{"x", hull->v()->x}, {"y", hull->v()->y}});
			for (Vertex* v = hull->v()->cw(); v != hull->v(); v = v->cw()) {
				response_json["hull"].push_back({{"x", v->x}, {"y", v->y}});
			}

			res.set_content(response_json.dump(), "application/json");
			delete hull;
			} catch (const std::exception& e) {
				res.status = 400;
				res.set_content(json({{"error", e.what()}}).dump(), "application/json");
			}
	});

	std::cout << "Сервер запущен на http://localhost:8080\n";
	svr.listen("127.0.0.1", 8080);

	return 0;
}
