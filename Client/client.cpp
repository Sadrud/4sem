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
	// Передаются в createJSON
	std::vector<Point> points1;
	std::vector<Point> points2;
	std::vector<Point> points3;

	try {
		//Создаем JSON хранящий в себе точки
		std::cout << "Test 1." << std::endl;
		json request_json1 = createJSON(points1);
		//Количество изначально введенных точек
		int quantityPoints1 = 0;
		for (const auto& p : request_json1["points"])
			quantityPoints1++;
		std::cout << std::endl;

		std::cout << "Test 2." << std::endl;
		json request_json2 = createJSON(points2);
		//Количество изначально введенных точек
		int quantityPoints2 = 0;
		for (const auto& p : request_json1["points"])
			quantityPoints2++;
		std::cout << std::endl;

		std::cout << "Test 3." << std::endl;
		json request_json3 = createJSON(points3);
		//Количество изначально введенных точек
		int quantityPoints3 = 0;
		for (const auto& p : request_json1["points"])
			quantityPoints3++;

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
			
			//Для сохранения оболочек
			std::vector<Point> hull1;
			std::vector<Point> hull2;
			std::vector<Point> hull3;

			for (const auto& p : response_json1["hull"])
				hull1.push_back (Point (p["x"], p["y"]));
			for (const auto& p : response_json2["hull"])
				hull2.push_back (Point (p["x"], p["y"]));
			for (const auto& p : response_json3["hull"])
				hull3.push_back (Point (p["x"], p["y"]));

			std::string folder("input");
			std::string file1("first");
			std::string file2("second");
			std::string file3("third");
			printVector (folder, file1, hull1, quantityPoints1);
			printVector (folder, file2, hull2, quantityPoints2);
			printVector (folder, file3, hull3, quantityPoints3);
		} else
			std::cerr << "Ошибка: " << ((res1 || res2 || res3) ? "Точки сохранены неправильно" : "Нет соединения") << "\n";
	} catch (const std::exception& e) { std::cerr << "Error: " << e.what() << std::endl; }

	return 0;
}
