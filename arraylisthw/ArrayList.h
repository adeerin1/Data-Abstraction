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
			T* loc;
			iterator(T *l):loc(l) {};
			iterator():loc(nullptr) {};
			iterator(const iterator &i):loc(i.loc) {};
			T &operator*() {return *loc;};
			bool operator==(const iterator &i) const {return loc == i.loc;};
			bool operator!=(const iterator &i) const {return !(*this == i);};
			iterator &operator=(const iterator &i) { loc = i.loc; return *this;};
               		iterator &operator++() {++loc; return *this;};
               		iterator &operator--() {--loc; return *this;};
                	iterator operator++(int) {
				const_iterator tmp(*this);
				++loc;
				return tmp;
			};
                	iterator operator--(int) {
				const_iterator tmp(*this);
				--loc;
				return tmp;
			};	
	};
// const_iterator
	class const_iterator {
                public:
			T* loc;
                	const_iterator(T *l):loc(l) {}; //parameterized constructor
                	const_iterator() { loc = nullptr; }; //default constructor
                	const_iterator(const const_iterator &i) { loc = i.loc; }; //copy constructor
                	const T &operator*() { return *loc; };
                	bool operator==(const const_iterator &i) const {return loc == i.loc;};
                	bool operator!=(const const_iterator &i) const { return !(*this == i);};
                	const_iterator &operator=(const const_iterator &i) {loc = i.loc; return *this;};
                	const_iterator &operator++() {++loc; return*this; };
                	const_iterator &operator--() {--loc; return *this; };
                	const_iterator operator++(int) {
				const_iterator tmp(*this);
				++ loc;
				return tmp;
			};
                	const_iterator operator--(int) {
				const_iterator tmp(*this);
				--loc;
				return tmp;
			};
        };

// General Methods
ArrayList():max_sz(1000), data{new T[max_sz]}, ct{0} {}; //default constructor
ArrayList(const ArrayList &that):data{new T[that.max_sz]}, ct{that.ct}, max_sz{that.max_sz} {
	for(int i = 0; i < ct; ++i) {
		data[i] = that.data[i];
	}
}; //copy constructor
ArrayList<T> &operator=(const ArrayList<T> &al) {
	ct = al.ct;
	max_sz = al.max_sz;
	delete [] data;
	data = new T[max_sz];
	for(int i = 0; i < ct; ++i) {
		data[i] = al.data[i];
	}
	return *this;
}; //copy assignment

~ArrayList() {
	delete [] data;
}; //destructor
void push_back(const T &t) {
	if (ct == max_sz) { //allocating more array length
		max_sz *= 2;
		//std::cout << "New max size: " << max_sz << std::endl;
		T* tempA = new T[max_sz];
		//std::cout << "Allocated new array of size " << max_sz << std::endl;
		for(int i = 0; i < ct; ++i) {
			tempA[i] = data[i];
		}
		delete [] data;
		data = tempA;
		//std::cout << "Copied array: \n";
	}
	data[ct++] = t;
}; // add to the end.
void pop_back() { --ct; }; // remove last element.
int size() const {return ct;}; //return the list size as an int
void clear() {ct = 0;}; //remove all elements from the arraylist
void insert(const T &t, int index) {
        /*if (ct == max_sz) { //allocating more array length
                T* tmp = new T[max_sz*2];
                for(int i = 0; i < ct; ++i) {
                        tmp[i] = data[i];
                }
                delete [] data;
                data = tmp;
                max_sz *= 2;
        }*/
	for (int i = ct; i != index; --i) {
                data[i] = data[i-1];
        }
        data[index] = t;
	++ct;
}

const T &operator[](int index) const {return data[index];}; // get the element at index.
T &operator[](int index) { return data[index]; }; // get the element at index.
void remove(int index) {
	for (int i = index; i < ct; ++i) {
                data[i] = data[i+1];
        }
	--ct;
}; // remove the item at the given index.
void print() const {
	for(int i = 0; i!= ct; ++i) {
		std::cout << i << ": " << data[i] << std::endl;
	}
} 

iterator begin() { return iterator(data);}; //return an iterator to the first element in the sequence
const_iterator begin() const { return const_iterstor(data);};
iterator end() {return iterator(data+ct);}; //return an iterator to the past-the-end element in the sequence
const_iterator end() const {return const_iterator(data+ct);};
const_iterator cbegin() const { return const_iterator(data); };
const_iterator cend() const { return const_iterator(data+ct); };
};

