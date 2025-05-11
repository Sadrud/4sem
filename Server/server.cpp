/*!
 * @file server.cpp
 * @brief Основной файл сервера для вычисления выпуклой оболочки множества точек.
 * 
 * Этот файл содержит реализацию HTTP-сервера, который принимает POST-запросы с набором точек
 * и возвращает их выпуклую оболочку в формате JSON.
 */

#include <iostream>
#include <vector>
#include "httplib.h"
#include <nlohmann/json.hpp> // Для работы с JSON
#include "../Methods/mainMethod.cpp"

using json = nlohmann::json;

/*!
 * @brief Основная функция, запускающая HTTP-сервер.
 * 
 * Сервер обрабатывает POST-запросы на эндпоинт `/process`, принимает JSON с массивом точек,
 * вычисляет их выпуклую оболочку и возвращает её в формате JSON.
 * 
 * @return int Код завершения программы (0 в случае успешного завершения).
 */
int main() {
	httplib::Server svr;

	 /*!
	  * @brief Обработчик POST-запроса для вычисления выпуклой оболочки.
	  * 
	  * Принимает JSON вида:
	  * ```json
	  * {
	  *     "points": [
	  *         {"x": 0, "y": 0},
	  *         {"x": 1, "y": 1},
	  *         ...
	  *     ]
	  * }
	  * ```
	  * 
	  * Возвращает JSON с вершинами выпуклой оболочки:
	  * ```json
	  * {
	  *     "hull": [
	  *         {"x": 0, "y": 0},
	  *         {"x": 1, "y": 1},
	  *         ...
	  *     ]
	  * }
	  * ```
	  * 
	  * В случае ошибки возвращает JSON с сообщением об ошибке:
	  * ```json
	  * {
	  *     "error": "Описание ошибки"
	  * }
	  * ```
	  */

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
