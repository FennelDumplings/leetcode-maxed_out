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
class MyHashSet1 {
public:
    /** Initialize your data structure here. */
    MyHashSet1() {
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

// -----
const int INF = 1e9;
typedef int hashType;

class CloseHashTable
{
private:
    struct Node
    {
        hashType data;
        int state; // 0: Empty  1: active  2: deleted
        Node()
        {
            state = 0;
        }
    };

    Node *arraytable;
    int sizetable;
    int (*key)(const hashType& x);
    const double A = 0.6180339887;

    static int defaultKey(const int &k)
    {
        return k;
    }

    int hash1(const hashType& x) const
    {
        return (key(x) + INF) % sizetable;
    }

    int hash2(const hashType& x) const
    {
        double d = key(x) * A;
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
        delete[]arraytable;
    }

    bool findx(const hashType &x) const;
    bool insertx(const hashType &x);
    bool removex(const hashType &x);
    void rehash();
};

bool CloseHashTable::findx(const hashType &x) const
{
    int initPos = hash1(x);
    int pos = initPos;

    do
    {
        if(arraytable[pos].state == 0)
            return false;
        if(arraytable[pos].state == 1 && key(arraytable[pos].data) == key(x))
            return true;
        pos = (pos + 1) % sizetable;
    }while(pos != initPos);

    return false;
}

bool CloseHashTable::insertx(const hashType &x)
{
    int initPos = hash1(x);
    int pos = initPos;

    do{
        if(arraytable[pos].state != 1)
        {
            arraytable[pos].data = x;
            arraytable[pos].state = 1;
            return true;
        }
        if(arraytable[pos].state == 1 && key(arraytable[pos].data) == key(x))
            return true;
        pos = (pos + 1) % sizetable;
    }while(pos != initPos);

    return false;
}

bool CloseHashTable::removex(const hashType &x)
{
    int initPos = hash1(x);
    int pos = initPos;

    do
    {
        if(arraytable[pos].state == 0)
            return false;
        if(arraytable[pos].state==1 && key(arraytable[pos].data) == key(x))
        {
            arraytable[pos].state = 2;
            return true;
        }
        pos = (pos + 1) % sizetable;
    }while(pos != initPos);

    return false;
}

void CloseHashTable::rehash()
{
    Node *tmp = arraytable;
    arraytable = new Node[sizetable];

    for(int i = 0; i < sizetable; ++i)
    {
        if(tmp[i].state == 1)
            insertx(tmp[i].data);
    }

    delete [] tmp;
}

class MyHashSet {
public:
    /** Initialize your data structure here. */
    MyHashSet() {
        table = new CloseHashTable(N);
    }

    ~MyHashSet()
    {
        delete table;
        table = nullptr;
    }

    void add(int key) {
        table -> insertx(key);
    }

    void remove(int key) {
        table -> removex(key);
    }

    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        return table -> findx(key);
    }

private:
    const int N = 99991;
    CloseHashTable *table;
};


typedef int hashType;
const int INF = 1e9;

class OpenHashTable
{
private:
    struct Node
    {
        hashType data;
        int cnt;
        Node *next;
        Node(const hashType &x)
        {
            data = x;
            cnt = 1;
            next = nullptr;
        }
        Node()
        {
            cnt = 0;
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

    int findx(const hashType &x) const
    {
        int pos = hash2(x);
        Node *p = arraytable[pos];
        while(p -> next != nullptr && (p -> next -> data != x))
            p = p -> next;
        if(p -> next != nullptr)
            return p -> next -> cnt;
        else
            return 0;
    }

    bool insertx(const hashType &x)
    {
        int pos = hash2(x);
        Node *p = arraytable[pos] -> next;
        while(p != nullptr && p -> data != x)
            p = p -> next;
        // 没找到就头插
        if(p == nullptr)
        {
            p = new Node(x);
            p -> next = arraytable[pos] -> next;
            arraytable[pos] -> next = p;
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
            q = p -> next;
            p -> next = q -> next;
            delete q;
            return true;
        }
    }
};

class MyHashSet {
public:
    /** Initialize your data structure here. */
    MyHashSet() {
        table = new OpenHashTable(N);
    }

    ~MyHashSet()
    {
        delete table;
        table = nullptr;
    }

    void add(int key) {
        table -> insertx(key);
    }

    void remove(int key) {
        table -> removex(key);
    }

    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        return table -> findx(key);
    }

private:
    const int N = 20011;
    OpenHashTable *table;
};
