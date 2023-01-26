// prob986: Interval List Intersections

/*
 * Given two lists of closed intervals, each list of intervals is pairwise disjoint and in sorted order.
 * Return the intersection of these two interval lists.
 * (Formally, a closed interval [a, b] (with a <= b) denotes the set of real numbers x with a <= x <= b.
 * The intersection of two closed intervals is a set of real numbers that is either empty, or can be represented as a closed interval.
 * For example, the intersection of [1, 3] and [2, 4] is [2, 3].)
 */

/*
 * Input: A = [[0,2],[5,10],[13,23],[24,25]], B = [[1,5],[8,12],[15,24],[25,26]]
 * Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
 * Reminder: The inputs and the desired output are lists of Interval objects, and not arrays or lists.
 */

/*
 * Note:
 * 0 <= A.length < 1000
 * 0 <= B.length < 1000
 * 0 <= A[i].start, A[i].end, B[i].start, B[i].end < 10^9
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        if(A.empty()) return A;
        if(B.empty()) return B;
        int na = A.size();
        int nb = B.size();
        int ia = 0, ib = 0;
        vector<int> cur_a, cur_b;
        vector<vector<int> > results;
        while(ia < na && ib < nb) // 必进循环
        {
            cur_a = A[ia], cur_b = B[ib];
            if(cur_a[1] < cur_b[0])
                ++ia;
            else if(cur_a[0] > cur_b[1])
                ++ib;
            else if(cur_a[1] < cur_b[1])
            {
                results.push_back(vector<int>({max(cur_a[0], cur_b[0]), cur_a[1]}));
                ++ia;
            }
            else
            {
                results.push_back(vector<int>({max(cur_a[0], cur_b[0]), cur_b[1]}));
                ++ib;
            }
        }
        return results;
    }
};
