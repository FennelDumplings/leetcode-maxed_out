// prob528: Random Pick with Weight

/*
 * https://leetcode-cn.com/problems/random-pick-with-weight/
 */

#include <vector>
#include <random>
#include <algorithm>

using namespace std;

class Solution_2 {
public:
    Solution_2(vector<int>& w) {
        int sum = 0;
        for(int i: w) sum += i;
        int n = w.size();
        ranges.assign(n, 0.0);
        int pre_sum = w[0];
        for(int i = 1; i < n; ++i)
        {
            ranges[i] = (double)pre_sum / sum;
            pre_sum += w[i];
        }
        dre = std::default_random_engine();
        dr = std::uniform_real_distribution<double>(0.0, 1.0);
    }

    int pickIndex() {
        double p = dr(dre);
        auto it = --upper_bound(ranges.begin(), ranges.end(), p);
        return it - ranges.begin();
    }

private:
    vector<double> ranges;
    std::default_random_engine dre;
    std::uniform_real_distribution<double> dr;
};

#include <cmath>

class Solution {
public:
    Solution(vector<int>& w) {
        this -> A = w;
        dre = std::default_random_engine();
        dr = std::uniform_real_distribution<double>(0.0, 1.0);
    }

    int pickIndex() {
        int n = (this -> A).size();
        int m = 1;
        int At = -1; // 蓄水池中的样本
        double rt = -1; // 蓄水池中样本 At 只有的随机数
        for(int i = 0; i < n; ++i)
        {
            int Ai = i;
            int wi = (this -> A)[i];
            double ri = log(dr(dre)) / (double)wi;
            if(i < m)
            {
                At = Ai;
                rt = ri;
            }
            else
            {
                if(rt < ri)
                {
                    At = Ai;
                    rt = ri;
                }
            }
        }
        return At;
    }

private:
    vector<int> A;
    std::default_random_engine dre;
    std::uniform_real_distribution<double> dr;
};
