struct Item
{
    int p;
    int c;
    Item(){}
    Item(int p, int c):p(p),c(c){}
};

struct Cmp
{
    bool operator()(const Item& i1, const Item& i2) const
    {
        return i1.p > i2.p;
    }
};

class Solution {
public:
    long long findMaximumElegance(vector<vector<int>>& items, int k) {
        int n = items.size();
        vector<Item> _items(n);
        for(int i = 0; i < n; ++i)
        {
            _items[i].p = items[i][0];
            _items[i].c = items[i][1];
        }
        sort(_items.begin(), _items.end(), Cmp());
        unordered_set<int> setting;
        stack<int> st;
        long long P = 0; // 候选集中的总利润
        for(int i = 0; i < k; ++i)
        {
            P += _items[i].p;
            if(setting.count(_items[i].c) == 0)
            {
                setting.insert(_items[i].c);
            }
            else
            {
                st.push(_items[i].p);
            }
        }
        long long C = setting.size(); // 候选集中的种类数
        long long ans = P + C * C;
        for(int i = k; i < n; ++i)
        {
            if(setting.count(_items[i].c) > 0 or st.empty())
                continue;
            P += _items[i].p - st.top();
            st.pop();
            setting.insert(_items[i].c);
            C = setting.size();
            ans = max(ans, P + C * C);
        }
        return ans;
    }
};
