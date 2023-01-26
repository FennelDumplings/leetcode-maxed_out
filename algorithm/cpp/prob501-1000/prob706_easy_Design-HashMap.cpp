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
class MyHashMap_2 {
public:
    /** Initialize your data structure here. */
    MyHashMap_2() {
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

#include <list>

class MyHashMap2 {
public:
    /** Initialize your data structure here. */
    MyHashMap2() {
        vec = vector<list<PII>>(N);
    }

    /** value will always be non-negative. */
    void put(int key, int value) {
        int pos = hash(key);
        list<PII>::iterator iter = vec[pos].begin();
        while(iter != vec[pos].end() && iter -> first != key)
            ++iter;
        if(iter == vec[pos].end())
            vec[pos].push_front(PII(key, value));
        else
            iter -> second = value;
    }

    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key) {
        int pos = hash(key);
        list<PII>::iterator iter = vec[pos].begin();
        while(iter != vec[pos].end() && iter -> first != key)
            ++iter;
        if(iter == vec[pos].end())
            return -1;
        return iter -> second;
    }

    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key) {
        int pos = hash(key);
        list<PII>::iterator iter = vec[pos].begin();
        while(iter != vec[pos].end() && iter -> first != key)
            ++iter;
        if(iter != vec[pos].end())
            vec[pos].erase(iter);
    }

private:
    const int N = 20011;
    using PII = pair<int, int>;
    vector<list<PII>> vec;

    int hash(int x)
    {
        return x % N;
    }
};


// ---
const int INF = 1e9;
typedef int hashType;
typedef int valueType;
const valueType VALUENULL = -1;

class CloseHashTable
{
private:
    struct Node
    {
        hashType data;
        valueType item;
        int state;
        // 0: Empty  -1: deleted
        // >0: cnt / active
        Node()
        {
            state = 0;
        }
    };

    Node *arraytable;
    int sizetable;
    int (*key)(const hashType& x); // 将 key 变成一个整数，如果 key 本身是整数直接返回
    const double A = 0.6180339887;

    static int defaultKey(const int &k)
    {
        return k;
    }

    int hash1(const hashType& x) const
    {
        if(key(x) < 0)
            return key(x) % sizetable;
        return (key(x) + INF) % sizetable;
    }

    int hash2(const hashType& x) const
    {
        double d;
        if(key(x) < 0)
            d = (key(x) + INF) * A;
        else
            d = (key(x)) * A;
        return (int)(sizetable * (d - (int)d));
    }

public:
    CloseHashTable(int length=20011, int (*f)(const hashType &x)=defaultKey)
    {
        sizetable = length;
        arraytable = new Node[sizetable];
        key = f;
    }

    ~CloseHashTable()
    {
        delete [] arraytable;
    }

    valueType findx(const hashType& x) const;
    bool insertx(const hashType& x, const valueType& v);
    bool removex(const hashType& x);
    void rehash();
};

valueType CloseHashTable::findx(const hashType &x) const
{
    int initPos = hash2(x);
    int pos = initPos;

    do
    {
        if(arraytable[pos].state == 0)
            return VALUENULL;
        if(arraytable[pos].state > 0 && key(arraytable[pos].data) == key(x))
            return arraytable[pos].item;
        pos = (pos + 1) % sizetable;
    }while(pos != initPos);

    return VALUENULL;
}

bool CloseHashTable::insertx(const hashType& x, const valueType& v)
{
    int initPos = hash2(x);
    int pos = initPos;

    do{
        if(arraytable[pos].state <= 0)
        {
            arraytable[pos].data = x;
            arraytable[pos].item = v;
            arraytable[pos].state = 1;
            return true;
        }
        else if(arraytable[pos].state > 0 && key(arraytable[pos].data) == key(x))
        {
            // 有重映射将用新值覆盖 item 改为将新值插入 items
            arraytable[pos].item = v;
            return true;
        }
        pos = (pos + 1) % sizetable;
    }while(pos != initPos);

    return false;
}

bool CloseHashTable::removex(const hashType &x)
{
    int initPos = hash2(x);
    int pos = initPos;

    do
    {
        if(arraytable[pos].state == 0)
            return false;
        if(arraytable[pos].state > 0 && key(arraytable[pos].data) == key(x))
        {
            // 有重映射改为将节点下的所有 item 删掉，将 arraytable[pos].state 改为 -1 后返回
            arraytable[pos].state = -1;
            return true;
        }
        pos = (pos + 1) % sizetable;
    }while(pos != initPos);

    return false;
}

void CloseHashTable::rehash()
{
    Node *tmp = arraytable;
    arraytable = new Node[sizetable * 2];

    for(int i = 0; i < sizetable; ++i)
    {
        if(tmp[i].state > 0)
        {
            for(int j = 0; i < tmp[j].state; ++j)
                insertx(tmp[i].data, tmp[i].item);
        }
    }
    sizetable *= 2;

    delete [] tmp;
}


// ------------------

class OpenHashTable
{
private:
    struct Node
    {
        hashType data;
        valueType item;
        Node *next;
        Node(const hashType &x, const valueType& v)
        {
            data = x;
            item = v;
            next = nullptr;
        }
        Node()
        {
            next = nullptr;
        }
    };

    Node **arraytable;
    int sizetable;
    int (*key)(const hashType &x);
    const double A = 0.6180339887;

    static int defaultKey(const int &k)
    {
        return k;
    }

    int hash1(const hashType& x) const
    {
        if(key(x) < 0)
            return (key(x) + INF) % sizetable;
        return key(x) % sizetable;
    }

    int hash2(const hashType& x) const
    {
        double d;
        if(key(x) < 0)
            d = (key(x) + INF) * A;
        else
            d = (key(x)) * A;
        return (int)(sizetable * (d - (int)d));
    }

public:
    OpenHashTable(int length = 20011, int (*f)(const hashType &x) = defaultKey)
    {
        sizetable = length;
        arraytable = new Node*[sizetable];
        key = f;
        for(int i = 0; i < sizetable; ++i)
        {
            arraytable[i] = new Node;
        }
    }

    ~OpenHashTable()
    {
        Node *p,*q;
        for(int i = 0; i < sizetable; ++i)
        {
            p = arraytable[i];
            // 头删
            do
            {
                q = p -> next;
                delete p;
                p = q;
            }while(p != nullptr);
        }
        delete [] arraytable;
    }

    valueType findx(const hashType &x) const
    {
        int pos = hash2(x);
        Node *p = arraytable[pos];
        while(p -> next != nullptr && (p -> next -> data != x))
            p = p -> next;
        if(p -> next != nullptr)
            return p -> next -> item;
        else
            return VALUENULL;
    }

    bool insertx(const hashType& x, const valueType& v)
    {
        int pos = hash2(x);
        Node *p = arraytable[pos] -> next;
        while(p != nullptr && p -> data != x)
            p = p -> next;
        // 没找到就头插
        if(p == nullptr)
        {
            p = new Node(x, v);
            p -> next = arraytable[pos] -> next;
            arraytable[pos] -> next = p;
            return true;
        }
        else
        {
            p -> item = v;
            return true;
        }
        return false;
    }

    bool removex(const hashType &x)
    {
        int pos = hash2(x);
        Node *p = arraytable[pos];
        Node *q;
        while(p -> next != nullptr && p -> next -> data != x)
            p = p -> next;
        if(p -> next == nullptr)
            return false;
        else
        {
            // 如果是无重集合，直接删 p -> next 即可
            q = p -> next;
            p -> next = q -> next;
            delete q;
            return true;
        }
    }
};

class MyHashMap {
public:
    /** Initialize your data structure here. */
    MyHashMap() {
        mapping = new OpenHashTable(N);
    }

    /** value will always be non-negative. */
    void put(int key, int value) {
        mapping -> insertx(key, value);
    }

    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key) {
        return mapping -> findx(key);
    }

    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key) {
        mapping -> removex(key);
    }

private:
    const int N = 20011;
    OpenHashTable *mapping;
};
