// prob1206: Design Skiplist

/*
 * https://leetcode-cn.com/problems/design-skiplist/
 */

#include <vector>
#include <random>

using namespace std;

struct SLNode
{
    int key;
    int level;
    vector<SLNode*> forwards;
    SLNode(int k, int l):key(k),level(l)
    {
        forwards = vector<SLNode*>(level);
    }
    SLNode(){}
    ~SLNode()
    {
        for(SLNode *nxt: forwards)
            nxt = nullptr;
    }
};

class MySkiplist {
public:
    MySkiplist(int max_level, double p) {
        MAX_LEVEL = max_level;
        P = p;
        head = new SLNode(-1, MAX_LEVEL);
        int seed = rand();
        dre = std::default_random_engine(seed);
        dr = std::uniform_real_distribution<double>(0.0, 1.0);
    }

    ~MySkiplist()
    {
        SLNode *iter = head;
        while(iter)
        {
            SLNode *tmp = iter;
            iter = (iter -> forwards)[0];
            delete tmp;
            tmp = nullptr;
        }
        head = nullptr;
    }

    bool search(int target) {
        SLNode *iter = head;
        int level = MAX_LEVEL - 1;
        while(level >= 0)
        {
            while((iter -> forwards)[level] && (iter -> forwards)[level] -> key < target)
                iter = (iter -> forwards)[level];
            --level;
        }
        // 此时 iter 为小于 target 的最大的节点
        if(!(iter -> forwards)[0])
            return false;
        iter = (iter -> forwards)[0];
        if(iter -> key == target)
            return true;
        else
            return false;
    }

    void add(int target) {
        SLNode *iter = head;
        vector<SLNode*> update(MAX_LEVEL);
        int level = MAX_LEVEL - 1;
        while(level >= 0)
        {
            while((iter -> forwards)[level] && (iter -> forwards)[level] -> key < target)
                iter = (iter -> forwards)[level];
            update[level] = iter;
            --level;
        }
        // 此时 iter 为小于 target 的最大的节点
        int new_level = get_random_level();
        SLNode *node = new SLNode(target, new_level);
        for(int l = 0; l < new_level; ++l)
        {
            (node -> forwards)[l] = (update[l] -> forwards)[l];
            (update[l] -> forwards)[l] = node;
        }
    }

    bool erase(int target) {
        SLNode *iter = head;
        vector<SLNode*> update(MAX_LEVEL);
        int level = MAX_LEVEL - 1;
        while(level >= 0)
        {
            while((iter -> forwards)[level] && (iter -> forwards)[level] -> key < target)
                iter = (iter -> forwards)[level];
            update[level] = iter;
            --level;
        }
        // 此时 iter 为小于 target 的最大的节点
        if(!(iter -> forwards)[0])
            return false;
        if((iter -> forwards)[0] -> key != target)
            return false;
        int new_level = (iter -> forwards)[0] -> level;
        SLNode *tmp = (iter -> forwards)[0];
        for(int l = 0; l < new_level; ++l)
        {
            (update[l] -> forwards)[l] = (tmp -> forwards)[l];
            (tmp -> forwards)[l] = nullptr;
        }
        delete tmp;
        tmp = nullptr;
        return true;
    }

private:
    SLNode *head;
    int MAX_LEVEL;
    double P;
    std::default_random_engine dre;
    std::uniform_real_distribution<double> dr;

    int get_random_level()
    {
        int level = 1;
        while(dr(dre) < P && level < MAX_LEVEL)
            ++level;
        return level;
    }
};

class Skiplist {
public:
    Skiplist() {
        skiplist = new MySkiplist(15, 0.5);
    }

    bool search(int target) {
        bool ans = skiplist -> search(target);
        return ans;
    }

    void add(int num) {
        skiplist -> add(num);
    }

    bool erase(int num) {
        bool ans = skiplist -> erase(num);
        return ans;
    }

private:
    MySkiplist *skiplist;
};
