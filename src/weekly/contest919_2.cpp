#include <vector>
#include <list>

using namespace std;

class Solution {
public:
    bool isMagic(vector<int>& target) {
        int n = target.size();
        list<int> l;
        for(int i = 1; i <= n; ++i)
            l.push_back(i);
        list<int> t;
        for(int i = 1; i <= n; ++i)
            t.push_back(target[i - 1]);
        // vector<int> cand(n + 1, true); // true 未知，false 不可行
        return solve(l, t);
    }

private:
    bool solve(list<int>& l, list<int>& t)
    {
        list<int> nxt = next(l);
        int max_len = check(nxt, t);
        if(max_len == 0)
            return false;
        for(int len = max_len; len >= 1; --len)
        {
            cout << "----" << endl;
            cout << len << endl;
            if(_solve(nxt, t, len))
                return true;
            cout << "----" << endl;
        }
        return false;
    }

    bool _solve(list<int> l, list<int> t, int len)
    {
        shrink(l, len);
        shrink(t, len);
        return __solve(l, t, len);
    }

    void show(list<int>& l)
    {
        auto it = l.begin();
        while(it != l.end())
            cout << *it++ << " ";
        cout << endl;
    }

    void shrink(list<int>& l, int len)
    {
        for(int i = 1; i <= len; ++i)
            l.erase(l.begin());
    }

    bool __solve(list<int>& l, list<int>& t, int len)
    {
        show(l);
        show(t);
        l = next(l);
        show(l);
        int max_len = check(l, t);
        if((int)l.size() <= len)
        {
            return max_len == (int)l.size();
        }
        if(max_len < len)
            return false;
        shrink(l, len);
        shrink(t, len);
        return _solve(l, t, len);
    }

    int check(list<int>& l, list<int>& t)
    {
        auto it1 = l.begin();
        auto it2 = t.begin();
        int len = 0;
        while(it1 != l.end() && *it1 == *it2)
        {
            ++it1;
            ++it2;
            ++len;
        }
        return len;
    }

    list<int> next(list<int>& l)
    {
        list<int> nxt;
        auto it = l.begin();
        int i = 0;
        while(it != l.end())
        {
            if(i & 1)
            {
                nxt.push_back(*it);
                it = l.erase(it);
            }
            else
                ++it;
            ++i;
        }
        nxt.insert(nxt.end(), l.begin(), l.end());
        return nxt;
    }
};
