// prob1487: Making File Names Unique

/*
 * https://leetcode-cn.com/problems/making-file-names-unique/
 */

#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> getFolderNames(vector<string>& names) {
        unordered_map<string, int> cnts;
        int n = names.size();
        vector<string> result(n);
        for(int i = 0; i < n; ++i)
        {
            string fold = names[i];
            if(cnts[fold] > 0)
            {
                int k = cnts[fold];
                while(true)
                {
                    string new_fold = fold + '(' + to_string(k) + ')';
                    if(cnts[new_fold] == 0)
                    {
                        result[i] = new_fold;
                        cnts[new_fold] = 1;
                        break;
                    }
                    else
                        ++k;
                }
                cnts[fold] = k + 1;
            }
            else
            {
                result[i] = fold;
                cnts[fold] = 1;
            }
        }
        return result;
    }

private:
    using PSI = pair<string, int>;
};
