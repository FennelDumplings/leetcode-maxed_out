// prob362: Design Hit Counter

/*
 * https://leetcode-cn.com/problems/design-hit-counter/
 */

#include <vector>
#include <list>
#include <queue>

using namespace std;

class HitCounter {
public:
    /** Initialize your data structure here. */
    HitCounter() {

    }

    /** Record a hit.
        @param timestamp - The current timestamp (in seconds granularity). */
    void hit(int timestamp) {
        while(!q.empty() && q.front() <= timestamp - 300)
            q.pop();
        q.push(timestamp);
    }

    /** Return the number of hits in the past 5 minutes.
        @param timestamp - The current timestamp (in seconds granularity). */
    int getHits(int timestamp) {
        while(!q.empty() && q.front() <= timestamp - 300)
            q.pop();
        return q.size();
    }

private:
    queue<int> q;
};
