// prob690: Employee Importance

/*
 * https://leetcode-cn.com/problems/employee-importance/
 */

#include <vector>
#include <unordered_map>

using namespace std;

/*
// Definition for Employee.
*/

class Employee {
public:
    int id;
    int importance;
    vector<int> subordinates;
};

class Solution {
public:
    int getImportance(vector<Employee*> employees, int id) {
        Employee *t = nullptr;
        for(Employee *p: employees)
        {
            mapping[p -> id] = p;
            if(p -> id == id)
                t = p;
        }
        if(!t)
            return 0;
        int ans = 0;
        dfs(t, ans);
        return ans;
    }

private:
    unordered_map<int, Employee*> mapping;

    void dfs(const Employee* const p, int& ans)
    {
        ans += p -> importance;
        for(int id: p -> subordinates)
            dfs(mapping[id], ans);
    }
};
