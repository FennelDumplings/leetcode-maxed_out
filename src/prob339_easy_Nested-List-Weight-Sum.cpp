// prob339: Nested List Weight Sum

/*
 * https://leetcode-cn.com/problems/nested-list-weight-sum/
 */

#include <vector>

using namespace std;

class NestedInteger {
  public:
    // Constructor initializes an empty nested list.
    NestedInteger();

    // Constructor initializes a single integer.
    NestedInteger(int value);

    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Set this NestedInteger to hold a single integer.
    void setInteger(int value);

    // Set this NestedInteger to hold a nested list and adds a nested integer to it.
    void add(const NestedInteger &ni);

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};

class Solution {
public:
    int depthSum(vector<NestedInteger>& nestedList) {
        return _depthSum(nestedList, 1);
    }

private:
    int _depthSum(const vector<NestedInteger>& subnestedList, int deep)
    {
        int n = subnestedList.size();
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            NestedInteger cur = subnestedList[i];
            if(cur.isInteger())
                ans += deep * cur.getInteger();
            else
            {
                ans += _depthSum(cur.getList(), deep + 1);
            }
        }
        return ans;
    }
};
