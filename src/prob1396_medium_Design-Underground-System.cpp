// prob1396: Design Underground System

/*
 * https://leetcode-cn.com/problems/design-underground-system/
 */

#include <unordered_map>

using namespace std;

class UndergroundSystem {
public:
    UndergroundSystem() {
        stat_mapping = unordered_map<string, PII>();
        user_mapping = unordered_map<int, PIS>();
    }

    void checkIn(int id, string stationName, int t) {
        user_mapping[id] = PIS(t, stationName);
    }

    void checkOut(int id, string stationName, int t) {
        int duration = t - user_mapping[id].first;
        string key = user_mapping[id].second + stationName;
        auto it = stat_mapping.find(key);
        if(it != stat_mapping.end())
        {
            ++stat_mapping[key].first;
            stat_mapping[key].second += duration;
        }
        else
            stat_mapping[key] = PII(1, duration);

    }

    double getAverageTime(string startStation, string endStation) {
        string key = startStation + endStation;
        double result = (double)stat_mapping[key].second / stat_mapping[key].first;
        return result;
    }

private:
    using PII = pair<int, int>;
    using PIS = pair<int, string>;
    unordered_map<string, PII> stat_mapping; // startend -> 次数, 时间总和
    unordered_map<int, PIS> user_mapping; // id -> 进站时间，进站站点
};
