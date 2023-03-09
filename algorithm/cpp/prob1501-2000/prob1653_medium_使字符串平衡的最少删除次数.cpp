class Solution {
public:
    int minimumDeletions(string s) {
        int n = s.size();
        if(n < 2)
            return 0;
        // left_b[i] := [0..i-1] 上 b 的个数，left_b[n] = 0
        left_b = vector<int>(n + 1);
        // right_a[i] := [i..n-1] 上 a 的个数，right_a[0] = 0
        right_a = vector<int>(n);
        for(int i = 0; i < n; ++i)
        {

        }
    }
};
