// prob705: Design HashSet

/*
 * Design a HashSet without using any built-in hash table libraries.
 * To be specific, your design should include these functions:
 * add(value): Insert a value into the HashSet. 
 * contains(value) : Return whether the value exists in the HashSet or not.
 * remove(value): Remove a value in the HashSet. If the value does not exist in the HashSet, do nothing.
 */

/*
 * Example:
 * MyHashSet hashSet = new MyHashSet();
 * hashSet.add(1);        
 * hashSet.add(2);        
 * hashSet.contains(1);    // returns true
 * hashSet.contains(3);    // returns false (not found)
 * hashSet.add(2);          
 * hashSet.contains(2);    // returns true
 * hashSet.remove(2);          
 * hashSet.contains(2);    // returns false (already removed)
 */

/*
 * Note:
 * All values will be in the range of [0, 1000000].
 * The number of operations will be in the range of [1, 10000].
 * Please do not use the built-in HashSet library.
 */

#include <vector>

using namespace std;

// 开放寻址法
class MyHashSet {
public:
    /** Initialize your data structure here. */
    MyHashSet() {
        vec = vector<int>(N, -1);
    }

    void add(int key) {
        int pos = hash(key);
        while(pos < N && vec[pos] >= 0 && vec[pos] != key)
            pos = (pos + 1) % N;
        if(vec[pos] < 0)
            vec[pos] = key;
    }

    void remove(int key) {
        int pos = hash(key);
        while(pos < N && vec[pos] != key && vec[pos] != -1)
            pos = (pos + 1) % N;
        if(vec[pos] == key)
            vec[pos] = -2;
    }

    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        int pos = hash(key);
        while(pos < N && vec[pos] != key && vec[pos] != -1)
            pos = (pos + 1) % N;
        return vec[pos] == key;
    }

private:
    // 20011
    // 为什么定 20011 而不是 20001，原因是
    // 1. 需要是指数
    // 2. 距离 2^N 够远
    // 3. 开成总数据量的 2 ~ 3 倍
    const int N = 20011; // 10000 次操作，若数据是
    vector<int> vec;

    int hash(int x)
    {
        return x % N;
    }
};
