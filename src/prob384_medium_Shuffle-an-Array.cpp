// prob384: Shuffle an Array

/*
 * https://leetcode-cn.com/problems/shuffle-an-array/
 */

#include <algorithm>
#include <vector>

using namespace std;

class Solution_2 {
public:
    Solution_2(vector<int>& nums) {
        vec = nums;
    }

    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return vec;
    }

    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        vector<int> result = vec;
        random_shuffle(result.begin(), result.end());
        return result;
    }

private:
    vector<int> vec;
};

#include <random>

class Solution_3 {
public:
    Solution_3(vector<int>& nums) {
        vec = nums;
        int seed = rand();
        std::default_random_engine dre(seed);
        std::uniform_real_distribution<double> dr(0.0, 1.0);
    }

    vector<int> reset() {
        return vec;
    }

    vector<int> shuffle() {
        vector<int> result(vec.begin(), vec.end());
        int n = result.size();
        for(int k = n; k >= 1; --k)
        {
            int random_idx = floor(dr(dre) * k);
            swap(result[random_idx], result[k - 1]);
        }
        return result;
    }

private:
    vector<int> vec;
    std::default_random_engine dre;
    std::uniform_real_distribution<double> dr;
};


class Solution_4 {
public:
    Solution_4(vector<int>& nums) {
        vec = nums;
        int seed = rand();
        std::default_random_engine dre(seed);
        std::uniform_real_distribution<double> dr(0.0, 1.0);
    }

    vector<int> reset() {
        return vec;
    }

    vector<int> shuffle() {
        int n = vec.size();
        vector<int> result(n);
        for(int i = 0; i < n; ++i)
        {
            int random_idx = floor(dr(dre) * (i + 1));
            swap(result[random_idx], result[i]);
            result[random_idx] = vec[i];
        }
        return result;
    }

private:
    vector<int> vec;
    std::default_random_engine dre;
    std::uniform_real_distribution<double> dr;
};


#include <iterator>

class Solution {
public:
    Solution(vector<int>& nums) {
        vec = nums;
        int seed = rand();
        dre = std::default_random_engine(seed);
        dr = std::uniform_real_distribution<double>(0.0, 1.0);
    }

    vector<int> reset() {
        return vec;
    }

    vector<int> shuffle() {
        vector<int> result = vec;
        shuffle(result.begin(), result.end(), dre);
        return result;
    }

private:
    void shuffle(vector<int>::iterator first, vector<int>::iterator last, std::default_random_engine& rand)
    {
        if(first == last) return;
        std::uniform_real_distribution<double> dr(0.0, 1.0);
        for(auto i = first + 1; i != last; ++i)
            iter_swap(i, first + floor(dr(rand) * (i - first + 1)));
    }

    vector<int> vec;
    std::default_random_engine dre;
    std::uniform_real_distribution<double> dr;
};

