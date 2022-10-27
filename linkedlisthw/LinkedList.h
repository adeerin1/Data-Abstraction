#include <iostream>

template<typename T>
class LinkedList {
	private:
		int ct;
		struct Node {
			Node *next; Node *prev;
			T data;
			Node() {}
		};
		Node sent;
	public:
		typedef T value_type;
		class iterator{
			private:
				Node* loc;
			public:
				iterator():loc(nullptr) {}
		};


		class const_iterator{
			private:
				const Node* loc;
			public:
				const_iterator():loc(nullptr) {}
				const_iterator(const Node* l):loc(l) {}
				bool operator==(const const_iterator &i) {return loc == i.loc;}
				bool operator!=(const const_iterator &i) {return !(*this == i);}
				const T& operator*() {return loc->data;}
				const_iterator& operator++() {loc = loc->next; return *this;}
				const_iterator& operator--() {loc = loc->prev; return*this;}
				const_iterator operator++(int) {
					const_iterator clone(loc);
					loc = loc->next;
					return clone;
				}
				const_iterator operator--(int) {
					const iterator clone(loc);
					loc = loc->prev;
					return clone;
				}

		};


		LinkedList():ct{0} {
			sent.next = &sent;
			sent.prev = &sent;
		}
		~LinkedList() {
			Node *rover = sent.next;
			while (rover != &sent) {
				Node *tmp = rover->next;
				delete rover;
				rover = tmp;
			}
		}
		int size() const{return ct;}
		void push_back(const T &t);
		const_iterator cbegin() const{return const_iterator(sent.next);}
		const_iterator cend() const{return const_iterator(&sent);}
};

template<typename T>
void LinkedList<T>::push_back(const T &t) {
	Node *n = new Node();
	n->data = t;
	n->prev = sent.prev;
	n->next = &sent;
	sent.prev = n;
	n->prev->next = n;
	++ct;
}

