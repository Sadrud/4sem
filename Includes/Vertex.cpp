#pragma once 

#include "Node.cpp"
#include "Point.cpp"

enum class Turn { CLOCKWISE, COUNTER_CLOCKWISE };

class Vertex : public Node, public Point { 
	public:  
		Vertex(double x, double y);  
		Vertex(Point);  
		Vertex *cw(void);  
		Vertex *ccw(void);  
		Vertex *neighbor(int rotation);  
		Point point(void);  
		Vertex *insert(Vertex*);  
		Vertex *remove(void);  
		void splice(Vertex*);  
		Vertex *split(Vertex*);  
		friend class Polygon;  
};


Vertex::Vertex (double x, double y) : Point(x, y) {}

Vertex::Vertex (Point p) : Point(p) {}

Vertex *Vertex::cw (void) { if (static_cast<Vertex*>(next()) == nullptr) std::cout << "dssdkm" << std::endl; return static_cast<Vertex*>(next()); }

Vertex *Vertex::ccw (void) { return static_cast<Vertex*>(prev()); }

Vertex *Vertex::neighbor (int rotation) { return ((rotation == static_cast<int>(Turn::CLOCKWISE)) ? cw() : ccw()); }

Point Vertex::point (void) { return *(dynamic_cast<Point*>(this)); }

Vertex *Vertex::insert (Vertex *v) { return dynamic_cast<Vertex*>(Node::insert(v)); }

Vertex *Vertex::remove (void) { return dynamic_cast<Vertex*>(Node::remove()); }

void Vertex::splice (Vertex *v) { Node::splice(v); }

Vertex* Vertex::split (Vertex* b) {
	Vertex* bp = b->ccw()->insert(new Vertex(b->point()));
	insert(new Vertex(point()));
	splice (bp);
	return bp;
}
