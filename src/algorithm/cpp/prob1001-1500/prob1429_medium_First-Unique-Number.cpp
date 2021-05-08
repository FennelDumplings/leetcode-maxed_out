// prob1429: First Unique Number

/*
 * https://leetcode-cn.com/problems/first-unique-number/
 */


#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <list>

using namespace std;

class FirstUnique {
public:
    FirstUnique(vector<int>& nums) {
        for(int i: nums)
            add(i);
    }

    int showFirstUnique() {
        if(l.empty())
            return -1;
        return l.front();
    }

    void add(int value) {
        if(cnt2.count(value) > 0)
            return;
        if(cnt1.count(value) == 0)
        {
            l.push_back(value);
            cnt1[value] = --l.end();
        }
        else
        {
            cnt2.insert(value);
            l.erase(cnt1[value]);
            cnt1.erase(value);
        }
    }

private:
    unordered_set<int> cnt2;
    unordered_map<int,list<int>::iterator> cnt1;
    list<int> l;
};
