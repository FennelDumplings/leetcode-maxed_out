// prob1507: Reformat Date

/*
 * https://leetcode-cn.com/problems/reformat-date/
 */

#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string reformatDate(string date) {
        unordered_map<string, string> month_mapping{
            {"Jan", "01"},
            {"Feb", "02"},
            {"Mar", "03"},
            {"Apr", "04"},
            {"May", "05"},
            {"Jun", "06"},
            {"Jul", "07"},
            {"Aug", "08"},
            {"Sep", "09"},
            {"Oct", "10"},
            {"Nov", "11"},
            {"Dec", "12"}
        };
        string year, month, day;
        stringstream ss;
        ss << date;
        ss >> day;
        ss >> month;
        ss >> year;
        string result;
        result.swap(year);
        result += '-';
        result += month_mapping[month];
        result += '-';
        int d;
        ss.clear();
        ss << day;
        ss >> d;
        string d_str = to_string(d);
        if(d_str.size() == 1)
            d_str = '0' + d_str;
        result+= d_str;
        return result;
    }
};
