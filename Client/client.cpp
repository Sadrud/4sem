/*!
 * @file client.cpp
 * @brief Основной файл клиента для вычисления выпуклой оболочки множества точек.
 *
 * Этот файл содержит реализацию HTTP-сервера, который отправляет наборы точек
 * и получает их выпуклую оболочку в формате JSON.
 */

#include <iostream>
#include <httplib.h>
#include "../Tests/tests.cpp"

using json = nlohmann::json;

/*!
 * @brief Основная функция тестового клиента.
 * 
 * Функция выполняет следующие действия:
 * 1. Генерирует массивы случайных чисел.
 * 2. Преобразует их в набор точек (каждые два числа — координаты x и y точки).
 * 3. Отправляет точки на сервер для вычисления выпуклой оболочки.
 * 4. Сохраняет исходные точки и полученнуе оболочки в файл.
 * 
 * @return int Код завершения программы (0 в случае успешного выполнения).
 */

int main(void) {
	std::vector<Point> *points1 = new std::vector<Point>;
	std::vector<Point> *points2 = new std::vector<Point>;
	std::vector<Point> *points3 = new std::vector<Point>;

	//Создаем JSON хранящий в себе точки
	json request_json1 = createJSON(10000, 1000000, points1);
	json request_json2 = createJSON(1000, 100000, points2);
	json request_json3 = createJSON(1000, 1000000, points3);

	// Отправляем POST-запрос на сервер
	httplib::Client cli1("http://127.0.0.1:8080");
	httplib::Client cli2("http://127.0.0.1:8080");
	httplib::Client cli3("http://127.0.0.1:8080");
	auto res1 = cli1.Post("/process", request_json1.dump(), "application/json");
	auto res2 = cli2.Post("/process", request_json2.dump(), "application/json");
	auto res3 = cli3.Post("/process", request_json3.dump(), "application/json");

	if ((res1 && res1->status == 200) && (res2 && res2->status == 200) && (res3 && res3->status == 200)) {
		// Парсим ответ и выводим результат
		auto response_json1 = json::parse(res1->body);
		auto response_json2 = json::parse(res2->body);
		auto response_json3 = json::parse(res3->body);
		for (const auto& p : response_json1["hull"])
			points1->push_back (Point (p["x"], p["y"]));
		for (const auto& p : response_json2["hull"])
			points2->push_back (Point (p["x"], p["y"]));
		for (const auto& p : response_json3["hull"])
			points3->push_back (Point (p["x"], p["y"]));

		std::string folder("input");
		std::string file1("first");
		std::string file2("second");
		std::string file3("third");
		printVector (folder, file1, *points1, points1->size());
		printVector (folder, file2, *points2, points2->size());
		printVector (folder, file3, *points3, points3->size());
	} else
		std::cerr << "Ошибка: " << ((res1 || res2 || res3) ? "Точки сохранены неправильно" : "Нет соединения") << "\n";

	delete points1;
	delete points2;
	delete points3;

	return 0;
}
