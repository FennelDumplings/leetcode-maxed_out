// prob1472: Design Browser History

/*
 * https://leetcode-cn.com/problems/design-browser-history/
 */

#include <string>
#include <vector>

using namespace std;

class BrowserHistory {
public:
    BrowserHistory(string homepage) {
        cache = vector<string>({homepage});
        pos = 0;
        max_pos = pos;
    }

    void visit(string url) {
        cache.erase(cache.begin() + pos + 1, cache.end());
        cache.push_back(url);
        ++pos;
        max_pos = pos;
    }

    string back(int steps) {
        if(pos - steps >= 0)
            pos -= steps;
        else
            pos = 0;
        return cache[pos];
    }

    string forward(int steps) {
        if(pos + steps <= max_pos)
            pos += steps;
        else
            pos = max_pos;
        return cache[pos];
    }

private:
    vector<string> cache;
    int pos;
    int max_pos;
};
