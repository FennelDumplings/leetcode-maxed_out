
#include <vector>

using namespace std;

struct Person
{
    int a, s;
    Person(int a, int s):a(a),s(s){}
};

struct Cmp
{
    bool operator()(const Person& p1, const Person& p2) const
    {
        if(p1.a == p2.a)
            return p1.s < p2.s;
        return p1.a < p2.a;
    }
};

class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();
        vector<Person> persons;
        for(int i = 0; i < n; ++i)
        {
            persons.emplace_back(ages[i], scores[i]);
        }
        sort(persons.begin(), persons.end(), Cmp());
        vector<int> dp(n, 0);
        dp[0] = persons[0].s;
        for(int i = 1; i < n; ++i)
        {
            int mx = 0;
            for(int j = 0; j < i; ++j)
            {
                if(persons[j].a == persons[i].a)
                    mx = max(mx, dp[j]);
                else if(persons[j].s < persons[i].s)
                    mx = max(mx, dp[j]);
            }
            dp[i] = mx + persons[i].s;
        }
        int ans = dp[0];
        for(int i = 1; i < n; ++i)
            ans = max(ans, dp[i]);
        return ans;
    }
};
