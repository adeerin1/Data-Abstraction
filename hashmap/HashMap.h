#include <vector>
#include <list>
#include <utility>
#include <algorithm>

template <typename K, typename V, typename Hash>
class HashMap
{
    Hash hashFunction;
    // Data to store the hash table and the number of elements.
    std::vector<std::list<std::pair<K, V>>> table;
    int ct;

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K, V> value_type;

    class iterator
    {
        // NOTE: These might be different depending on how you store your table.

    public:
        decltype(table.begin()) mainIter;
        decltype(table.begin()) mainEnd;
        decltype(table[0].begin()) subIter;
        friend class const_iterator;

        // NOTE: These might be different depending on how you store your table.

        iterator(const decltype(mainIter) mi, const decltype(mainEnd) me) : mainIter(mi), mainEnd(me)
        {
            if (mainIter != mainEnd)
                subIter = mainIter->begin();
            while (mainIter != mainEnd && subIter == mainIter->end())
            {
                ++mainIter;
                if (mainIter != mainEnd)
                    subIter = mainIter->begin();
            }
        }
        // NOTE: These might be different depending on how you store your table.

        iterator(const decltype(mainIter) mi,
                 const decltype(mainEnd) me,
                 const decltype(subIter) si) : mainIter(mi), mainEnd(me), subIter(si) {}

        bool operator==(const iterator &i) const { return mainIter == i.mainIter && (mainIter == mainEnd || subIter == i.subIter); }
        bool operator!=(const iterator &i) const { return !(*this == i); }
        std::pair<K, V> &operator*() { return *subIter; }
        iterator &operator++()
        {
            ++subIter;
            while (mainIter != mainEnd && subIter == mainIter->end())
            {
                ++mainIter;
                if (mainIter != mainEnd)
                    subIter = mainIter->begin();
            }
            return *this;
        }
        iterator operator++(int)
        {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };

    class const_iterator
    {
        // NOTE: These might be different depending on how you store your table.

    public:
        // NOTE: These might be different depending on how you store your table.
        decltype(table.cbegin()) mainIter;
        decltype(table.cbegin()) mainEnd;
        decltype(table[0].cbegin()) subIter;
        const_iterator(const decltype(table.cbegin()) mi, const decltype(table.cbegin()) me) : mainIter(mi), mainEnd(me)
        {
            if (mainIter != mainEnd)
                subIter = mainIter->begin();
            while (mainIter != mainEnd && subIter == mainIter->end())
            {
                ++mainIter;
                if (mainIter != mainEnd)
                    subIter = mainIter->begin();
            }
        }
        // NOTE: These might be different depending on how you store your table.

        const_iterator(const decltype(table.begin()) mi,
                       const decltype(table.begin()) me,
                       const decltype(table[0].begin()) si) : mainIter(mi), mainEnd(me), subIter(si) {}
        // NOTE: These might be different depending on how you store your table.

        const_iterator(const iterator &i) : mainIter(i.mainIter), mainEnd(i.mainEnd), subIter(i.subIter)
        {
        }

        bool operator==(const const_iterator &i) const { return mainIter == i.mainIter && (mainIter == mainEnd || subIter == i.subIter); }
        bool operator!=(const const_iterator &i) const { return !(*this == i); }
        const std::pair<K, V> &operator*() const { return *subIter; }
        const_iterator &operator++()
        {
            ++subIter;
            while (mainIter != mainEnd && subIter == mainIter->end())
            {
                ++mainIter;
                if (mainIter != mainEnd)
                    subIter = mainIter->begin();
            }
            return *this;
        }
        const_iterator operator++(int)
        {
            const_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
    };

    HashMap(const Hash &hf) : hashFunction(hf), table(7), ct(0){}; // done
    // HashMap(const HashMap<K,V,Hash> &that); // Only if needed.
    // HashMap &operator=(const HashMap<K,V,Hash> &that); // Only if needed.
    bool empty() const // done
    {                  // done
        if (ct == 0)
            return true;
        else
            return false;
    };
    unsigned int size() const { return ct; };               // done
    iterator find(const key_type &k);                       // done
    const_iterator find(const key_type &k) const;           // done
    int count(const key_type &k) const;                     // done
    std::pair<iterator, bool> insert(const value_type &val) // done
    {
        // std::cout << "Inserting:\n";
        if (ct == table.size())
            growTableAndRehash();
        auto key = val.first;
        int hc = hashFunction(key);
        int bin = hc % table.size();
        auto itr = find_if(table[bin].begin(), table[bin].end(),
                           [&key](const std::pair<K, V> &p)
                           { return p.first == key; });
        if (itr == table[bin].end())
        { // not found
            ++ct;
            table[bin].push_back(make_pair(key, val.second));
            return std::make_pair(find(key), true);
        }
        else
        {
            // std::cout << "Key existed\n";
            (*itr).second = val.second;
            return std::make_pair(find(key), false);
        }
    }
    void print() const // done
    {
        std::cout << "Count: " << ct << std::endl;
        int bin = 0;
        for (auto itr = table.cbegin(); itr != table.cend(); ++itr) // table iterator
        {
            std::cout << "Bin: " << bin << std::endl;
            for (auto elm = (*itr).cbegin(); elm != (*itr).cend(); ++elm) // list iterator
            {

                std::cout << "\tKey: " << (*elm).first << " Value: " << (*elm).second << std::endl;
            }
            ++bin;
        }
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) // done
    {
        while (first != last)
        {
            insert(*first);
            ++first;
        }
    }

    iterator erase(const_iterator position) // done
    {
        auto key = (*position).first;
        iterator returnIterator = find(key);
        if (returnIterator == end())
        {
            return returnIterator;
        }
        else
        {
            std::cout << "Erased " << key << ", returniterator = " << (*returnIterator).first << ", " << (*returnIterator).second << std::endl;
            ++returnIterator;
            erase(key);
            return returnIterator;
        }
    };
    int erase(const key_type &k);         // done
    void clear();                         // done
    mapped_type &operator[](const K &key) // done
    {
        if (ct == table.size())
            growTableAndRehash();
        int hc = hashFunction(key);
        int bin = hc % table.size();
        // use find -> itr
        auto itr = find_if(table[bin].begin(), table[bin].end(),
                           [&key](const std::pair<K, V> &p)
                           { return p.first == key; });
        if (itr == table[bin].end())
        { // not found
            ++ct;
            table[bin].push_back(make_pair(key, V()));
            return table[bin].back().second;
        }
        else
        {
            return itr->second;
        }
    };
    bool operator==(const HashMap<K, V, Hash> &rhs) const;                            // done
    bool operator!=(const HashMap<K, V, Hash> &rhs) const { return !(*this == rhs); } // done
    iterator begin() { return iterator(table.begin(), table.end()); };
    const_iterator begin() const { return const_iterator(table.begin(), table.end()); };
    iterator end() { return iterator(table.end(), table.end()); };
    const_iterator end() const { return const_iterator(table.end(), table.end()); };
    const_iterator cbegin() const { return const_iterator(table.begin(), table.end()); };
    const_iterator cend() const { return const_iterator(table.end(), table.end()); };

private:
    void growTableAndRehash()
    {
        //std::cout << "Growing table\n";
        int tempCt = ct;
        std::vector<std::list<std::pair<K, V>>> table2;
        table2 = std::move(table);
        table.resize(table2.size() * 4);
        for (auto tItr = table2.begin(); tItr != table2.end(); ++tItr)
        {
            for (auto lItr = (*tItr).begin(); lItr != (*tItr).end(); ++lItr)
            {
                insert(*lItr);
            }
        }
        ct = tempCt;
    };
};

template <typename K, typename V, typename Hash>
int HashMap<K, V, Hash>::erase(const K &key)
{
    int hc = hashFunction(key);
    int bin = hc % table.size();
    // use find -> itr
    auto itr = find_if(table[bin].begin(), table[bin].end(),
                       [&key](const std::pair<K, V> &p)
                       { return p.first == key; });
    if (itr == table[bin].end())
    { // not found
        return 0;
    }
    else
    {
        table[bin].erase(itr);
        --ct;
        return 1;
    }
}

template <typename K, typename V, typename Hash>
typename HashMap<K, V, Hash>::iterator HashMap<K, V, Hash>::find(const key_type &key)
{
    int hc = hashFunction(key);
    int bin = hc % table.size();
    // use find -> itr
    auto itr = find_if(table[bin].begin(), table[bin].end(),
                       [&key](const std::pair<K, V> &p)
                       { return p.first == key; });
    if (itr == table[bin].end())
    { // not found
        return end();
    }
    else
    {
        return iterator(table.begin() + bin, table.end(), itr);
    }
}

template <typename K, typename V, typename Hash>
typename HashMap<K, V, Hash>::const_iterator HashMap<K, V, Hash>::find(const key_type &key) const
{
    int hc = hashFunction(key);
    int bin = hc % table.size();
    // use find -> itr
    auto itr = find_if(table[bin].begin(), table[bin].end(),
                       [&key](const std::pair<K, V> &p)
                       { return p.first == key; });
    if (itr == table[bin].end())
    { // not found
        return end();
    }
    else
    {
        return iterator(table.begin() + bin, table.end(), itr);
    }
}

template <typename K, typename V, typename Hash>
int HashMap<K, V, Hash>::count(const key_type &k) const
{
    int hc = hashFunction(k);
    int bin = hc % table.size();
    auto itr = find_if(table[bin].begin(), table[bin].end(),
                       [&k](const std::pair<K, V> &p)
                       { return p.first == k; });
    if (itr == table[bin].end())
    { // not found
        return 0;
    }
    else
    {
        return 1;
    }
}

template <typename K, typename V, typename Hash>
void HashMap<K, V, Hash>::clear()
{
    for (auto tItr = table.begin(); tItr != table.end(); ++tItr)
    {
        (*tItr).clear();
    }
    ct = 0;
}

template <typename K, typename V, typename Hash>
bool HashMap<K, V, Hash>::operator==(const HashMap<K, V, Hash> &rhs) const
{
    if (ct != rhs.ct)
    {
        std::cout << "Count fail\n";
        return false;
    }
    else
    {
        for (auto itr = cbegin(); itr != cend(); ++itr)
        {
            auto key = (*itr).first;
            auto value = (*itr).second;
            int hc = rhs.hashFunction(key);
            int bin = hc % rhs.table.size();
            auto ritr = find_if(rhs.table[bin].begin(), rhs.table[bin].end(),
                                [&key](const std::pair<K, V> &p)
                                { return p.first == key; });
            if (ritr == rhs.table[bin].end())
            { // not found
                std::cout << "Key not found fail\n";
                return false;
            }
            else if ((*ritr).second != value) {
                std::cout << "Value not match fail\n";
                return false;
            }
        }
        return true;
    }
}