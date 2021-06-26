// prob444: Sequence Reconstruction

/*
 * Check whether the original sequence org can be uniquely reconstructed from the sequences in seqs. The org sequence is a
 * permutation of the integers from 1 to n, with 1 ≤ n ≤ 104. Reconstruction means building a shortest common supersequence of the
 * sequences in seqs (i.e., a shortest sequence so that all sequences in seqs are subsequences of it). Determine whether there is only one
 * sequence that can be reconstructed from seqs and it is the org sequence.
 */

/*
 * Example 1:
 * Input:
 * org: [1,2,3], seqs: [[1,2],[1,3]]
 * Output:
 * false
 * Explanation:
 * [1,2,3] is not the only one sequence that can be reconstructed, because [1,3,2] is also a valid sequence that can be reconstructed.
 * Example 2:
 * Input:
 * org: [1,2,3], seqs: [[1,2]]
 * Output:
 * false
 * Explanation:
 * The reconstructed sequence can only be [1,2].
 * Example 3:
 * Input:
 * org: [1,2,3], seqs: [[1,2],[1,3],[2,3]]
 * Output:
 * true
 * Explanation:
 * The sequences [1,2], [1,3], and [2,3] can uniquely reconstruct the original sequence [1,2,3].
 * Example 4:
 * Input:
 * org: [4,1,5,2,6,3], seqs: [[5,2,6,3],[4,1,5,2]]
 * Output:
 * true
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        if(seqs.empty()) return false;
        int n = org.size();
        vector<vector<int> > g(n + 1);
        vector<int> indegrees(n + 1, -1);
        for(const vector<int> &seq: seqs)
        {
            if(seq.empty()) continue;
            int n_seq = seq.size();
            if(seq[0] <= 0 || seq[0] > n)
                return false;
            if(indegrees[seq[0]] == -1)
                indegrees[seq[0]] = 0;
            if(n_seq == 1) continue;
            for(int i = 1; i < n_seq; ++i)
            {
                if(seq[i] <= 0 || seq[i] > n)
                    return false;
                g[seq[i - 1]].push_back(seq[i]);
                if(indegrees[seq[i]] == -1)
                    indegrees[seq[i]] = 1;
                else
                    ++indegrees[seq[i]];
            }
        }
        queue<int> q;
        for(int i = 1; i <= n; ++i)
        {
            if(indegrees[i] == -1)
                return false;
            if(indegrees[i] == 0)
                q.push(i);
        }
        if(q.size() != 1) return false;
        vector<int> top_sorted;
        while(!q.empty())
        {
            int cur = q.front();
            top_sorted.push_back(cur);
            q.pop();
            for(int son: g[cur])
            {
                --indegrees[son];
                if(indegrees[son] == 0)
                    q.push(son);
            }
            if(q.size() > 1) return false;
        }
        if((int)top_sorted.size() != n)
            return false;
        for(int i = 0; i < n; ++i)
            if(org[i] != top_sorted[i])
                return false;
        return true;
    }
};
