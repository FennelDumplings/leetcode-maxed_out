// prob454: 4Sum II

/*
 * Given four lists A, B, C, D of integer values, compute how many tuples (i, j, k, l) there are such that A[i] + B[j] + C[k] + D[l] is zero.
 * To make problem a bit easier, all A, B, C, D have same length of N where 0 ≤ N ≤ 500. All integers are in the range of -228 to 228 - 1
 * and the result is guaranteed to be at most 231 - 1.
 */

/*
 * Example:
 * Input:
 * A = [ 1, 2 ]
 * B = [-2,-1]
 * C = [-1, 2]
 * D = [ 0, 2 ]
 * Output:
 * 2
 * Explanation:
 * The two tuples are:
 * 1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
 * 2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0
 */

#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// TLE
class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        int na = A.size(), nb = B.size(), nc = C.size(), nd = D.size();
        if(na == 0 || nb == 0 || nc == 0 || nd == 0)
            return 0;
        unordered_map<int, int> mapping;
        for(int i: A) ++mapping[i];
        int result = 0;
        for(int i = 0; i < nb; ++i)
            for(int j = 0; j < nc; ++j)
                for(int k = 0; k < nd; ++k)
                {
                    int gap = 0 - (B[i] + C[j] + D[k]);
                    result += mapping[gap];
                }
        return result;
    }
};


class Solution_2 {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        int na = A.size(), nb = B.size(), nc = C.size(), nd = D.size();
        if(na == 0 || nb == 0 || nc == 0 || nd == 0)
            return 0;
        unordered_map<int, int> mapping;
        for(int i = 0; i < na; ++i)
            for(int j = 0; j < nb; ++j)
                ++mapping[A[i] + B[j]];
        int result = 0;
        for(int k = 0; k < nc; ++k)
            for(int l = 0; l < nd; ++l)
            {
                int gap = 0 - (C[k] + D[l]);
                result += mapping[gap];
            }
        return result;
    }
};
