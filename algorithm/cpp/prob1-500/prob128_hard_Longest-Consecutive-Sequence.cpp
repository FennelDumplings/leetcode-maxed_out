// prob128: Longest Consecutive Sequence

/*
 * Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
 * Your algorithm should run in O(n) complexity.
 */

/*
 * Example:
 * Input: [100, 4, 200, 1, 3, 2]
 * Output: 4
 * Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
 */

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <climits>

using namespace std;

// 哈希表做法
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.empty()) return 0;
        unordered_set<int> setting;
        for(int num: nums)
            setting.insert(num);

        int result = 0;
        for(int num: setting)
        {
            if(num != INT_MIN && setting.count(num - 1) > 0)
                continue;
            // 找到了一个序列的最左元素
            int cnt = 1;
            ++num;
            while(setting.count(num) > 0)
            {
                ++cnt;
                ++num;
            }
            result = max(result, cnt);
        }
        return result;
    }
};

// 并查集做法
class UnionFindSet {
public:
    UnionFindSet(const vector<int>& nums)
    {
        int n = nums.size();
        _set_num = n;
        for(int i = 0; i < n; ++i)
        {
            _father[nums[i]] = nums[i];
            _size[nums[i]] = 1;
        }
    }

    ~UnionFindSet(){}

    bool same(int x, int y)
    {
        return _find(x) == _find(y);
    }

    int merge(int x, int y)
    {
        // merge 后返回集合大小
        x = _find(x);
        y = _find(y);
        if(x == y) return _size[x];

        // 此时 x, y 是所在树的根
        if(_rank[x] < _rank[y])
        {
            _father[x] = y;
            _size[y] += _size[x];
            --_set_num;
            return _size[y];
        }
        else
        {
            _father[y] = x;
            _size[x] += _size[y];
            if(_rank[x] == _rank[y])
                ++_rank[x];
            --_set_num;
            return _size[x];
        }
    }

    int count(int x)
    {
        // 返回元素 x 是否在并查集中
        return _father.count(x);
    }

    int set_size(int x)
    {
        return _size[_find(x)];
    }

    int set_num()
    {
        return _set_num;
    }

private:
    unordered_map<int, int> _father;
    unordered_map<int, int> _rank;
    unordered_map<int, int> _size; // 集合级的权
    int _set_num;

    int _find(int x)
    {
        if(_father[x] == x)
            return x;
        else
            return _father[x] = _find(_father[x]); // 路径压缩
    }
};

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.empty()) return 0;
        UnionFindSet unionfindset(nums);

        int result = 1;
        for(int i: nums)
        {
            if(i != INT_MAX && unionfindset.count(i + 1))
                result = max(result, unionfindset.merge(i , i + 1));
        }
        return result;
    }
};
