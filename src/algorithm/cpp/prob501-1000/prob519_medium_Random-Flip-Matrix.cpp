// prob519: Random Flip Matrix

/*
 * https://leetcode-cn.com/problems/random-flip-matrix/
 */

#include <vector>
#include <random>
#include <unordered_set>

using namespace std;

class Solution_2 {
public:
    Solution_2(int n_rows, int n_cols) {
        n = n_rows;
        m = n_cols;
        dre = std::default_random_engine();
        fliped = unordered_set<int>();
    }

    vector<int> flip() {
        int max_idx = n * m - fliped.size() - 1;
        std::uniform_int_distribution<int> di(0, max_idx);
        int random_idx = di(dre);
        while(fliped.count(random_idx) > 0)
            random_idx = di(dre);
        fliped.insert(random_idx);
        int x, y;
        idx2xy(random_idx, x, y);
        return {x, y};
    }

    void reset() {
        fliped.clear();
    }

private:
    int n, m;
    unordered_set<int> fliped;
    std::default_random_engine dre;

    void idx2xy(int idx, int& x, int& y)
    {
        x = idx / m;
        y = idx % m;
    }
};

#include <unordered_map>

class Solution {
public:
    Solution(int n_rows, int n_cols) {
        n = n_rows;
        m = n_cols;
        len = n_rows * n_cols;
        dre = std::default_random_engine();
        mapping = unordered_map<int, int>();
    }

    vector<int> flip() {
        std::uniform_int_distribution<int> di(0, len - 1);
        int random_idx = di(dre);
        int x, y;
        if(mapping.count(random_idx) == 0)
            idx2xy(random_idx, x, y);
        else
            idx2xy(mapping[random_idx], x, y);
        if(mapping.count(len - 1) == 0)
            mapping[random_idx] = len - 1;
        else
            mapping[random_idx] = mapping[len - 1];
        --len;
        return {x, y};
    }

    void reset() {
        len = n * m;
        mapping.clear();
    }

private:
    int n, m;
    int len;
    unordered_map<int, int> mapping;

    void idx2xy(int idx, int& x, int& y)
    {
        x = idx / m;
        y = idx % m;
    }
    std::default_random_engine dre;
};
