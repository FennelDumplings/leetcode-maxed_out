// Prob15: 3sum

/* Description
 * Given an array nums of n integers, are there elements a, b, c
 * in nums such that a + b + c = 0? Find all unique triplets
 * in the array which gives the sum of zero.
 */

/* Example:
 * Given array nums = [-1, 0, 1, 2, -1, -4],
 * A solution set is:
 * [
 *     [-1, 0, 1],
 *     [-1, -1, 2]
 * ]
 */

// Note:
// The solution set must not contain duplicate triplets.

// Tags

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
// #include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > result;
        if(nums.size() < 3)
        {
            return result;
        }

        // 排序
        sort(nums.begin(), nums.end());

        // 遍历数组
        int prev_num = nums[0];
        for(int i = 0; i < nums.size() - 2; ++i)
        {
            // 若与上一个数重复则跳过
            if(i == 0 || nums[i] != prev_num)
            {
                int target = nums[i];
                int gap = -target;
                int right = nums.size() - 1;
                int left = i + 1;
                vector<vector<int> > _result = _find(nums, left, right, gap);
                for(int j = 0; j < _result.size(); ++j)
                {
                    vector<int> item = {target, _result[j][0], _result[j][1]};
                    result.push_back(item);
                }
                prev_num = nums[i];
            }
        }

        return result;
    }

private:
    vector<vector<int> > _find(const vector<int> &nums, int left, int right, int gap)
    {
        vector<vector<int> > result;
        while(left < right)
        {
            int sum = nums[left] + nums[right];
            if(sum == gap)
            {
                vector<int> item = {nums[left], nums[right]};
                result.push_back(item);
                ++left;
                --right;
                while(left < right && nums[left] == nums[left - 1])
                    ++left;
                while(left < right && nums[right] == nums[right + 1])
                    --right;
            }
            else if(sum < gap)
            {
                ++left;
                while(left < right && nums[left] == nums[left - 1])
                    ++left;
            }
            else
            {
                --right;
                while(left < right && nums[right] == nums[right + 1])
                    --right;
            }
        }
        return result;
    }
};

void unittest()
{
    // C++ 读测试文件
    ifstream fin("test/prob15_test2.txt");
    vector<int> a;
    string line;
    if(fin)
    {
        while(getline(fin, line))
        {
            stringstream ss;
            ss << line;
            if(!ss.eof())
            {
                int n;
                while(ss >> n)
                    a.push_back(n);
            }
        }
    }
    for(auto iter = a.begin(); iter != a.end(); ++iter)
    {
        cout << *iter << endl;
    }

    Solution solution;
    vector<vector<int> > result = solution.threeSum(a);
    for(auto iter = result.begin(); iter != result.end(); ++iter)
    {
        for(int i = 0; i < 3; ++i)
        {
            cout << (*iter)[i] << " ";
        }
        cout << endl;
    }
}

void jsontest()
{

}

int main()
{
    unittest();
}

// tag
// Array
// Two Pointers

/*
 * Two Sum -- Easy
 * 3Sum Closest -- Medium
 * 4Sum -- Medium
 * 3Sum Smaller -- Medium
 */
