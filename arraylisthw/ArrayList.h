template<typename T>
class ArrayList {
public:
// Types
// value_type
// iterator
// const_iterator

// General Methods
ArrayList();
ArrayList(const ArrayList &that);
ArrayList<T> &operator=(const ArrayList<T> &al);

~ArrayList();
void push_back(const T &t); // add to the end.
void pop_back(); // remove last element.
int size() const;
void clear();
void insert(const T &t,int index); // insert this element before the given index.
const T &operator[](int index) const; // get the element at index.
T &operator[](int index); // get the element at index.
void remove(int index); // remove the item at the given index.

iterator begin();
const_iterator begin() const;
iterator end();
const_iterator end() const;
const_iterator cbegin() const;
const_iterator cend() const;
};

