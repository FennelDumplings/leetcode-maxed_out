// prob1152: Analyze User Website Visit Pattern

/*
 * We are given some website visits: the user with name username[i] visited the website website[i] at time timestamp[i].
 * A 3-sequence is a list of websites of length 3 sorted in ascending order by the time of their visits.  (The websites in a 3-sequence are not necessarily distinct.)
 * Find the 3-sequence visited by the largest number of users. If there is more than one solution, return the lexicographically smallest such 3-sequence
 */

/*
 * Example 1:
 *
 * Input: username = ["joe","joe","joe","james","james","james","james","mary","mary","mary"], timestamp = [1,2,3,4,5,6,7,8,9,10], website = ["home","about","career","home","cart","maps","home","home","about","career"]
 * Output: ["home","about","career"]
 * Explanation:
 * The tuples in this example are:
 * ["joe", 1, "home"]
 * ["joe", 2, "about"]
 * ["joe", 3, "career"]
 * ["james", 4, "home"]
 * ["james", 5, "cart"]
 * ["james", 6, "maps"]
 * ["james", 7, "home"]
 * ["mary", 8, "home"]
 * ["mary", 9, "about"]
 * ["mary", 10, "career"]
 * The 3-sequence ("home", "about", "career") was visited at least once by 2 users.
 * The 3-sequence ("home", "cart", "maps") was visited at least once by 1 user.
 * The 3-sequence ("home", "cart", "home") was visited at least once by 1 user.
 * The 3-sequence ("home", "maps", "home") was visited at least once by 1 user.
 * The 3-sequence ("cart", "maps", "home") was visited at least once by 1 user.
 */

/*
 * Note:
 *
 * 3 <= N = username.length = timestamp.length = website.length <= 50
 * 1 <= username[i].length <= 10
 * 0 <= timestamp[i] <= 10^9
 * 1 <= website[i].length <= 10
 * Both username[i] and website[i] contain only lowercase characters.
 * It is guaranteed that there is at least one user who visited at least 3 websites.
 * No user visits two websites at the same time.
 */

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

struct Record
{
    int time;
    string url;
    Record(int time, string url):time(time),url(url){}
};

struct Person
{
    vector<Record> records;
    Person(){}
};

struct Cmp
{
    bool operator()(const Record& r1, const Record& r2)
    {
        return r1.time < r2.time;
    }
};

class Solution {
public:
    vector<string> mostVisitedPattern(vector<string>& username, vector<int>& timestamp, vector<string>& website) {
        int n = username.size();
        unordered_map<string, Person> mapping;
        for(int i = 0; i < n; ++i)
        {
            string &name = username[i];
            if(mapping.find(name) == mapping.end())
                mapping[name] = Person();
            string &url = website[i];
            mapping[name].records.push_back(Record(timestamp[i], url));
        }

        vector<vector<Record>*> records;
        for(auto it = mapping.begin(); it != mapping.end(); ++it)
        {
            sort((it -> second).records.begin(), (it -> second).records.end(), Cmp());
            auto p = &(it -> second).records;
            if(p -> size() < 3) continue;
            records.push_back(p);
        }
        int n_person = records.size();
        vector<int> result_idx(3);
        map<vector<string>, int> stat;
        for(int i_person = 0; i_person < n_person; ++i_person)
        {
            vector<Record>* record = records[i_person];
            int n = record -> size();
            for(int i = 0; i <= n - 3; ++i)
                for(int j = i + 1; j <= n - 2; ++j)
                    for(int k = j + 1; k <= n - 1; ++k)
                    {
                        vector<string> path({(*record)[i].url, (*record)[j].url, (*record)[k].url});
                        int cnt = 1;
                        if(stat[path] != 0)
                            continue;
                        for(int j_person = i_person + 1; j_person < n_person; ++j_person)
                            if(check(*records[j_person], path))
                                ++cnt;
                        stat[path] = cnt;
                    }
        }
        int max_cnt = 0;
        vector<string> result;
        for(auto it = stat.begin(); it != stat.end(); ++it)
        {
            if(it -> second > max_cnt)
            {
                max_cnt = it -> second;
                result = it -> first;
            }
        }
        return result;
    }

private:
    bool check(const vector<Record>& record, const vector<string>& path)
    {
        int n = record.size();
        for(int i = 0; i <= n - 3; ++i)
            for(int j = i + 1; j <= n - 2; ++j)
                for(int k = j + 1; k <= n - 1; ++k)
                {
                    if(record[i].url == path[0] && record[j].url == path[1] && record[k].url == path[2])
                        return true;
                }
        return false;
    }
};

