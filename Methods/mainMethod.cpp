#pragma once

#include <vector>
#include "../Includes/Polygon.cpp"

template <typename T>
void printVector (std::string& folder, std::string& file, const std::vector<T>& g, int size) {
#ifdef _WIN32
	mkdir(folder.c_str());
#else
	mkdir(folder.c_str(), 0777);
#endif
	std::string filename = folder + '/' + file + ".txt";
	std::ofstream out(filename);

	if (size != 0)
		out << size << std::endl;

	for (const auto& val : g)
		out << val.x << " " << val.y << std::endl;

	out.close();
}

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


int leftToRightCmp(Point* a, Point* b) {
	if (a->x < b->x || (abs(a->x, b->x) <= epsilon && a->y < b->y)) return -1;
	if (a->x > b->x || (abs(a->x, b->x) <= epsilon && a->y > b->y)) return 1;
	return 0;
}


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


template <typename T>
void selectionSort(T* arr[], int n, int (*cmp)(T*, T*)) {
	if (n > 0) {
		int i = positionOfSmallest (arr, n, cmp);
		std::swap(arr[0], arr[i]);
		selectionSort (arr+1, n-1, cmp);
	}
}


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
