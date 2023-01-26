// interview66: 构建乘积数组

/*
 * https://leetcode-cn.com/problems/gou-jian-cheng-ji-shu-zu-lcof/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> constructArr(vector<int>& a) {
        if(a.empty()) return {};
        int n = a.size();
        vector<int> prefix_product(n + 1, 1), suffix_product(n + 1, 1);
        for(int i = 1; i <= n; ++i)
            prefix_product[i] = prefix_product[i - 1] * a[i - 1];
        for(int i = n - 1; i >= 0; --i)
            suffix_product[i] = suffix_product[i + 1] * a[i];
        vector<int> result(n, 1);
        for(int i = 0; i < n; ++i)
            result[i] = prefix_product[i] * suffix_product[i + 1];
        return result;
    }
};
