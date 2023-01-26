// prob895: Maximum Frequency Stack

/*
 * https://leetcode-cn.com/problems/maximum-frequency-stack/
 */


#include <vector>
#include <list>
#include <unordered_map>
#include <stack>

using namespace std;

class FreqStack_2 {
public:
    FreqStack_2() {
        cnts = vector<list<Bag>>(1);
        stamp = 0;
        st = list<int>();
        mapping = unordered_map<int, list<Bag>::iterator>();
    }

    void push(int x) {
        st.push_back(x);
        list<int>::iterator item_it = --st.end();
        if(mapping.count(x))
        {
            list<Bag>::iterator it = mapping[x];
            int cnt = (it -> items) -> size();
            (it -> items) -> push_front(Item(stamp++, item_it));
            Bag new_item(x, it -> items);
            if((int)cnts.size() == cnt + 1)
                cnts.push_back({});
            cnts[cnt + 1].push_front(new_item);
            cnts[cnt].erase(it);
            mapping[x] = cnts[cnt + 1].begin();
        }
        else
        {
            if((int)cnts.size() == 1)
                cnts.push_back({});
            list<Item> *l = new list<Item>(1, Item(stamp++, item_it));
            cnts[1].push_front(Bag(x, l));
            mapping[x] = cnts[1].begin();
        }
    }

    int pop() {
        int cnt = cnts.size() - 1;
        // 找到待删除元素：删除 st 中最靠近顶的 x
        int x = cnts[cnt].front().x;
        list<int>::iterator item_it = (cnts[cnt].front().items -> front()).it;
        // 创建 new_item 后删除 cnts[cnt].front()
        cnts[cnt].front().items -> pop_front();
        Bag new_item(x, cnts[cnt].front().items);
        cnts[cnt].pop_front();
        if(cnts[cnt].empty())
            cnts.pop_back();
        // 若 cnt -1 >= 1
        // 在 cnts[cnt - 1] 中找到插入 new_item 的位置
        if(cnt >= 2)
        {
            auto it = cnts[cnt - 1].begin();
            while(it != cnts[cnt - 1].end() && (it -> items -> front()).stamp > (new_item.items -> front()).stamp)
                ++it;
            it = cnts[cnt - 1].insert(it, new_item);
            mapping[x] = it;
        }
        else
            mapping.erase(x);
        st.erase(item_it);
        return x;
    }

private:
    using PII = pair<int, int>;

    struct Item
    {
        int stamp;
        list<int>::iterator it;
        Item(int stamp, list<int>::iterator it):stamp(stamp),it(it){}
    };

    struct Bag
    {
        int x;
        list<Item> *items;
        Bag(int x=-1, list<Item>* items=nullptr):x(x),items(items){}
    };

    int stamp;
    list<int> st;
    unordered_map<int, list<Bag>::iterator> mapping;
    vector<list<Bag>> cnts;
};


class FreqStack {
public:
    FreqStack() {
        cnts = vector<stack<int>>(1);
    }

    void push(int x) {
        ++mapping[x];
        int cnt = mapping[x];
        if((int)cnts.size() == cnt)
            cnts.push_back({});
        cnts[cnt].push(x);
    }

    int pop() {
        int cnt = cnts.size() - 1;
        int x = cnts[cnt].top();
        cnts[cnt].pop();
        if(cnts[cnt].empty())
            cnts.pop_back();
        --mapping[x];
        return x;
    }

private:
    vector<stack<int>> cnts;
    unordered_map<int, int> mapping;
};
