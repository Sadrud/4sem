#ifndef EDGE_HPP
#define EDGE_HPP

#include "Point.cpp"

class Edge {
	private:
		Point org;
		Point dest;

	public:
		Edge (Point org_, Point dest_) : org(org_), dest(dest_) {}
		Edge () : org(Point(0, 0)), dest(Point(1, 0)) {}
		~Edge () {}
		friend std::ostream& operator<< (std::ostream& os, Edge& edge) {
			os << edge.org.x << " " << edge.org.y << " " << edge.dest.x << " " << edge.dest.y << std::endl;
			return os;
		}
		void print () { std::cout << "Edge: (" << org.x << ", " << org.y << ") -> (" << dest.x << ", " << dest.y << ")" << std::endl; }
		double org_x() { return org.x; }
		double org_y() { return org.y; }
		double dest_x() { return dest.x; }
		double dest_y() { return dest.y; }

};


#endif
