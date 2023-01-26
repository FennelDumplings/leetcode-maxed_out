// prob712: Random Pick with Blacklist

/*
 * https://leetcode-cn.com/problems/random-pick-with-blacklist/
 */

#include <vector>
#include <unordered_map>
#include <random>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution {
public:
    Solution(int N, vector<int>& blacklist) {
        int nB = blacklist.size();
        int n = N - nB;
        dre = std::default_random_engine();
        di = std::uniform_int_distribution<int>(0, n - 1);

        mapping = unordered_map<int, int>();
        unordered_set<int> B(blacklist.begin(), blacklist.end());
        for(int b: blacklist)
        {
            if(b >= n)
                continue;
            --N;
            while(B.count(N) > 0)
                --N;
            mapping[b] = N;
        }
    }

    int pick() {
        int r = di(dre);
        if(mapping.count(r) > 0)
            return mapping[r];
        else
            return r;
    }

private:
    unordered_map<int, int> mapping;
    std::default_random_engine dre;
    std::uniform_int_distribution<int> di;
};
