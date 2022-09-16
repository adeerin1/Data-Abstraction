#include <iostream>

template<typename T>
class ArrayList {
	private:
		T* data;
		int ct;
		int max_sz;
public:
// Types
// value_type
	typedef T value_type;
// iterator
	class iterator {
		public:
			iterator(T *l) {};
			iterator() {};
			iterator(const iterator &i) {};
			T &operator*() {};
			bool operator==(const iterator &i) const {};
			bool operator!=(const iterator &i) const {};
			iterator &operator=(const iterator &i) {};
               		iterator &operator++() {};
               		iterator &operator--() {};
                	iterator operator++(int) {};
                	iterator operator--(int) {};	
	}
// const_iterator
	class const_iterator {
                public:
                	const_iterator(T *l) {};
                	const_iterator() {};
                	const_iterator(const const_iterator &i) {};
                	T &operator*() {};
                	bool operator==(const const_iterator &i) const {};
                	bool operator!=(const const_iterator &i) const {};
                	const_iterator &operator=(const const_iterator &i) {};
                	const_iterator &operator++() {};
                	const_iterator &operator--() {};
                	const_iterator operator++(int) {};
                	const_iterator operator--(int) {};
        };

// General Methods
ArrayList():data{new T[max_sz]}, ct{0}, max_sz{10} {}; //default constructor
ArrayList(const ArrayList &that) {}; //copy constructor
ArrayList<T> &operator=(const ArrayList<T> &al) {}; //copy assignment

~ArrayList(); //destructor
void push_back(const T &t) {}; // add to the end.
void pop_back() {}; // remove last element.
int size() const {}; //return the list size as an int
void clear() {}; //remove all elements from the arraylist
void insert(const T &t,int index) {

}; // insert this element before the given index.
const T &operator[](int index) const {}; // get the element at index.
T &operator[](int index) {}; // get the element at index.
void remove(int index) {}; // remove the item at the given index.
void print() const {
	for(int i = 0; i!= ct; ++i) {
		std::cout << i ": " << data[i] << std::endl;
	}
} 

iterator begin() {}; //return an iterator to the first element in the sequence
const_iterator begin() const {};
iterator end() {}; //return an iterator to the past-the-end element in the sequence
const_iterator end() const {};
const_iterator cbegin() const { return const_iterator(data); }; //where is the data instantiated
const_iterator cend() const { return const_iterator(data+ct); };
};

template<typename T>
void ArrayList<T>::insert(const T &t, int index) {
	for (int i = ct; i != index; --i) {
		data[i] = data[i-1];
	}
	data[idx] = t;
	++ct;
}

