// prob1442: Count Triplets That Can Form Two Arrays of Equal XOR

/*
 * Given an array of integers arr.
 *
 * We want to select three indices i, j and k where (0 <= i < j <= k < arr.length).
 *
 * Let's define a and b as follows:
 *
 * a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
 * b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
 * Note that ^ denotes the bitwise-xor operation.
 *
 * Return the number of triplets (i, j and k) Where a == b.
 */

/*
 * Example 1:
 * Input: arr = [2,3,1,6,7]
 * Output: 4
 * Explanation: The triplets are (0,1,2), (0,2,2), (2,3,4) and (2,4,4)
 * Example 2:
 * Input: arr = [1,1,1,1,1]
 * Output: 10
 * Example 3:
 * Input: arr = [2,3]
 * Output: 0
 * Example 4:
 * Input: arr = [1,3,5,7,9]
 * Output: 3
 * Example 5:
 * Input: arr = [7,11,12,9,5,2,7,17,22]
 * Output: 8
 */

/*
 * Constraints:
 * 1 <= arr.length <= 300
 * 1 <= arr[i] <= 10^8
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    // 前缀异或
    // 枚举所有 (i, j, k)
    // O(N^3)
    int countTriplets(vector<int>& arr) {
        int n = arr.size();
        vector<int> prexor(n + 1);
        for(int i = 1; i <= n; ++i)
            prexor[i] = prexor[i - 1] ^ arr[i - 1];

        int result = 0;
        // [i, .., j, .., k]
        for(int i = 0; i < n - 1; ++i)
            for(int k = i + 1; k < n; ++k)
                for(int j = i + 1; j <= k; ++j)
                {
                    int xor1 = prexor[i] ^ prexor[j];
                    int xor2 = prexor[j] ^ prexor[k + 1];
                    if(xor1 == xor2)
                        ++result;
                }
        return result;
    }
};

// 利用异或的性质
// a = b 即 a^b = 0
// arr[i]^...^arr[j-1]^arr[j]^...^a[k] == 0
// prexor[k+1] - prexor[i] == 0;
class Solution_2 {
public:
    int countTriplets(vector<int>& arr) {
        int n = arr.size();
        vector<int> prexor(n + 1);
        for(int i = 1; i <= n; ++i)
            prexor[i] = prexor[i - 1] ^ arr[i - 1];

        int result = 0;
        // [i, .., j, .., k]
        for(int i = 0; i < n - 1; ++i)
            for(int k = i + 1; k < n; ++k)
            {
                if((prexor[i] ^ prexor[k + 1]) == 0)
                    result += k - i;
            }
        return result;
    }
};

// 用 unordered_map 动态维护已经有的前缀异或
class Solution_3 {
public:
    int countTriplets(vector<int>& arr) {
        int n = arr.size();
        int pre_xor = 0;
        unordered_map<int, vector<int>> mapping; // xor -> idxs
        mapping[0].push_back(-1);
        int result = 0;
        for(int i = 0; i < n; ++i)
        {
            pre_xor = pre_xor ^ arr[i];
            for(int idx: mapping[pre_xor])
                result += i - idx - 1;
            mapping[pre_xor].push_back(i);
        }
        return result;
    }
};


