// prob502: IPO

/*
 * https://leetcode-cn.com/problems/ipo/
 */

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Project
{
    int profit;
    int start;
    Project(int p, int s):profit(p),start(s){}
};

struct Sort_cmp
{
    bool operator()(const Project& p1, const Project& p2) const
    {
        return p1.start < p2.start;
    }
};

struct Heap_cmp
{
    bool operator()(const Project& p1, const Project& p2) const
    {
        return p1.profit < p2.profit;
    }
};

class Solution {
public:
    int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
        int n = Profits.size();
        vector<Project> projects;
        for(int i = 0; i < n; ++i)
            projects.emplace_back(Project(Profits[i], Capital[i]));
        sort(projects.begin(), projects.end(), Sort_cmp());
        priority_queue<Project, vector<Project>, Heap_cmp> pq;
        int iter = 0;
        while(iter < n && projects[iter].start <= W)
            pq.push(projects[iter++]);
        while(k > 0 && !pq.empty())
        {
            Project choose = pq.top();
            pq.pop();
            int p = choose.profit;
            if(p <= 0)
                return W;
            W += p;
            --k;
            while(iter < n && projects[iter].start <= W)
                pq.push(projects[iter++]);
        }
        return W;
    }
};
