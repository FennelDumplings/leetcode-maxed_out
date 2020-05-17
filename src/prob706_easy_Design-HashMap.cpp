// prob706: Design HashMap

/*
 * Design a HashMap without using any built-in hash table libraries.
 * To be specific, your design should include these functions:
 * put(key, value) : Insert a (key, value) pair into the HashMap. If the value already exists in the HashMap, update the value.
 * get(key): Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key.
 * remove(key) : Remove the mapping for the value key if this map contains the mapping for the key.
 */

/*
 * Example:
 * MyHashMap hashMap = new MyHashMap();
 * hashMap.put(1, 1);          
 * hashMap.put(2, 2);        
 * hashMap.get(1);            // returns 1
 * hashMap.get(3);            // returns -1 (not found)
 * hashMap.put(2, 1);          // update the existing value
 * hashMap.get(2);            // returns 1
 * hashMap.remove(2);          // remove the mapping for 2
 * hashMap.get(2);            // returns -1 (not found)
 */

/*
 * Note:
 * All keys and values will be in the range of [0, 1000000].
 * The number of operations will be in the range of [1, 10000].
 * Please do not use the built-in HashMap library.
 */

#include <vector>

using namespace std;

// 哈希函数: 取模法
// 哈希冲突: 开放寻址法 -- 线性
class MyHashMap {
public:
    /** Initialize your data structure here. */
    MyHashMap() {
        vec = vector<PII>(N, PII(-1, -1));
    }

    /** value will always be non-negative. */
    void put(int key, int value) {
        int pos = hash(key);
        while(pos < N && vec[pos].first >= 0 && vec[pos].first != key)
            pos = (pos + 1) % N;
        vec[pos] = PII(key, value);
    }

    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key) {
        int pos = hash(key);
        while(pos < N && vec[pos].first != -1 && vec[pos].first != key)
            pos = (pos + 1) % N;
        return vec[pos].second;
    }

    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key) {
        int pos = hash(key);
        while(pos < N && vec[pos].first != -1 && vec[pos].first != key)
            pos = (pos + 1) % N;
        if(vec[pos].first == key)
            vec[pos] = PII(-2, -1);
    }

private:
    const int N = 20011;
    using PII = pair<int, int>;
    vector<PII> vec;

    int hash(int x)
    {
        return x % N;
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
