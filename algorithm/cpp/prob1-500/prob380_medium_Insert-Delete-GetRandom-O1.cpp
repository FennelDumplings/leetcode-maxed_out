// prob380: Insert Delete GetRandom O(1)

/*
 * https://leetcode-cn.com/problems/insert-delete-getrandom-o1/
 */

#include <vector>
#include <unordered_map>
#include <random>

using namespace std;

class RandomizedSet {
public:
    RandomizedSet() {
        data = vector<int>();
        mapping = unordered_map<int, int>();
        dre = std::default_random_engine();
        dr = std::uniform_real_distribution<double>(0.0, 1.0);
    }

    bool insert(int val) {
        if(mapping.count(val) != 0)
            return false;
        int n = data.size();
        mapping[val] = n;
        data.push_back(val);
        return true;
    }

    bool remove(int val) {
        if(mapping.count(val) == 0)
            return false;
        int idx = mapping[val];
        int n = data.size();
        int tail = data[n - 1];
        swap(data[idx], data[n - 1]);
        data.pop_back();
        mapping[tail] = idx;
        mapping.erase(val);
        return true;
    }

    int getRandom() {
        if(data.empty())
            return -1;
        int n = data.size();
        // [0..1) -> [0 .. n-1]
        // 0 <= r * n < n
        int random_idx = floor(n * dr(dre));
        return data[random_idx];
    }

private:
    vector<int> data; // idx -> key
    unordered_map<int, int> mapping; // key -> idx
    std::default_random_engine dre;
    std::uniform_real_distribution<double> dr;
};
