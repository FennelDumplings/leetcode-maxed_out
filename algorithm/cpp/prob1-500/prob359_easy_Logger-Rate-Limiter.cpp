// prob359: Logger Rate Limiter

/*
 * https://leetcode-cn.com/problems/logger-rate-limiter/
 */

#include <string>
#include <unordered_set>
#include <queue>

using namespace std;

struct Record
{
    string s;
    int t;
    Record(const string& s, int t):s(s),t(t){}
};

class Logger {
public:
    /** Initialize your data structure here. */
    Logger() {
        q = queue<Record>();
        setting = unordered_set<string>();
    }

    /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
        If this method returns false, the message will not be printed.
        The timestamp is in seconds granularity. */
    bool shouldPrintMessage(int timestamp, string message) {
        while(!q.empty() && q.front().t <= timestamp - 10)
        {
            setting.erase(q.front().s);
            q.pop();
        }
        if(setting.count(message) > 0)
            return false;
        setting.insert(message);
        q.push(Record(message, timestamp));
        return true;
    }

private:
    unordered_set<string> setting;
    queue<Record> q;
};
