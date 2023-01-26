// prob870: Advantage Shuffle

/*
 * https://leetcode-cn.com/problems/advantage-shuffle/
 */

#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    vector<int> advantageCount(vector<int>& A, vector<int>& B) {
        int n = A.size();
        multiset<int> setA;
        for(int a: A)
            setA.insert(a);
        vector<int> result(n);
        for(int i = 0; i < n; ++i)
        {
            int b = B[i];
            // 在 A 中找到大于 b 的最小的 a
            // 如果没有大于 b 的，则取最小的 a
            auto it = setA.upper_bound(b);
            if(it == setA.end())
            {
                result[i] = *setA.begin();
                setA.erase(setA.begin());
            }
            else
            {
                result[i] = *it;
                setA.erase(it);
            }
        }
        return result;
    }
};
