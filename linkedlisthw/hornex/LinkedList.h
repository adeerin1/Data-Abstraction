template<typename T>
class LinkedList {
	int ct;
	struct Node {
		Node *next, *prev;
		T data;
		Node() {}
	};
	Node sent;
	public:
		class iterator {
			Node * loc;
			public:
				iterator() : loc(nullptr) {}
				iterator(Node* l) { loc = l; }
				bool operator==(const iterator &i) {return loc == i.loc;}
				bool operator!=(const iterator &i) {return !(*this == i); }
				T& operator*() { return loc->data;}
				iterator& operator++() { loc = loc->next; return *this; }
				iterator& operator--() { loc = loc->prev; return *this; }
				iterator operator++(int) {
					iterator clone(loc);
					loc = loc->next;
					return clone;
				}
				iterator operator--(int) {
					iterator clone(loc);
					loc = loc->prev;
					return clone;
				}
				friend class LinkedList;
		};
		class const_iterator {
			const Node * loc;
			public:
				const_iterator() : loc(nullptr) {}
				const_iterator(const Node* l) { loc = l; }
				bool operator==(const const_iterator &i) {return loc == i.loc;}
				bool operator!=(const const_iterator &i) {return !(*this == i); }
				const T& operator*() { return loc->data;}
				const_iterator& operator++() { loc = loc->next; return *this; }
				const_iterator& operator--() { loc = loc->prev; return *this; }
				const_iterator operator++(int) {
					const_iterator clone(loc);
					loc = loc->next;
					return clone;
				}
				const_iterator operator--(int) {
					const_iterator clone(loc);
					loc = loc->prev;
					return clone;
				}
				friend class LinkedList;
		};
		LinkedList():ct{0} {
			sent.next = &sent;
			sent.prev = &sent;
		}

		LinkedList(const LinkedList<T> &that):ct(that.ct) {
			Node *rover = &sent;
			for (auto itr = that.cbegin(); itr != that.cend(); ++itr) { //implement pushback
				Node *tmp = new Node();
				tmp->data = *itr;
				tmp->prev = rover;
				rover->next = tmp;
				rover = rover->next;
				if (itr == --that.cend()) {
					rover->next = &sent;
					sent.prev = rover;
				}
			}
		}

		LinkedList &operator=(const LinkedList &that) { //copy assignment
			this->clear();
			this->ct = that.ct;
			Node *rover = &sent;
			for (auto itr = that.cbegin(); itr != that.cend(); ++itr) { //implement pushback
				Node *tmp = new Node();
				tmp->data = *itr;
				tmp->prev = rover;
				rover->next = tmp;
				rover = rover->next;
				if (itr == --that.cend()) {
					rover->next = &sent;
					sent.prev = rover;
				}
			}
			return *this;

		}
		~LinkedList() {
			Node *rover = sent.next;
			while (rover != &sent) {
				Node *tmp = rover->next;
				delete rover;
				rover = tmp;
			}
		}
		int size() const{
			return ct;
		}
		void clear() {
			ct = 0;
			Node* rover = sent.next;
			while(rover != &sent) {
				Node *tmp = rover->next;
				delete rover;
				rover = tmp;
			}
			sent.next = &sent;
			sent.prev = &sent;
		};
		void push_back(const T &t);
		void pop_back() {
			--ct;
			Node* orig = sent.prev;
			sent.prev = orig->prev;
			sent.prev->next = &sent;
			delete orig;
		}; //remove last element
		iterator insert(iterator position,const T &t) {
			Node* orig = position.loc;
			Node* n = new Node();
			n->data = t;
			n->next = orig;
			n->prev = orig->prev;
			orig->prev = n;
			n->prev->next = n;
			++ct;
			return iterator(n);
		}
		const T &operator[](int index) const {
			int count = 0;
			auto itr = cbegin();
			while (count != index) {++count; ++itr;}
			return *itr;
		}; //get the element at index
		T &operator[](int index) {
			int count = 0;
			auto itr = begin();
			while (count != index) {++count; ++itr;}
			return *itr;
		}; //get the element at index
		iterator erase(iterator position) {
			Node* orig = position.loc;
			orig->prev->next = orig->next;
			orig->next->prev = orig->prev;
			--ct;
			Node *tmp = orig->next;
			delete orig;
			return iterator(tmp);
		}; //remove the item at the given index
		const_iterator cbegin() const { return const_iterator(sent.next); }
		const_iterator cend() const { return const_iterator(&sent); }
		const_iterator begin() const { return const_iterator(sent.next); }
		const_iterator end() const { return const_iterator(&sent); }
		iterator begin() { return iterator(sent.next); }
		iterator end() { return iterator(&sent); }
		void print() {
			for (auto itr = this->cbegin(); itr != this->cend(); ++itr) {
				std::cout << *itr << std::endl;
			}
		};
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
