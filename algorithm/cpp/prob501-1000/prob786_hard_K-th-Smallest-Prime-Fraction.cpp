// prob786: K-th Smallest Prime Fraction

/*
 * A sorted list A contains 1, plus some number of primes.  Then, for every p < q in the list, we consider the fraction p/q.
 * What is the K-th smallest fraction considered?  Return your answer as an array of ints, where answer[0] = p and answer[1] = q.
 */

/*
 * Examples:
 * Input: A = [1, 2, 3, 5], K = 3
 * Output: [2, 5]
 * Explanation:
 * The fractions to be considered in sorted order are:
 * 1/5, 1/3, 2/5, 1/2, 3/5, 2/3.
 * The third fraction is 2/5.
 *
 * Input: A = [1, 7], K = 1
 * Output: [1, 7]
 */

/*
 * Note:
 * A will have length between 2 and 2000.
 * Each A[i] will be between 1 and 30000.
 * K will be between 1 and A.length * (A.length - 1) / 2.
 */

#include <vector>
#include <algorithm>

using namespace std;


struct Fraction
{
    int p, q, cnt;
    Fraction(int p, int q, int cnt):p(p),q(q),cnt(cnt){}
};

class Solution {
public:
    // 整体思路：
    // 主体的二分：算法主体通过二分找到一个数，这个数是满足“小于等于该数的fraction有K个”的最小的数
    // 二分的check条件就是对于mid，统计小于等于mid的fraction个数
    // 二分实现找lowerBound：“统计小于等于某个数”也用二分来实现
    // 暴力解法是通过两层遍历平方级别实现，但是其实可以优化，思路就是对于每一行，找到满足条件的下标，然后通过下标直接计算这一行中“小于等于某个数”的个数。类似的优化思路在第668题中也有体现
    // 在这个过程中每次二分时也求出对应的p和q，并且不断找出最接近答案的值，当所有的二分完成时，我们就找到了最终的p和q
    vector<int> kthSmallestPrimeFraction(vector<int>& A, int K) {
        int n = A.size();
        double left = (double)A[0] / A[n - 1];
        double right = 1.0;
        vector<int> result(2, -1);
        while(left < right)
        {
            double mid = (right + left) / 2;
            Fraction fraction = _leq(A, mid); // 小于等于 mid 的分数 p / q 的个数，同时记录最大的 p / q
            result[0] = fraction.p;
            result[1] = fraction.q;
            if(fraction.cnt > K)
                right = mid;
            else if(fraction.cnt < K)
                left = mid;
            else
                break;
        }
        return result;
    }

private:
    Fraction _leq(const vector<int>& A, double mid)
    {
        // 小于等于 mid 的 fraction 有几个
        int cnt = 0, p = -1, q = -1;
        int n = A.size();
        double maxx = 0;
        for(int i = 0; i < n - 1; ++i)
        {
            // p = a[i]
            // [i+1, .., n-1] 中的 q，从右到左首次  p/q > mid 的位置为 idx
            // 即首次 q < p/mid
            // a[i+1..n-1] 为递增序列
            int left = i + 1, right = n - 1;
            while(left < right)
            {
                int mmid = (left + right + 1) / 2;
                if(double(A[i]) / A[mmid] > mid)
                    left = mmid;
                else
                    right = mmid - 1;
            }
            int j = left;
            if(left == n - 1)
            {
                if((double)A[i] / A[n - 1] > mid)
                    j = n - 1;
                else
                    j = n - 2;
            }
            if(left == i + 1)
            {
                if((double)A[i] / A[i + 1] > mid)
                    j = i + 1;
                else
                    j = i;
            }
            if(j == n - 1) continue;
            cnt += (n - 1) - j;
            double frac = (double)A[i] / A[j + 1];
            if(frac > maxx)
            {
                maxx = frac;
                p = A[i];
                q = A[j + 1];
            }
        }
        return Fraction(p, q, cnt);
    }

    Fraction _leq_linear(const vector<int>& A, double mid)
    {
        // 小于等于 mid 的 fraction 有几个
        int cnt = 0, p = -1, q = -1;
        int n = A.size();
        double maxx = 0;
        for(int i = 0; i < n - 1; ++i)
        {
            for(int j = i + 1; j < n; ++j)
            {
                double frac = double(A[i]) / A[j];
                if(frac <= mid)
                {
                    ++cnt;
                    if(frac > maxx)
                    {
                        maxx = frac;
                        p = A[i];
                        q = A[j];
                    }
                }
            }
        }
        return Fraction(p, q, cnt);
    }
};
