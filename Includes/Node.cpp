#ifndef NODE_HPP
#define NODE_HPP

class Node {
	protected:
		Node* next_;
		Node* prev_;

	public:
		Node () : next_(this), prev_(this) {}
		~Node () {}
		virtual Node* next () { return next_; }
		virtual Node* prev () { return prev_; }
		Node* insert (Node*);
		Node* remove ();
		void splice (Node*);
};


Node* Node::insert (Node* n) {
	Node* c = next_;
	n->next_ = c;
	n->prev_ = this;
	next_ = n;
	c->prev_ = n;
	return n;
}

Node* Node::remove () {
	prev_->next_ = next_;
	next_->prev_ = prev_;
	next_ = prev_ = this;
	return this;
}

void Node::splice (Node* b) {
	Node* a = this;
	Node* an = a->next_;
	Node* bn = b->next_;
	a->next_ = bn;
	b->next_ = an;
	an->prev_ = b;
	bn->prev_ = a;
}


#endif
