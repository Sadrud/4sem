#include <vector>
#include <random>
#include <ctime>
#include "../Methods/mainMethod.cpp"

#define PI 3.1415926535

int main () {

	Polygon* arr = new Polygon[10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 6; j++){
			Point a(i + 2 * cos((PI/3) * j), 2 * sin((PI/3) * j));
			arr[i].insert(a);
		}	
	}

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

	std::string folder("input");
	std::string file("first");
	printVector(folder, file, points, size/2);

	Polygon *pol = insertionHull2 (points.data(), points.size());
	pol->print("first");

	delete [] arr;
	delete pol;

	return 0;
}
