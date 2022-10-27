#include <cstdio>
#include <string>
#include <iostream>

template<typename T>
class FileLinkedList {
	FILE *fl;
	int ct; //number of elements
	int ff; //head of  free list

	//helper functions
	void writeData(int pos, const T &data) const;
	void writePrev(int pos, int prev) const;
	void writeNext(int pos, int next) const;
	void writeNode(int pos, const T &data, int prev, int next) const;
	void writeCtAndFF() const;
	void readData(int pos, const T &data) const;
	int readNext(int pos) const;
	int readPrev(int pos) const;

	public:
	typedef T value_type;
	class const_iterator{
	FILE * fptr;
                int index;
                public:
                        const_iterator(int i,FILE *f) : fptr{f}, index{i} {}
                        const_iterator(const const_iterator &i):fptr{i.fptr}, index{i.index} {}
                        T operator*() {
                                std::fseek(fptr,index*sizeof(T) + sizeof(int),SEEK_SET);
                                T ret;
                                std::fread(&ret,sizeof(T),1,fptr);
                                return ret;
                        }
                        bool operator==(const const_iterator &i) const { return index == i.index && fptr == i.fptr; }
                        bool operator!=(const const_iterator &i) const { return !(*this == i); }
                        const_iterator &operator=(const const_iterator &i) {
                                fptr = i.fptr;
                                index = i.index;
                                return *this;};
                        const_iterator &operator++() { ++index; return *this; }
                        const_iterator &operator--() { --index; return *this; }
                        const_iterator operator++(int) {
                                const_iterator tmp(*this);
                                ++index;
                                return tmp;
                        };
                        const_iterator operator--(int) {
                                const_iterator tmp(*this);
                                --index;
                                return tmp;
                        };

                        friend class FileArrayList;
	};
	//general methods
	FileLinkedList(const std::string &fname); //constructor

	template<typename I> // The type I will be an iterator.
	FileLinkedList(I begin,I end,const std::string &fname) {
	// TODO - Write this one here. It is easier than trying to fight with adding a template below.
	}
	~FileLinkedList() {std::fclose(fl);};
	void push_back(const T &t);
	void pop_back();
	int size() const;
	void clear();
	const_iterator insert(const_iterator position, const T &t);
	T operator[](int index) const;
	const_iterator erase(const_iterator position);
	void set(const T &value,int index);
	void set(const T &value,const_iterator position);

	const_iterator begin();
	const_iterator begin() const;
	const_iterator end();
	const_iterator end() const;
	const_iterator cbegin() const;
	const_iterator cend() const;
	
}:

template <typename T>
FileLinkedList(const std::string &fname) {
                fl = std::fopen(fname.c_str(),"r+b");
                if (fl == nullptr) {fl = std::fopen(fname.c_str(), "w+b");} // file did not exist
                std::fseek(fl,0,SEEK_END);
                if (std::ftell(fl) > 0) { // file already existed
                        std::fseek(fl,0,SEEK_SET);
                        std::fread(&ct,sizeof(int),1,fl);
			std::fread(&ff,sizeof(int),1,fl);
                }
                else {
                        ct = 0;
                        //std::fwrite(&ct,sizeof(int),1,fl);
			ff = -1;
			//std::fwrite(&ff,sieof(int),1,fl);
			writeCtAndFF();
			T sent;
			writeNode(0,sent,0,0);
                }
}

template <typename T>
void FileLinkedList<T>::push_back(const T &data) const {
	int newPos;
	if (ff < 0) {
		newPos = ct +1;
	} else {
		newPos = ff;
		ff = readNext(ff);
	}
	int tail = readPrev(0);
	writeNode(newPos,data,tail,0);
	writeNext(tail,newPos);
	writeNext(0, newPos);
	++ct;
	writeCtAndFF();
}

template <typename T>
void FileLinkedList<T>::writeNode(int pos, const T &data, int prev, int next) const {
	std::fseek(fl,2*sizeof(int) + pos*(sizeof(int)),SEEK_SET);
	std::fwrite(&data,sizeof(T),1,fl);
	std::fwrite(&prev,sizeof(int),1,fl);
	std::fwrite(&next,sizeof(int)1,fl);
}
