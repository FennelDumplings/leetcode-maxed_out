// prob1348: Tweet Counts Per Frequency

/*
 * https://leetcode-cn.com/problems/tweet-counts-per-frequency/
 */

#include <map>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class TweetCounts {
public:
    TweetCounts() {
        mapping = unordered_map<string, map<int, int>>();
    }

    void recordTweet(string tweetName, int time) {
        ++mapping[tweetName][time];
    }

    vector<int> getTweetCountsPerFrequency(string freq, string tweetName, int startTime, int endTime) {
        if(mapping.count(tweetName) == 0)
            return {};
        auto it_left = mapping[tweetName].lower_bound(startTime);
        auto it_right = mapping[tweetName].upper_bound(endTime);
        int interval;
        if(freq == "minute")
            interval = 60;
        else if(freq == "hour")
            interval = 3600;
        else
            interval = 3600 * 24;
        vector<int> result;
        auto it = it_left;
        int time = startTime;
        while(time <= endTime)
        {
            int nxt_time = time + interval;
            result.push_back(0);
            while(it != it_right && it -> first < nxt_time)
            {
                result.back() += it -> second;
                ++it;
            }
            time = nxt_time;
        }
        return result;
    }

private:
    unordered_map<string, map<int, int>> mapping;
};
