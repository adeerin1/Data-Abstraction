#include "Stack.h"

using namespace std;

template<typename T>
class ArrayStack : public Stack<T> {
	public:
		ArrayStack() {
		   max_sz = 10;
		   top = 0;
		   data = new T[max_sz];
		}
		ArrayStack(const ArrayStack<T> &a) : max_sz{a.max_sz}, top{a.top}, data{new T[a.max_sz]} {
			for (int j = 1; j < max_sz; j++) {
				data[j] = a.data[j];
			}
		}
		ArrayStack<T> &operator=(const ArrayStack<T> a) {
			T *s = new T[a.max_sz];
			for (int j = 1; j < a.max_sz; j++) {
				s[j] = a.data[j];
			}
			delete [] data;
			data = s;
			top = a.top;
			return *this;
		}
		~ArrayStack(){
		   delete [] data;
		}
		void push(const T &t){
			if(top == (max_sz-1)) {
				T* tempS = new T[max_sz*2];
				for (int j = 1; j < max_sz; j++) {
					tempS[j] = data[j];
				}
				delete [] data;
				data = tempS;
				max_sz *= 2;
			}
			data[++top] = t;
		};
		T pop() {
			return data[top--];
		};
		T peek() const {return data[top];};
		bool isEmpty() const {return top == 0;};
		void print() const {
			for (int j = 1; j <= top; j++) {
				cout << "j: " << data[j] << endl;
			}
		}
		void clear() {
			while(!isEmpty()) {
				pop();
			}
		};

	private:
		int max_sz;
		int top;
		T* data;

};
