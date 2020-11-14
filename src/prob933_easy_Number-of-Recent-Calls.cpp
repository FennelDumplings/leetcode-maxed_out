// prob933: Number of Recent Calls

/*
 * https://leetcode-cn.com/problems/number-of-recent-calls/
 */

#include <vector>
#include <queue>

using namespace std;

class RecentCounter {
public:
    RecentCounter() {
        q = queue<int>();
    }

    int ping(int t) {
        q.push(t);
        while(!q.empty() && q.front() < t - 3000)
            q.pop();
        return q.size();
    }

private:
    const int INTERVAL = 3000;
    queue<int> q;
};
