#include <stdio.h>
#include <string>
#include <iostream>

template <typename T>
class FileArrayList
{

	FILE *fl;
	int ct;
	void writeElem(int index, const T &t)
	{
		std::fseek(fl, index * sizeof(T) + sizeof(int), SEEK_SET);
		std::fwrite(&t, sizeof(T), 1, fl);
	}
	void writeCt()
	{
		std::fseek(fl, 0, SEEK_SET);
		std::fwrite(&ct, sizeof(int), 1, fl);
	}
	int readCount() const
	{
		int fct;
		std::fseek(fl, 0, SEEK_SET);
		std::fread(&fct, sizeof(int), 1, fl);
		return fct;
	}

public:
	class const_iterator
	{
		FILE *fptr;
		int index;

	public:
		const_iterator(int i, FILE *f) : fptr{f}, index{i} {}
		const_iterator(const const_iterator &i) : fptr{i.fptr}, index{i.index} {}
		T operator*()
		{
			std::fseek(fptr, index * sizeof(T) + sizeof(int), SEEK_SET);
			T ret;
			std::fread(&ret, sizeof(T), 1, fptr);
			return ret;
		}
		bool operator==(const const_iterator &i) const { return index == i.index && fptr == i.fptr; }
		bool operator!=(const const_iterator &i) const { return !(*this == i); }
		const_iterator &operator=(const const_iterator &i)
		{
			fptr = i.fptr;
			index = i.index;
			return *this;
		};
		const_iterator &operator++()
		{
			++index;
			return *this;
		}
		const_iterator &operator--()
		{
			--index;
			return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator tmp(*this);
			++index;
			return tmp;
		};
		const_iterator operator--(int)
		{
			const_iterator tmp(*this);
			--index;
			return tmp;
		};

		friend class FileArrayList;
	};

	// general methods
	FileArrayList(const std::string &fname)
	{
		fl = std::fopen(fname.c_str(), "r+b");
		if (fl == nullptr)
		{
			fl = std::fopen(fname.c_str(), "w+b");
		} // file did not exist
		std::fseek(fl, 0, SEEK_END);
		if (std::ftell(fl) > 0)
		{ // file already existed
			std::fseek(fl, 0, SEEK_SET);
			std::fread(&ct, sizeof(int), 1, fl);
		}
		else
		{
			ct = 0;
			std::fwrite(&ct, sizeof(int), 1, fl);
		}
	}
	template <typename I> // The type I will be an iterator.
	FileArrayList(I begin, I end, const std::string &fname)
	{
		fl = std::fopen(fname.c_str(), "w+b");
		ct = 0;
		writeCt();
		while (begin != end)
		{
			push_back(*begin);
			// std::cout << *begin << std::endl;
			++begin;
		}
	}
	~FileArrayList() { std::fclose(fl); };
	void pop_back()
	{
		--ct;
		writeCt();
	}
	int size() const { return ct; }
	const_iterator insert(const_iterator position, const T &t)
	{
		const_iterator rover = --end();
		push_back(*(end()));
		for (auto itr = --end(); itr != position; --itr)
		{
			writeElem(itr.index, *rover);
			--rover;
		}
		++rover;
		writeElem(rover.index, t);
		return rover;
	}
	T operator[](int index) const
	{
		T ret;
		std::fseek(fl, index * sizeof(T) + sizeof(int), SEEK_SET); 
		std::fread(&ret, sizeof(int), 1, fl);
		return ret;
	}; // get the element at that index
	const_iterator erase(const_iterator position)
	{
		auto rover = position;
		for (auto itr = ++position; itr != end(); ++itr)
		{
			writeElem(rover.index,*itr);
			++rover;
		}
		--ct;
		writeCt();
	};									 // erase element at that index
	void set(const T &value, int index){
		writeElem(index,value);
	}; // change the value of an element at a given index
	void print()
	{
		std::cout << "Ct: " << ct << std::endl;
		for (auto itr = begin(); itr != end(); ++itr)
		{
			std::cout << *itr << std::endl;
		}
	}

	// Done at the bottom
	void push_back(const T &t);
	void clear();
	// delete functions
	FileArrayList(const FileArrayList &that) = delete;
	FileArrayList<T> &operator=(const FileArrayList<T> &al) = delete;

	const_iterator begin() { return const_iterator(0, fl); }
	const_iterator begin() const { return const_iterator(0, fl); }
	const_iterator end() { return const_iterator(ct, fl); }
	const_iterator end() const { return const_iterator(ct, fl); }
	const_iterator cbegin() const { return const_iterator(0, fl); }
	const_iterator cend() const { return const_iterator(ct, fl); }
};

template <typename T>
void FileArrayList<T>::push_back(const T &t)
{
	writeElem(ct, t);
	++ct;
	writeCt();
}

template <typename T>
void FileArrayList<T>::clear()
{
	ct = 0;
	writeCt();
}
