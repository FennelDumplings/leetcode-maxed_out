// prob274: H-Index

/*
 * Given an array of citations (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.
 * According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each,
 * and the other N − h papers have no more than h citations each."
 */

/*
 * Example:
 * Input: citations = [3,0,6,1,5]
 * Output: 3
 * Explanation: [3,0,6,1,5] means the researcher has 5 papers in total and each of them had
 *              received 3, 0, 6, 1, 5 citations respectively.
 *              Since the researcher has 3 papers with at least 3 citations each and the remaining
 *              two with no more than 3 citations each, her h-index is 3.
 */

/*
 * Note: If there are several possible values for h, the maximum one is taken as the h-index.
 */

#include <vector>

using namespace std;

class Solution_2 {
public:
    int hIndex(vector<int>& citations) {
        if(citations.empty()) return 0;
        int n = citations.size();
        int left = 0, right = n;
        while(left < right)
        {
            int mid = (left + right + 1) / 2;
            if(_check(citations, mid))
                left = mid;
            else
                right = mid - 1;
        }
        return left;
    }

private:
    bool _check(const vector<int>& citations, int mid)
    {
        int cnt = 0;
        for(int citation: citations)
            if(citation - mid >= 0)
                ++cnt;
        return cnt >= mid;
    }
};

class Solution {
public:
    int hIndex(vector<int>& citations) {
        if(citations.empty()) return 0;
        int n = citations.size();
        vector<int> cnt(n + 1, 0);
        for(int i: citations)
            ++cnt[min(i, n)];
        int k = n;
        for(int s = cnt[n]; k > s; s += cnt[k])
            --k;
        return k;
    }
};
