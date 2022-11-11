#include <cstdio>
#include <string>
#include <iostream>
#include "ArrayStack.h"

template <typename T>
class FileLinkedList
{
	FILE *fl;
	int ct;				// number of elements
	ArrayStack<int> ff; // free list stack

	// helper functions
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
	class const_iterator
	{
		FILE *fptr;
		int index;
		int pos;

	public:
		const_iterator(int i, int p, FILE *f) : fptr{f}, pos{p}, index{i} {}
		const_iterator(const const_iterator &i) : fptr{i.fptr}, pos(i.pos), index{i.index} {}
		T operator*()
		{
			T data;
			std::fseek(fptr, 2 * sizeof(int) + pos * (sizeof(T) + 2 * sizeof(int)), SEEK_SET);
			std::fread(&data, sizeof(T), 1, fptr);
			return data;
		}
		bool operator==(const const_iterator &i) const
		{
			// std::cout << "First node) index: " << index << " pos: " << pos << std::endl;
			// std::cout << "Second node) index: " << i.index << " pos: " << i.pos << std::endl;
			return index == i.index; //&& pos == i.pos && fptr == i.fptr;
		}
		bool operator!=(const const_iterator &i) const { return !(*this == i); }
		const_iterator &operator=(const const_iterator &i)
		{
			fptr = i.fptr;
			index = i.index;
			pos = i.pos;
			return *this;
		};
		const_iterator &operator++()
		{
			int next;
			std::fseek(fptr, 2 * sizeof(int) + pos * (sizeof(T) + 2 * sizeof(int)) + sizeof(T) + sizeof(int), SEEK_SET);
			std::fread(&next, sizeof(int), 1, fptr);
			++index;
			pos = next;
			return *this;
		}
		const_iterator &operator--()
		{
			int prev;
			std::fseek(fptr, 2 * sizeof(int) + pos * (sizeof(T) + 2 * sizeof(int)) + sizeof(T), SEEK_SET);
			std::fread(&prev, sizeof(int), 1, fptr);
			--index;
			pos = prev;
			return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator tmp(*this);
			int next;
			std::fseek(fptr, 2 * sizeof(int) + pos * (sizeof(T) + 2 * sizeof(int)) + sizeof(T) + sizeof(int), SEEK_SET);
			std::fread(&next, sizeof(int), 1, fptr);
			++index;
			pos = next;
			return tmp;
		};
		const_iterator operator--(int)
		{
			const_iterator tmp(*this);
			int prev;
			std::fseek(fptr, 2 * sizeof(int) + pos * (sizeof(T) + 2 * sizeof(int)) + sizeof(T), SEEK_SET);
			std::fread(&prev, sizeof(int), 1, fptr);
			--index;
			pos = prev;
			return tmp;
		};

		friend class FileLinkedList;
	};
	// general methods
	FileLinkedList(const std::string &fname)
	{
		fl = std::fopen(fname.c_str(), "r+b");
		if (fl == nullptr)
		{
			fl = std::fopen(fname.c_str(), "w+b");
		} // file did not exist
		std::fseek(fl, 0, SEEK_END);
		if (std::ftell(fl) > 0)
		{ // file has content
			//std::cout << "File has content\n";
			int free;
			ff.clear();
			std::fseek(fl, 0, SEEK_SET);
			std::fread(&ct, sizeof(int), 1, fl);
			std::fread(&free, sizeof(int), 1, fl);
			ff.push(free);
		}
		else
		{
			//std::cout << "empty file\n";
			ct = 0;
			// std::fwrite(&ct,sizeof(int),1,fl);
			ff.clear();
			// std::fwrite(&ff,sieof(int),1,fl);
			clear();
			writeCtAndFF();
			T sent;
			writeNode(0, sent, 0, 0);
		}
	};									   // constructor
	~FileLinkedList() { std::fclose(fl); } // done
	void push_back(const T &t);			   // done
	void pop_back();					   // done
	int size() const { return ct; };	   // done
	void clear()						   // done
	{
		ct = 0;
		ff.clear();
		writeCtAndFF();
		T data;
		writeNode(0, data, 0, 0);
	};
	T operator[](int index) const;					   // done
	void set(const T &value, int index);			   // done
	void set(const T &value, const_iterator position); // done
	void print() const;								   // done

	const_iterator insert(const_iterator position, const T &t)
	{
		int prev = (--position).pos;
		int next = (++position).pos;
		writeNode(ct + 1, t, prev, next);
		writePrev(next, ct + 1);
		writeNext(prev, ct + 1);
		++ct;
		writeCtAndFF();
		return --position;
	};

	const_iterator erase(const_iterator position)
	{
		int prev = (--position).pos;
		int next = (++ ++position).pos;
		writePrev(next, prev);
		writeNext(prev, next);
		--ct;
		writeCtAndFF();
		return position;
	};

	template <typename I> // The type I will be an iterator.
	FileLinkedList(I begin, I end, const std::string &fname)
	{
		fl = std::fopen(fname.c_str(), "w+b");
		clear();
		for (auto itr = begin; itr != end; ++itr) {
			push_back(*itr);
			//std::cout << "Pushing back: " << *itr << std::endl;
		}
	}

	// iterator instantiation
	const_iterator begin()
	{
		int sentnext;
		fseek(fl, 2 * sizeof(int) + sizeof(T) + sizeof(int), SEEK_SET);
		std::fread(&sentnext, sizeof(int), 1, fl);
		return const_iterator(0, sentnext, fl);
	}
	const_iterator begin() const
	{
		int sentnext;
		fseek(fl, 2 * sizeof(int) + sizeof(T) + sizeof(int), SEEK_SET);
		std::fread(&sentnext, sizeof(int), 1, fl);
		return const_iterator(0, sentnext, fl);
	}
	const_iterator end()
	{
		return const_iterator(ct, 0, fl);
	}
	const_iterator end() const
	{
		return const_iterator(ct, 0, fl);
	}
	const_iterator cbegin() const
	{
		int sentnext;
		fseek(fl, 2 * sizeof(int) + sizeof(T) + sizeof(int), SEEK_SET);
		std::fread(&sentnext, sizeof(int), 1, fl);
		return const_iterator(0, sentnext, fl);
	}
	const_iterator cend() const
	{
		return const_iterator(ct, 0, fl);
	}
};

// templated functions
template <typename T>
void FileLinkedList<T>::push_back(const T &data)
{
	int newPos;
	ff.clear(); // remove later?
	if (ff.isEmpty())
	{
		newPos = ct + 1;
	}
	else
	{
		newPos = ff.pop();
	}
	int tail = readPrev(0);
	writeNode(newPos, data, tail, 0);
	writeNext(tail, newPos);
	writePrev(0, newPos);
	++ct;
	writeCtAndFF();
	// std::cout << "node data: " << data << " pos: " << newPos << " prev: " << readPrev(newPos) << " Next: " << readNext(newPos) << std::endl;
	// std::cout << "sentinel prev: " << readPrev(0) << " Next: " << readNext(0) << std::endl;
}

template <typename T>
void FileLinkedList<T>::print() const
{
	std::cout << "Size: " << ct << endl;
	for (auto itr = begin(); itr != end(); ++itr)
	{
		std::cout << "index: " << itr.index << " pos: " << itr.pos << " Data: " << *itr << " prev: " << readPrev(itr.pos) << " Next: " << readNext(itr.pos) << std::endl;
	}
};

template <typename T>
void FileLinkedList<T>::pop_back()
{
	int tail = readPrev(0);
	writeNext(readPrev(tail), 0);
	writePrev(0, readPrev(tail));
	--ct;
	writeCtAndFF();
}

template <typename T>
T FileLinkedList<T>::operator[](int index) const
{
	auto itr = begin();
	int i = 0;
	while (i < index)
	{
		++i;
		++itr;
	}
	return *itr;
};

template <typename T>
void FileLinkedList<T>::set(const T &value, int index)
{
	auto itr = begin();
	int i = 0;
	while (i < index)
	{
		++i;
		++itr;
	}
	writeData(itr.pos, value);
};

template <typename T>
void FileLinkedList<T>::set(const T &value, const_iterator position)
{
	writeData(position.pos, value);
};

// helper functions
template <typename T>
void FileLinkedList<T>::writeNode(int pos, const T &data, int prev, int next) const
{
	std::fseek(fl, 2 * sizeof(int) + pos * (sizeof(T) + 2 * sizeof(int)), SEEK_SET);
	std::fwrite(&data, sizeof(T), 1, fl);
	std::fwrite(&prev, sizeof(int), 1, fl);
	std::fwrite(&next, sizeof(int), 1, fl);
}

template <typename T>
void FileLinkedList<T>::writeData(int pos, const T &data) const
{
	std::fseek(fl, 2 * sizeof(int) + pos * (sizeof(T) + 2 * sizeof(int)), SEEK_SET);
	std::fwrite(&data, sizeof(T), 1, fl);
};

template <typename T>
void FileLinkedList<T>::writePrev(int pos, int prev) const
{
	std::fseek(fl, 2 * sizeof(int) + pos * (sizeof(T) + 2 * sizeof(int)) + sizeof(T), SEEK_SET);
	std::fwrite(&prev, sizeof(int), 1, fl);
};

template <typename T>
void FileLinkedList<T>::writeNext(int pos, int next) const
{
	std::fseek(fl, 2 * sizeof(int) + pos * (sizeof(T) + 2 * sizeof(int)) + sizeof(T) + sizeof(int), SEEK_SET);
	std::fwrite(&next, sizeof(int), 1, fl);
};

template <typename T>
void FileLinkedList<T>::writeCtAndFF() const
{
	int free = ff.peek();
	std::fseek(fl, 0, SEEK_SET);
	std::fwrite(&ct, sizeof(int), 1, fl);
	std::fwrite(&free, sizeof(int), 1, fl);
};

template <typename T>
void FileLinkedList<T>::readData(int pos, const T &data) const
{
	std::fseek(fl, 2 * sizeof(int) + pos * (sizeof(T) + 2 * sizeof(int)), SEEK_SET);
	std::fread(&data, sizeof(T), 1, fl);
};

template <typename T>
int FileLinkedList<T>::readNext(int pos) const
{
	int next;
	std::fseek(fl, 2 * sizeof(int) + pos * (sizeof(T) + 2 * sizeof(int)) + sizeof(T) + sizeof(int), SEEK_SET);
	std::fread(&next, sizeof(int), 1, fl);
	return next;
};

template <typename T>
int FileLinkedList<T>::readPrev(int pos) const
{
	int prev;
	std::fseek(fl, 2 * sizeof(int) + pos * (sizeof(T) + 2 * sizeof(int)) + sizeof(T), SEEK_SET);
	std::fread(&prev, sizeof(int), 1, fl);
	return prev;
};
