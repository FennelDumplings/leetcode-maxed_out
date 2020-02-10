//prob167 Two sum 2 - Input array is sorted

/*
Given an array of integers that is already sorted in ascending order, find two numbers such that
they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target,
where index1 must be less than index2. Please note that your returned answers (both index1 and
index2) are not zero-based.

You may assume that each input would have exactly one solution and you may not use the same
element twice.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
    vector<int> twoSum(vector<int>& numbers, int target)
    {
        //题中假设了每组输入都刚好有一个结果，因此不用考虑numbers中元素个数为1和0的情况
        int n = numbers.size(); //已知n >= 2
        int head = 0;
        int tail = n - 1;
        //vector<int> result(2, 0);
        while(head < tail)
        {
            int sum = numbers[head] + numbers[tail];
            if(sum == target)
            {
                //result[0] = head + 1;
                //result[1] = tail + 1;
                //break;
                return vector<int>{head + 1, tail + 1};
            }
            else if(sum < target)
            {
                ++head;
            }
            else
            {
                --tail;
            }
        }
        return vector<int>{0, 0};
    }
}


int main()
{
    int n;
    cout << "length of sorted array: " << endl;
    cin >> n;
    vector<int> nums(n, 0);
    cout << "Input " << n << " numbers in ascending order: " << endl;
    for(int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }
    for(int i = 0; i < n; ++i)
    {
        cout << nums[i] << " ";
    }
    cout << endl;
    cout << "Input target: " << endl;
    int tar;
    cin >> tar;
    Solution solution;
    vector<int> res = solution.twoSum(nums, tar);
    cout << "result: " << res[0] << ", " << res[1] << endl;
}
