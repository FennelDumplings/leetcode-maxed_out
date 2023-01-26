// prob1169: Invalid Transactions

/*
 * https://leetcode-cn.com/problems/invalid-transactions/
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <sstream>

using namespace std;

class Solution {
public:
    vector<string> invalidTransactions(vector<string>& transactions) {
        unordered_map<string, unordered_map<string, map<int, int>>> mapping;
        for(const string& record: transactions)
        {
            int i = 0;
            int j = record.find(',', i);
            string name = record.substr(i, j - i);
            i = j + 1;
            j = record.find(',', i);
            string time = record.substr(i, j - i);
            int t;
            stringstream ss;
            ss << time;
            ss >> t;
            i = j + 1;
            j = record.find(',', i);
            string c = record.substr(i, j - i);
            int amount;
            ss.clear();
            ss << c;
            ss >> amount;
            i = j + 1;
            string city = record.substr(i);

            mapping[name][city][t] = amount;
        }

        vector<string> result;
        for(const string& record: transactions)
        {
            int i = 0;
            int j = record.find(',', i);
            string name = record.substr(i, j - i);
            i = j + 1;
            j = record.find(',', i);
            string time = record.substr(i, j - i);
            int t;
            stringstream ss;
            ss << time;
            ss >> t;
            i = j + 1;
            j = record.find(',', i);
            string c = record.substr(i, j - i);
            int amount;
            ss.clear();
            ss << c;
            ss >> amount;
            i = j + 1;
            string city = record.substr(i);

            if(amount > 1000)
            {
                result.push_back(record);
                continue;
            }
            auto it = mapping.find(name);
            auto it1 = (it -> second).begin();
            while(it1 != (it -> second).end())
            {
                if(it1 -> first == city)
                {
                    ++it1;
                    continue;
                }
                int t1 = t - 60;
                int t2 = t + 60;
                auto it2 = (it1 -> second).lower_bound(t1);
                if(it2 != (it1 -> second).end() && it2 -> first <= t2)
                {
                    result.push_back(record);
                    break;
                }
                ++it1;
            }
        }
        return result;
    }
};
