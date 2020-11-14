// prob379: Design Phone Directory

/*
 * https://leetcode-cn.com/problems/design-phone-directory/
 */

#include <list>
#include <vector>

using namespace std;

class PhoneDirectory {
public:
    /** Initialize your data structure here
        @param maxNumbers - The maximum numbers that can be stored in the phone directory. */
    PhoneDirectory(int maxNumbers) {
        state = vector<bool>(maxNumbers, false);
        vector<int> tmp(maxNumbers);
        for(int i = 0; i < maxNumbers; ++i)
            tmp[i] = i;
        valid = list<int>(tmp.begin(), tmp.end());
    }

    /** Provide a number which is not assigned to anyone.
        @return - Return an available number. Return -1 if none is available. */
    int get() {
        if(valid.empty())
            return -1;
        int id = valid.front();
        state[id] = true;
        valid.pop_front();
        return id;
    }

    /** Check if a number is available or not. */
    bool check(int number) {
        return !state[number];
    }

    /** Recycle or release a number. */
    void release(int number) {
        if(!state[number])
            return;
        state[number] = false;
        valid.push_back(number);
    }

private:
    vector<bool> state;
    list<int> valid;
};
