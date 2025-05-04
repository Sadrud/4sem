#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <fstream>
#include <cmath>

static double epsilon = 1e-20;

enum class Position { LEFT, RIGHT, BEHIND, BEYOND, ORIGIN, BETWEEN, DESTINATION };

template <typename T>
static double abs (T x, T y) {
	if (x > y)
		return x-y;
	return y-x;
}

class Point {
	public:
		double x;
		double y;
		Point (double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
		~Point () {}

		int operator< (Point&);
		int operator> (Point&);
		int operator== (Point&);
		int operator!= (Point&);
		Point operator+ (Point&);
		double length ();
		int classify (Point&, Point&);
};

int Point::operator< (Point& p) { return ((x < p.x) || ((x == p.x) && (y < p.y))); }

int Point::operator> (Point& p) { return ((x > p.x) || ((x == p.x) && (y > p.y))); }

int Point::operator== (Point& p) { return (abs(x, p.x) <= epsilon && abs(y, p.y) <= epsilon); }

int Point::operator!= (Point& p) { return !(*this == p); }

Point Point::operator+ (Point& p) { return Point(x + p.x, y + p.y); }

double Point::length () { return std::sqrt((x*x) + (y*y)); }

int Point::classify (Point& p0, Point& p1) {
	Point p2 = *this;
	Point a(p1.x - p0.x, p1.y - p0.y);
	Point b(p2.x - p0.x, p2.y - p0.y);
	double sa = a.x * b.y - b.x * a.y;
	if (sa > 0.0)
		return static_cast<int>(Position::LEFT);
	if (sa < 0.0)
		return static_cast<int>(Position::RIGHT);
	if (a.x * b.x < 0.0 || a.y * b.y < 0.0)
		return static_cast<int>(Position::BEHIND);
	if (a.length() < b.length()) {
		return static_cast<int>(Position::BEYOND);
	}
	if (p0 == p2)
		return static_cast<int>(Position::ORIGIN);
	if (p1 == p2)
		return static_cast<int>(Position::DESTINATION);
	return static_cast<int>(Position::BETWEEN);

}

#endif
