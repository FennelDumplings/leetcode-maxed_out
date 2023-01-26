// prob954: Array of Doubled Pairs

/*
 * https://leetcode-cn.com/problems/array-of-doubled-pairs/
 */

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Cmp
{
    bool operator()(const int& a1, const int& a2) const
    {
        return abs(a1) < abs(a2);
    }
};

class Solution {
public:
    bool canReorderDoubled(vector<int>& A) {
        unordered_map<int, int> mapping;
        for(int a: A) ++mapping[a];
        sort(A.begin(), A.end(), Cmp());
        int n = A.size();
        for(int i = 0; i < n; ++i)
        {
            if(mapping.count(A[i]) == 0)
                continue;
            if(mapping.count(A[i] * 2) == 0)
                return false;
            --mapping[A[i]];
            if(mapping[A[i]] == 0)
                mapping.erase(A[i]);
            --mapping[A[i] * 2];
            if(mapping[A[i] * 2] == 0)
                mapping.erase(A[i] * 2);
        }
        return true;
    }
};
