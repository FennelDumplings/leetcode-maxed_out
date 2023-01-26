// Prob18: 4sum

/* Description
 * 给定一个包含 n 个整数的数组 nums 和一个目标值 target，
 * 判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值
 * 与 target 相等？找出所有满足条件且不重复的四元组。
 */

/* Example:
 * 给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。
 *
 * 满足要求的四元组集合为：
 * [
 *   [-1,  0, 0, 1],
 *   [-2, -1, 1, 2],
 *   [-2,  0, 0, 2]
 * ]
 */

// Note:
// 答案中不可以包含重复的四元组。

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
    vector<vector<int> > fourSum(vector<int>& nums, int target)
    {
        vector<vector<int> > result;
        // 边界判断
        if(nums.size() < 4)
            return result;

        // 排序
        sort(nums.begin(), nums.end());

        int i_prev = nums[0];
        for(size_t i = 0; i < nums.size() - 3; ++i)
        {
            if(i != 0 && nums[i] == i_prev)
                continue;
            int j_prev = nums[i + 1];
            for(size_t j = i + 1; j < nums.size() - 2; ++j)
            {
                if(j != i + 1 && nums[j] == j_prev)
                    continue;
                int anchor = target - nums[i] - nums[j];
                size_t left = j + 1;
                size_t right = nums.size() - 1;
                vector<vector<int> > result_items = _find(nums, left, right, anchor);
                for(auto iter = result_items.begin(); iter != result_items.end(); ++iter)
                {
                    result.push_back({nums[i], nums[j], (*iter)[0], (*iter)[1]});
                }
                j_prev = nums[j];
            }
            i_prev = nums[i];
        }

        return result;
    }

private:
    vector<vector<int> > _find(vector<int>& nums, size_t left, size_t right, int anchor)
    {
        vector<vector<int> > result_items;
        int left_prev = nums[left];
        int right_prev = nums[right];
        while(left < right)
        {
            int sum = nums[left] + nums[right];
            if(sum == anchor)
            {
                result_items.push_back({nums[left], nums[right]});
                while(left < right && nums[left] == left_prev)
                    ++left;
                left_prev = nums[left];
                while(left < right && nums[right] == right_prev)
                    --right;
                right_prev = nums[right];
            }
            else if(sum < anchor)
            {
                while(left < right && nums[left] == left_prev)
                    ++left;
                left_prev = nums[left];
            }
            else
            {
                while(left < right && nums[right] == right_prev)
                    --right;
                right_prev = nums[right];
            }
        }
        return result_items;
    }
};

void unittest()
{
    // C++ 读测试文件
    ifstream fin("test/prob18_test2.txt");
    vector<int> a;
    string line;
    int t;

    if(fin)
    {
        // 目标读取
        getline(fin, line);
        stringstream ss;
        ss << line;
        ss >> t;
        // 数组读取
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
    vector<vector<int> > result = solution.fourSum(a, t);
    for(auto iter = result.begin(); iter != result.end(); ++iter)
    {
        for(int i = 0; i < 4; ++i)
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
