// 20200621
// 2. 保证文件名唯一

/*
 * 给你一个长度为 n 的字符串数组 names 。你将会在文件系统中创建 n 个文件夹：在第 i 分钟，新建名为 names[i] 的文件夹。
 *
 * 由于两个文件 不能 共享相同的文件名，因此如果新建文件夹使用的文件名已经被占用，系统会以 (k) 的形式为新文件夹的文件名添加后缀，其中 k 是能保证文件名唯一的 最小正整数 。
 *
 * 返回长度为 n 的字符串数组，其中 ans[i] 是创建第 i 个文件夹时系统分配给该文件夹的实际名称。
 */

#include <unordered_map>
#include <vector>
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
