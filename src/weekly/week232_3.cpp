
#include <vector>
#include <set>
#include <cmath>
#include <queue>

using namespace std;

const double EPS = 1e-9;

struct ClassInfo
{
    int pass;
    int total;
    double delta;
    ClassInfo(int p, int t):pass(p),total(t)
    {
        delta = (total - pass) / (double)total / (total + 1);
    }
};

struct Cmp
{
    bool operator()(const ClassInfo& c1, const ClassInfo& c2) const
    {
        return c1.delta < c2.delta;
    }
};

class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        int n = classes.size();
        multiset<ClassInfo, Cmp> setting;
        priority_queue<ClassInfo, vector<ClassInfo>, Cmp> pq;
        for(const vector<int>& info: classes)
        {
            // setting.insert(ClassInfo(info[0], info[1]));
            pq.push(ClassInfo(info[0], info[1]));
        }
        while(extraStudents > 0)
        {
            // ClassInfo p = *setting.rbegin();
            ClassInfo p = pq.top();
            pq.pop();
            pq.push(ClassInfo(p.pass + 1, p.total + 1));
            // setting.insert(ClassInfo(p.pass + 1, p.total + 1));
            --extraStudents;
        }
        double result = 0.0;
        // for(auto iter = setting.begin(); iter != setting.end(); ++iter)
            // result += double(iter -> pass) / (iter -> total);
        while(!pq.empty())
        {
            result += double(pq.top().pass) / (pq.top().total);
            pq.pop();
        }
        return result / n;
    }
};
