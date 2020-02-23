// Prob146 LRU Cache

/* Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.
 *
 * get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
 * put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
 *
 * The cache is initialized with a positive capacity.
 */

/* LRUCache cache = new LRUCache(2); // 2 is capacity
 * cache.put(1, 1);
 * cache.put(2, 2);
 * cache.get(1);       // returns 1
 * cache.put(3, 3);    // evicts key 2
 * cache.get(2);       // returns -1 (not found)
 * cache.put(4, 4);    // evicts key 1
 * cache.get(1);       // returns -1 (not found)
 * cache.get(3);       // returns 3
 * cache.get(4);       // returns 4
 */

#include <unordered_map>
#include <list>

using namespace std;

class LRUCache {
public:
    LRUCache(int cap) {
        capacity = cap;
        count = 0;
    }

    int get(int key) {
        auto it = mapping.find(key);
        if(it == mapping.end())
            return -1;
        else
        {
            auto iter = (it -> second).second;
            linkedlist.erase(iter);
            linkedlist.push_front(key);
            (it -> second).second = linkedlist.begin();
            return (it -> second).first;
        }
    }

    void put(int key, int value) {
        auto it = mapping.find(key);
        if(it == mapping.end())
        {
            if(count == capacity)
            {
                int key_to_be_destroyed = *(linkedlist.rbegin());
                mapping.erase(mapping.find(key_to_be_destroyed));
                linkedlist.pop_back();
                --count;
            }
            linkedlist.push_front(key);
            mapping.insert(pair<int, pair<int, list<int>::iterator>>(key, pair<int, list<int>::iterator>(value, linkedlist.begin())));
            ++count;
        }
        else
        {
            (it -> second).first = value;
            auto iter = (it -> second).second;
            linkedlist.erase(iter);
            linkedlist.push_front(key);
            (it -> second).second = linkedlist.begin();
        }
    }

private:
    int capacity;
    int count;
    unordered_map<int, pair<int, list<int>::iterator>> mapping;
    list<int> linkedlist;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

