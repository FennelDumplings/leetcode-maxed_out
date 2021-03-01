#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
        int n = apples.size();
        map<int, int> mapping; // 腐烂日期 -> 个数
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            auto it = mapping.begin();
            if(!mapping.empty() && mapping.begin() -> first <= i)
                mapping.erase(it);
            if(apples[i] > 0)
                mapping[i + days[i]] += apples[i];
            if(!mapping.empty())
            {
                ++ans;
                --(mapping.begin() -> second);
                if(mapping.begin() -> second == 0)
                    mapping.erase(mapping.begin());
            }
        }
        int iter = n;
        while(!mapping.empty())
        {
            if(mapping.begin() -> first <= iter)
                mapping.erase(mapping.begin());
            if(!mapping.empty())
            {
                ++ans;
                --(mapping.begin() -> second);
                if(mapping.begin() -> second == 0)
                    mapping.erase(mapping.begin());
            }
            ++iter;
        }
        return ans;
    }
};
