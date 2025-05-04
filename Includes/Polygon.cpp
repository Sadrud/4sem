#pragma once

#include "Edge.cpp"
#include "Vertex.cpp"
#include <sys/stat.h>

class Polygon {
	private:
		Vertex *v_;
		int size_;
		void resize(void);
	public:
		Polygon(void);
		Polygon(Polygon&);
		Polygon(Vertex*);
		~Polygon(void);
		Vertex* v(void);
		int size(void);
		Point point(void);
		Edge edge(void);
		Vertex* cw(void);
		Vertex* ccw(void);
		Vertex* neighbor(int rotation);
		Vertex* advance(int rotation);
		Vertex* setV(Vertex*);
		Vertex* insert(Point&);
		Vertex* insert(Vertex*);
		void remove(void);
		Polygon* split(Vertex*);

		void print(const std::string& filename);
};


Polygon::Polygon(void) : v_(nullptr), size_(0) {}

Polygon::Polygon (Polygon& p) {
	size_ = p.size_;
	if (size_ == 0)
		v_ == nullptr;
	else {
		v_ = new Vertex(p.point());
		for (int i = 1; i < size_; i++) {
			p.advance(static_cast<int>(Turn::CLOCKWISE));
			v_ = v_->insert(new Vertex(p.point()));
		}
		p.advance(static_cast<int>(Turn::CLOCKWISE));
		v_ = v_->cw();
	}
}

Polygon::Polygon(Vertex* v) : v_(v) { resize(); }

void Polygon::resize () {
	if (v_ == nullptr)
		size_ = 0;
	else {
		Vertex *v = v_->cw();
		for (size_ = 1; v != v_; v = v->cw()) {}
	}
}

Polygon::~Polygon(void) {
	if (v_) {
		Vertex* w = v_->cw();
		while (v_ != w){
			delete w->remove();
			w = v_->cw();
		}
		delete v_;
	}
}


Vertex* Polygon::v (void) { return v_; }

int Polygon::size () { return size_; }

Point Polygon::point (void) { return v_->point(); }

Edge Polygon::edge (void) { return Edge(point(), v_->cw()->point()); }

Vertex* Polygon::cw (void) { return v_->cw(); }

Vertex* Polygon::ccw (void) { return v_->ccw(); }

Vertex* Polygon::neighbor (int rotation) { return v_->neighbor(rotation); }

Vertex* Polygon::advance (int rotation) { return v_ = v_->neighbor(rotation); }

Vertex* Polygon::setV (Vertex* v) { return v_ = v; }

Vertex* Polygon::insert (Point& p) {
	if (size_++ == 0)
		v_ = new Vertex(p);
	else
		v_ = v_->insert(new Vertex(p));
	return v_;
}

Vertex* Polygon::insert (Vertex* v) {
	if (size_++ == 0)
		v_ = v;
	else
		v_ = v_->insert(v);
	return v_;
}

void Polygon::remove (void) {
	Vertex* v = v_;
	v_ = (--size_ == 0) ? nullptr : v_->ccw();
	delete v->remove();
}

Polygon* Polygon::split(Vertex* b) {
	Vertex* bp = v_->split(b);
	resize();
	return new Polygon(bp);
}

void Polygon::print (const std::string& filename) {
	std::string folder = "input";

#ifdef _WIN32
	mkdir(folder.c_str());
#else
	mkdir(folder.c_str(), 0777);
#endif

	std::string filepath = folder + "/" + filename + ".txt";
	std::ofstream out (filepath, std::ios::app);

	out << v_->x << " " << v_->y << std::endl;
	for (Vertex *v = v_->cw(); v != v_; v = v->cw()) 
		out << v->x << " " << v->y << std::endl;
	out.close();
}
