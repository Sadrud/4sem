/*!
 * @file mainMethod.cpp
 * @brief Основной файл, в котором содержится алгоритм для поиска выпуклой оболочки.
 *  
 * В этом файле также содержатся вспомагательные методы для работы основного алгоритма.
 * Есть метод для печати получаемых данных с сервера в файл. 
 */

#pragma once

#include <vector>
#include "../Includes/Polygon.cpp"

/*!
 * @brief Печать вектора в файл
 * В начале файла печатается количество точек изначально, затем печаются все точки и только в конце печатаются точки, образующие выпуклую оболочку.
 * @param[in] folder, file, g, size Название папки, в которой хранятся файлы, название для файла, в котором буду хранится точки, вектор точек и размер вектора точек.
 */
template <typename T>
void printVector (std::string& folder, std::string& file, const std::vector<T>& g, int size) {
#ifdef _WIN32
	mkdir(folder.c_str());
#else
	mkdir(folder.c_str(), 0777);
#endif
	std::string filename = folder + '/' + file + ".txt";
	std::ofstream out(filename);

	/*if (size != 0)
		out << size << std::endl;*/

	for (const auto& val : g)
		out << val.x << " " << val.y << std::endl;

	out.close();
}

/*!
 * @brief Ключевой метод для работы алгоритма.
 * Данная функция определяет положение точки относительно соседних с помощью метода classify.
 * @param[in] s, p, side Точка из вектора точек, многоульник, в который собираеются точки выпуклой оболочки и направление поворота около точки
 */
void supportingLine(Point &s, Polygon *p, int side){
	int rotation = (side == static_cast<int>(Position::LEFT)) ? static_cast<int>(Turn::CLOCKWISE) : static_cast<int>(Turn::COUNTER_CLOCKWISE);
	Vertex *a = p->v();
	Vertex *b = p->neighbor(rotation);
	int c = b->classify(s, *a);
	while ((c == side) || (c == static_cast<int>(Position::BEHIND)) || (c == static_cast<int>(Position::BETWEEN))) {
		p->advance(rotation);
		a = p->v();
		b = p->neighbor(rotation);
		c = b->classify(s, *a);
	}
}


/*!
 * @brief Компаратор дл точек
 * Сравнение точек происходит по их положению на горизонтальной оси, а затем уже по вертикальной (если по горизонтальной одинаковы)
 * @param[in]  a, b Указатели на две точки
 * @return -1 если первая точка левее второй (если одинаковы по положению на горизонтальной оси, то если первая ниже второй), 1 в противном случае, 0 если это одна и та же точка.
 */
int leftToRightCmp(Point* a, Point* b) {
	if (a->x < b->x || (abs(a->x, b->x) <= epsilon && a->y < b->y)) return -1;
	if (a->x > b->x || (abs(a->x, b->x) <= epsilon && a->y > b->y)) return 1;
	return 0;
}

/*!
 * @brief Вспомагательный метод для сортировки для поиска индекса минимального элемента в имеющемся массиве.
 * @param[in] arr[], n, cmp Указатель на начало массива, длина массива, компаратор
 * @return Позиция наименьшего элемента в массиве
 */
template <typename T>
int positionOfSmallest (T* arr[], int n, int (*cmp)(T*, T*)) {
	int small = 0;
	T* smallest = arr[0];
	for (int i = 0; i < n; i++) {
		if (cmp(smallest, arr[i]) > 0) {
			smallest = arr[i];
			small = i;
		}
	}
	return small;
}

/*!
 * @brief Сортировка выбором
 * @param[in] arr[], n, cmp Указатель на начало массива, длина массива, компаратор
 */
template <typename T>
void selectionSort(T* arr[], int n, int (*cmp)(T*, T*)) {
	if (n > 0) {
		int i = positionOfSmallest (arr, n, cmp);
		std::swap(arr[0], arr[i]);
		selectionSort (arr+1, n-1, cmp);
	}
}

/*!
 * @brief Основной метод для поиска выпуклой оболочки множества точек.
 * Функция получает массив точек плоскости, сортирует из по положению на горизонтальной оси.
 * Берется каждая точка из массива и вычисляют ее положение с помощью вмпомагательных функций.
 * Подходящие точки добавляются в многоугольник.
 * @param[in] pts[], n Указатель на массив точек, количество точек.
 * @return Многоугольник, являющийся выпуклой оболочкой множество точек.
 */
Polygon *insertionHull2(Point pts[], int n) {
	Point **s = new Point*[n];
	for (int i = 0; i < n; i++) s[i] = &pts[i];
	selectionSort(s, n, leftToRightCmp);
	Polygon *p = new Polygon;
	p->insert(new Vertex(*s[0]));
	for (int i = 1; i < n; i++) {
		if (*s[i] == *s[i-1]) continue;
		supportingLine(*s[i], p, static_cast<int>(Position::LEFT));
		Vertex *l = p->v();
		supportingLine(*s[i], p, static_cast<int>(Position::RIGHT));
		delete p->split(l);
		p->insert(new Vertex(*s[i]));
	}
	delete [] s;
	return p;
}
