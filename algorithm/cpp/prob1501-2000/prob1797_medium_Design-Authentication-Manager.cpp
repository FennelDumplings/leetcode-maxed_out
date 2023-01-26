
#include <string>
#include <unordered_map>
#include <set>
#include <iostream>
#include <climits>

using namespace std;

// 双向链表
struct Token
{
    string id;
    int t; // 过期时间
    Token(string id, int t):id(id),t(t){}
    Token(){}
    bool operator==(const Token& token) const
    {
        return id == token.id && t == token.t;
    }
    bool operator!=(const Token& token) const
    {
        return !(*this == token);
    }
};
ostream& operator<<(ostream& out, const Token& token)
{
    out << "id: " << token.id << "; expiredtime: " << token.t << endl;
    return out;
}

typedef Token DLType;
const DLType DLTypeNULL = Token("", 1e9);
const int MAX_LEN = 1e6;

struct DLNode
{
    DLType val;
    DLNode *next;
    DLNode *prev;
    DLNode(){}
    DLNode(DLType x) : val(x), next(nullptr), prev(nullptr) {}
};

class DoubleCircleList
{
private:
    // head 一直指向 dummy
    // tail 在空表时指向 dummy，否则指向 head 的前一个节点
    DLNode *head, *tail;
    int length;
    int capacity;

public:
    DoubleCircleList(int N=MAX_LEN)
    {
        head = new DLNode(DLTypeNULL);
        head -> next = head;
        head -> prev = head;
        tail = head;
        length = 0;
        capacity = N;
    }

    bool removeHead()
    {
        if(isEmpty())
            return false;
        remove(get_head());
        return true;
    }

    bool removeTail()
    {
        if(isEmpty())
            return false;
        remove(get_tail());
        return true;
    }

    DLType getHead() const
    {
        if(isEmpty())
            return DLTypeNULL;
        return get_head() -> val;
    }

    DLType getTail() const
    {
        if(isEmpty())
            return DLTypeNULL;
        return get_tail() -> val;
    }

    DLNode* insertHead(DLType val)
    {
        if(isFull())
            return nullptr;
        return insert(head, val);
    }

    DLNode* insertTail(DLType val)
    {
        if(isFull())
            return nullptr;
        return insert(tail, val);
    }

    DLNode* insert(DLNode *pos, DLType val)
    {
        if(!pos || isFull())
            return nullptr;
        DLNode *cur = new DLNode(val);
        cur -> next = pos -> next;
        cur -> prev = pos;
        pos -> next -> prev = cur;
        pos -> next = cur;
        if(tail == pos)
            tail = cur;
        ++length;
        return cur;
    }

    DLType get(DLNode *pos) const
    {
        if(!pos || is_dummy(pos))
            return DLTypeNULL;
        return pos -> val;
    }

    DLNode* remove(DLNode *pos)
    {
        if(!pos || is_dummy(pos) || isEmpty())
            return nullptr;
        if(tail == pos)
            tail = tail -> prev;
        --length;
        pos -> prev -> next = pos -> next;
        pos -> next -> prev = pos -> prev;
        DLNode *result = pos -> next;
        delete pos;
        pos = nullptr;
        if(isEmpty())
            return nullptr;
        if(is_dummy(result))
            result = result -> next;
        return result;
    }

    bool change(DLNode* pos, DLType val)
    {
        if(!pos || is_dummy(pos))
            return false;
        pos -> val = val;
        return true;
    }

    DLNode* get_next(DLNode *pos) const
    {
        if(isEmpty())
            return nullptr;
        if(is_tail(pos))
            return get_head();
        return pos -> next;
    }

    DLNode* get_prev(DLNode *pos) const
    {
        if(isEmpty())
            return nullptr;
        if(is_head(pos))
            return get_tail();
        return pos -> prev;
    }

    bool is_dummy(DLNode *pos) const
    {
        return pos == head;
    }

    bool is_head(DLNode *pos) const
    {
        return (!isEmpty() && pos == head -> next);
    }

    bool is_tail(DLNode *pos) const
    {
        return (!isEmpty() && pos == tail);
    }

    DLNode* get_tail() const
    {
        if(isEmpty())
            return nullptr;
        return tail;
    }

    DLNode* get_head() const
    {
        if(isEmpty())
            return nullptr;
        return head -> next;
    }


    bool isEmpty() const
    {
        return head == tail;
    }

    int size() const
    {
        return length;
    }

    bool isFull() const
    {
        return length >= capacity;
    }

    void traverse() const
    {
        auto iter = head -> next;
        while(iter != head)
        {
            cout << iter -> val << ", ";
            iter = iter -> next;
        }
        cout << endl;
    }
};

// 哈希映射

const int INF = INT_MAX;
typedef string HashType;
int defaultKey(const HashType &k)
{
    return k.size();
}
const HashType HashTypeNULL = "";
struct ValueType
{
    HashType value;
    DLNode *list_node;
    ValueType(HashType v=HashTypeNULL, DLNode *node=nullptr):value(v),list_node(node){}
    bool operator==(const ValueType& v) const
    {
        return value == v.value && list_node == v.list_node;
    }
    bool operator!=(const ValueType& v) const
    {
        return !(*this == v);
    }
};
const ValueType VALUENULL(HashTypeNULL, nullptr);

int SDBMHash(char *str)
{
    int hash = 0;

    while (*str)
    {
        // equivalent to: hash = 65599 * hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }
    return (hash & 0x7FFFFFFF);
}

int f(const string& str)
{
    return SDBMHash((char*)str.c_str());
}

class CloseHashTable
{
private:
    struct Node
    {
        HashType data;
        ValueType item;
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
    int (*key)(const HashType& x); // 将 key 变成一个整数，如果 key 本身是整数直接返回
    const double A = 0.6180339887;

    int hash1(const HashType& x) const
    {
        if(key(x) < 0)
            return key(x) % sizetable;
        return (key(x) + INF) % sizetable;
    }

    int hash2(const HashType& x) const
    {
        double d;
        if(key(x) < 0)
            d = (key(x) + INF) * A;
        else
            d = (key(x)) * A;
        return (int)(sizetable * (d - (int)d));
    }

public:
    CloseHashTable(int length=20011, int (*f)(const HashType &x)=defaultKey)
    {
        sizetable = length;
        arraytable = new Node[sizetable];
        key = f;
    }

    ~CloseHashTable()
    {
        delete [] arraytable;
    }

    ValueType findx(const HashType& x) const;
    bool insertx(const HashType& x, const ValueType& v);
    bool removex(const HashType& x);
    void rehash();
};

ValueType CloseHashTable::findx(const HashType &x) const
{
    int initPos = hash2(x);
    int pos = initPos;

    do
    {
        if(arraytable[pos].state == 0)
            return VALUENULL;
        if(arraytable[pos].state > 0 && arraytable[pos].data == x)
            return arraytable[pos].item;
        pos = (pos + 1) % sizetable;
    }while(pos != initPos);

    return VALUENULL;
}

bool CloseHashTable::insertx(const HashType& x, const ValueType& v)
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
        else if(arraytable[pos].state > 0 && arraytable[pos].data == x)
        {
            // 有重映射将用新值覆盖 item 改为将新值插入 items
            arraytable[pos].item = v;
            return true;
        }
        pos = (pos + 1) % sizetable;
    }while(pos != initPos);

    return false;
}

bool CloseHashTable::removex(const HashType &x)
{
    int initPos = hash2(x);
    int pos = initPos;

    do
    {
        if(arraytable[pos].state == 0)
            return false;
        if(arraytable[pos].state > 0 && arraytable[pos].data == x)
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
        if(tmp[i].state > 0)
            insertx(tmp[i].data, tmp[i].item);

    sizetable *= 2;
    delete [] tmp;
}

class OrderedDict
{
public:
    OrderedDict()
    {
        linkedlist = DoubleCircleList();
        CloseHashTable mapping(hashtable_capacity, f);
    }

    ~OrderedDict(){}

    void generate(string key, int value, int timeToLive)
    {
        ValueType v = mapping.findx(key);
        if(v != VALUENULL)
        {
            DLNode *node = v.list_node;
            linkedlist.remove(node);
            mapping.removex(key);
        }
        DLNode *node = linkedlist.insertHead(DLType(key, value + timeToLive));
        mapping.insertx(key, ValueType(key, node));
    }

    void renew(string key, int value, int timeToLive)
    {
        ValueType v = mapping.findx(key);
        if(v == VALUENULL || (v.list_node -> val).t <= value)
            return;
        if(v != VALUENULL)
        {
            DLNode *node = v.list_node;
            linkedlist.remove(node);
            mapping.removex(key);
        }
        DLNode *node = linkedlist.insertHead(DLType(key, value + timeToLive));
        mapping.insertx(key, ValueType(key, node));
    }

    int query(int value)
    {
        while(true)
        {
            DLType token = linkedlist.getTail();
            if(token == DLTypeNULL)
                break;
            if(token.t > value)
                break;
            ValueType v = mapping.findx(token.id);
            DLNode *node = v.list_node;
            linkedlist.remove(node);
            mapping.removex(token.id);
        }
        return size();
    }

    int size() const
    {
        return linkedlist.size();
    }

    void traverse() const
    {
        if(linkedlist.isEmpty())
        {
            cout << "Empty" << endl;
            return;
        }
        DLNode *head = linkedlist.get_head();
        DLNode *iter = head;
        do{
            cout << (iter -> val).id << " " << (iter -> val).t << "; ";
            iter = linkedlist.get_next(iter);
        }
        while(iter != head);
        cout << endl;
    }

private:
    const int hashtable_capacity = 99991;
    DoubleCircleList linkedlist;
    CloseHashTable mapping;
};

class AuthenticationManager {
public:
    AuthenticationManager(int timeToLive) {
        this -> timeToLive = timeToLive;
    }

    void generate(string tokenId, int currentTime) {
        ordereddict.generate(tokenId, currentTime, timeToLive);
    }

    void renew(string tokenId, int currentTime) {
        ordereddict.renew(tokenId, currentTime, timeToLive);
    }

    int countUnexpiredTokens(int currentTime) {
        int ans = ordereddict.query(currentTime);
        return ans;
    }

private:
    OrderedDict ordereddict;
    int timeToLive;
};
