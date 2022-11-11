#include <vector>
#include <list>
#include <utility>
#include <algorithm>

template<typename K,typename V,typename Hash>
class HashMap {
    Hash hashFunction;
    // Data to store the hash table and the number of elements.
	std::vector<std::list<std::pair<K,V>>> table;
	int ct;

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;


    class const_iterator;


    class iterator {
        // NOTE: These might be different depending on how you store your table.

        decltype(table.begin()) mainIter;
        decltype(table.begin()) mainEnd;
        decltype(table[0].begin()) subIter;
    public:
        friend class const_iterator;


        // NOTE: These might be different depending on how you store your table.

        iterator(const decltype(mainIter) mi,const decltype(mainEnd) me):mainIter(mi),mainEnd(me) {
            if(mainIter!=mainEnd) subIter = mainIter->begin();
            while(mainIter!=mainEnd && subIter == mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
        }
        // NOTE: These might be different depending on how you store your table.

        iterator(const decltype(mainIter) mi,
                const decltype(mainEnd) me,
                const decltype(subIter) si):
                mainIter(mi),mainEnd(me),subIter(si) {}


        bool operator==(const iterator &i) const { return mainIter==i.mainIter && (mainIter==mainEnd || subIter==i.subIter); }
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() { return *subIter; }
        iterator &operator++() {
            ++subIter;
            while(mainIter!=mainEnd && subIter==mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
            return *this;
        }
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };


    class const_iterator {
        // NOTE: These might be different depending on how you store your table.

        decltype(table.cbegin()) mainIter;
        decltype(table.cbegin()) mainEnd;
        decltype(table[0].cbegin()) subIter;
    public:
        // NOTE: These might be different depending on how you store your table.

        const_iterator(const decltype(table.cbegin()) mi,const decltype(table.cbegin()) me):mainIter(mi),mainEnd(me) {
            if(mainIter!=mainEnd) subIter = mainIter->begin();
            while(mainIter!=mainEnd && subIter == mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
        }
        // NOTE: These might be different depending on how you store your table.

        const_iterator(const decltype(table.begin()) mi,
            const decltype(table.begin()) me,
            const decltype(table[0].begin()) si):
                mainIter(mi),mainEnd(me),subIter(si) {}
        // NOTE: These might be different depending on how you store your table.

        const_iterator(const iterator &i):mainIter(i.mainIter),mainEnd(i.mainEnd),subIter(i.subIter) {


        }


        bool operator==(const const_iterator &i) const { return mainIter==i.mainIter && (mainIter==mainEnd || subIter==i.subIter); }
        bool operator!=(const const_iterator &i) const { return !(*this==i); }
        const std::pair<K,V> &operator*() const { return *subIter; }
        const_iterator &operator++() {
            ++subIter;
            while(mainIter!=mainEnd && subIter==mainIter->end()) {
                ++mainIter;
                if(mainIter!=mainEnd) subIter = mainIter->begin();
            }
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };

    HashMap(const Hash &hf) : hashFunction(hf), table(7), ct(0) {};
    //HashMap(const HashMap<K,V,Hash> &that); // Only if needed.
    //HashMap &operator=(const HashMap<K,V,Hash> &that); // Only if needed.
    bool empty() const;
    unsigned int size() const;
    iterator find(const key_type& k);
    const_iterator find(const key_type& k) const;
    int count(const key_type& k) const;
    std::pair<iterator,bool> insert(const value_type& val);

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        // TODO: Put this one here to simplify the templates
    }

    iterator erase(const_iterator position);
    int erase(const key_type& k);
    void clear();
    mapped_type &operator[](const K &key) {
		int hc = hashFunction(key);
		int bin = hc % table.size();
		// use find -> itr
		auto itr = find_if(table[bin].begin(), table[bin].end(),
					[&key](const std::pair<K,V> &p){ return p.first == key; });
		if (itr == table[bin].end()) { // not found
			++ct;
			table[bin].push_back(make_pair(key,V()));
			return table[bin].back().second;
		} else {
			return itr->second;
		}
	};
    bool operator==(const HashMap<K,V,Hash>& rhs) const;
    bool operator!=(const HashMap<K,V,Hash>& rhs) const;
    iterator begin() { return iterator(table.begin(), table.end()); };
    const_iterator begin() const {return const_iterator(table.begin(),table.end()); };
    iterator end() {return iterator(table.end(),table.end()); };
    const_iterator end() const { return const_iterator(table.end(),table.end()); };
    const_iterator cbegin() const { return const_iterator(table.begin(),table.end()); };
    const_iterator cend() const { return const_iterator(table.end(),table.end()); };

private:
    void growTableAndRehash();
};

template <typename K, typename V, typename Hash>
int HashMap<K,V,Hash>::erase(const K& key) {
	int hc = hashFunction(key);
	int bin = hc % table.size();
	// use find -> itr
	auto itr = find_if(table[bin].begin(), table[bin].end(),
				[&key](const std::pair<K,V> &p){ return p.first == key; });
	if (itr == table[bin].end()) { // not found
		return 0;
	} else {
		table[bin].erase(itr);
		--ct;
		return 1;
	}
}

template<typename K, typename V, typename Hash>    
typename HashMap<K,V,Hash>::iterator HashMap<K,V,Hash>::find(const key_type& key) {
	int hc = hashFunction(key);
	int bin = hc % table.size();
	// use find -> itr
	auto itr = find_if(table[bin].begin(), table[bin].end(),
				[&key](const std::pair<K,V> &p){ return p.first == key; });
	if (itr == table[bin].end()) { // not found
		return end();
	} else {
		return iterator(table.begin()+bin,table.end(),itr);
	}
}
