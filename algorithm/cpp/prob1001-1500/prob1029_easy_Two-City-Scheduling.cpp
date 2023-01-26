// prob1029: Two City Scheduling

/*
 * https://leetcode-cn.com/problems/two-city-scheduling/
 */

#include <vector>
#include <algorithm>

using namespace std;

struct Person
{
    int a, b;
    Person(int a, int b):a(a),b(b){}
};

struct Cmp
{
    bool operator()(const Person& p1, const Person& p2) const
    {
        return (p1.a - p1.b) < (p2.a - p2.b);
    }
};

class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        int n = costs.size();
        vector<Person> persons;
        for(int i = 0; i < n; ++i)
        {
            persons.push_back(Person(costs[i][0], costs[i][1]));
        }
        sort(persons.begin(), persons.end(), Cmp());
        int ans = 0;
        for(int i = 0; i < n / 2; ++i)
            ans += persons[i].a;
        for(int i = n / 2; i < n; ++i)
            ans += persons[i].b;
        return ans;
    }
};
