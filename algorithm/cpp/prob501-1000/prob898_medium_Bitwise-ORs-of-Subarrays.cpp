// prob898: Bitwise ORs of Subarrays

/*
 * https://leetcode-cn.com/problems/bitwise-ors-of-subarrays/
 */

#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>

using namespace std;

// std::set_union
// TLE
class Solution {
public:
    int subarrayBitwiseORs(vector<int>& A) {
        if(A.empty()) return 0;
        int n = A.size();
        if(n == 1) return 1;
        // STL 用 std::set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(result));
        // set 必须有序
        vector<int> setting;
        setting.push_back(A[0]); // [0..i] 的各个 set_i 的并集
        set<int> set_prev; // 以 i - 1 结尾的区间的按位或值集合
        set_prev.insert(A[0]);
        vector<int> tmp;
        set<int> set_i; // 以 i 结尾的区间的按位或值集合
        for(int i = 1; i < n; ++i)
        {
            for(int num: set_prev)
                set_i.insert(num | A[i]);
            set_i.insert(A[i]);
            vector<int> vec1(set_i.begin(), set_i.end());
            set_union(vec1.begin(), vec1.end(), setting.begin(), setting.end(), back_inserter(tmp));
            setting.swap(tmp);
            tmp.clear();
            set_prev.swap(set_i);
            set_i.clear();
        }
        return setting.size();
    }
};

// set
class Solution_2 {
public:
    int subarrayBitwiseORs(vector<int>& A) {
        if(A.empty()) return 0;
        int n = A.size();
        if(n == 1) return 1;
        // STL 用 std::set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(result));
        // set 必须有序
        unordered_set<int> setting;
        setting.insert(A[0]); // [0..i] 的各个 set_i 的并集
        unordered_set<int> set_prev; // 以 i - 1 结尾的区间的按位或值集合
        set_prev.insert(A[0]);
        unordered_set<int> set_i; // 以 i 结尾的区间的按位或值集合
        for(int i = 1; i < n; ++i)
        {
            for(int num: set_prev)
                set_i.insert(num | A[i]);
            set_i.insert(A[i]);
            for(int num: set_i)
                setting.insert(num);
            set_prev.swap(set_i);
            set_i.clear();
        }
        return setting.size();
    }
};

// DP
class Solution_3 {
public:
    int subarrayBitwiseORs(vector<int>& A) {
        if(A.empty()) return 0;
        int n = A.size();
        if(n == 1) return 1;
        unordered_set<int> setting;
        for(int i = 0; i < n; ++i)
        {
            setting.insert(A[i]);
            for(int j = i - 1; j >= 0; --j)
            {
                if((A[i] | A[j]) == A[j])
                {
                    // A[i] 为 1 的位置，A[j] 已经为 1
                    break;
                }
                // 保留积累状态
                A[j] |= A[i];
                setting.insert(A[j]);
            }
        }
        return setting.size();
    }
};

