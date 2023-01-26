// prob381: Insert Delete GetRandom O(1) - Duplicates allowed

/*
 * https://leetcode-cn.com/problems/insert-delete-getrandom-o1-duplicates-allowed/
 */

#include <vector>
#include <random>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class RandomizedCollection {
public:
    RandomizedCollection() {
        data = vector<int>();
        mapping = unordered_map<int, unordered_set<int>>();
        int rand_seed = rand();
        dre = std::default_random_engine(rand_seed);
        dr = std::uniform_real_distribution<double>(0.0, 1.0);
    }

    bool insert(int val) {
        bool has_val = mapping.count(val) == 0;
        int n = data.size();
        mapping[val].insert(n);
        data.push_back(val);
        return has_val;
    }

    bool remove(int val) {
        if(mapping.count(val) == 0)
            return false;
        int idx = *(mapping[val].begin());
        int n = data.size();
        int tail = data[n - 1];
        swap(data[n - 1], data[idx]);
        data.pop_back();
        mapping[val].erase(mapping[val].find(idx));
        if(n - 1 != idx)
        {
            mapping[tail].erase(n - 1);
            mapping[tail].insert(idx);
        }
        if(mapping[val].empty())
            mapping.erase(val);
        return true;
    }

    int getRandom() {
        if(data.empty())
            return -1;
        int n = data.size();
        int random_idx = floor(n * dr(dre));
        return data[random_idx];
    }

private:
    vector<int> data;
    unordered_map<int, unordered_set<int>> mapping;
    std::default_random_engine dre;
    std::uniform_real_distribution<double> dr;
};
