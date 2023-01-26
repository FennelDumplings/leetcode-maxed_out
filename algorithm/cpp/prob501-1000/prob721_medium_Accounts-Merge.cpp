// prob721: Accounts Merge

/*
 * Given a list accounts, each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name,
 * and the rest of the elements are emails representing emails of the account.
 * Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some email
 * that is common to both accounts. Note that even if two accounts have the same name, they may belong to different
 * people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.
 * After merging the accounts, return the accounts in the following format: the first element of each account is the name,
 * and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.
 */

/*
 * Example 1:
 * Input:
 * accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnnybravo@mail.com"], ["John", "johnsmith@mail.com", "john_newyork@mail.com"], ["Mary", "mary@mail.com"]]
 * Output: [["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],  ["John", "johnnybravo@mail.com"], ["Mary", "mary@mail.com"]]
 * Explanation:
 * The first and third John's are the same person as they have the common email "johnsmith@mail.com".
 * The second John and Mary are different people as none of their email addresses are used by other accounts.
 * We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'],
 * ['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
 */

/*
 * Note:
 * The length of accounts will be in the range [1, 1000].
 * The length of accounts[i] will be in the range [1, 10].
 * The length of accounts[i][j] will be in the range [1, 30].
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <set>

using namespace std;

class UnionFindSet
{
public:
    UnionFindSet(int N)
    {
        _father = vector<int>(N, -1);
        _rank = vector<int>(N, 1);
        for(int i = 0; i < N; ++i)
            _father[i] = i;
    }

    bool same(int x, int y)
    {
        return find(x) == find(y);
    }

    int find(int x)
    {
        if(_father[x] == x) return x;
        return _father[x] = find(_father[x]);
    }

    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);

        if(x == y) return;
        if(_rank[x] < _rank[y])
            _father[x] = y;
        else
            _father[y] = x;
        if(_rank[x] == _rank[y])
            ++_rank[x];
    }

private:
    vector<int> _father;
    vector<int> _rank;
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int N = accounts.size();
        unordered_map<string, int> mapping;
        UnionFindSet unionfindset(N);
        for(int i = 0; i < N; ++i)
        {
            for(int j = 1; j < (int)accounts[i].size(); ++j)
            {
                auto it = mapping.find(accounts[i][j]);
                if(it == mapping.end())
                    mapping[accounts[i][j]] = i;
                else
                    unionfindset.merge(mapping[accounts[i][j]], i);
            }
        }
        unordered_map<int, set<string> > id_emails;
        for(int i = 0; i < N; ++i)
        {
            int root = unionfindset.find(i);
            for(int j = 1; j < (int)accounts[i].size(); ++j)
                id_emails[root].insert(accounts[i][j]);
        }
        vector<vector<string> > result;
        for(auto it = id_emails.begin(); it != id_emails.end(); ++it)
        {
            int id = it -> first;
            vector<string> item({accounts[id][0]});
            for(const string &email: it -> second)
                item.push_back(email);
            result.push_back(item);
        }
        return result;
    }
};
