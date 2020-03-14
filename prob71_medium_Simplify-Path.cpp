// prob71: Simplify Path

/*
 * Given an absolute path for a file (Unix-style), simplify it. Or in other words, convert it to the canonical path.
 * In a UNIX-style file system, a period . refers to the current directory.
 * Furthermore, a double period .. moves the directory up a level.
 * For more information, see: Absolute path vs relative path in Linux/Unix
 * Note that the returned canonical path must always begin with a slash /,
 * and there must be only a single slash / between two directory names.
 * The last directory name (if it exists) must not end with a trailing /.
 * Also, the canonical path must be the shortest string representing the absolute path.
 */

/*
 * Example 1:
 * Input: "/home/"
 * Output: "/home"
 * Explanation: Note that there is no trailing slash after the last directory name.
 * Example 2:
 * Input: "/../"
 * Output: "/"
 * Explanation: Going one level up from the root directory is a no-op, as the root level is the highest level you can go.
 * Example 3:
 * Input: "/home//foo/"
 * Output: "/home/foo"
 * Explanation: In the canonical path, multiple consecutive slashes are replaced by a single one.
 * Example 4:
 * Input: "/a/./b/../../c/"
 * Output: "/c"
 * Example 5:
 * Input: "/a/../../b/../c//.//"
 * Output: "/c"
 * Example 6:
 * Input: "/a//b////c/d//././/.."
 * Output: "/a/b/c"
 */

#include <string>

using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        int n = path.size();
        if(n <= 1) return path;
        string result;
        int iter = n - 1;
        // 处理末尾的 /
        while(iter >= 0 && path[iter] == '/') --iter;
        int cnt = 0; // 记录未匹配的 .. 的个数
        while(iter >= 0)
        {
            // 刚进入循环时，保证 path[iter] 不为 /
            int right = iter;
            if(path[iter] == '.' && path[iter - 1] == '/')
                iter -= 2;
            else if(path[iter] == '.' && path[iter - 1] == '.' && path[iter - 2] == '/') // .. path[iter]=. 且前一位也是 .
            {
                ++cnt;
                iter -= 3;
            }
            else
            {
                while(iter >= 0 && path[iter] != '/') --iter;
                // 处理连续的 /
                if(cnt == 0)
                    result = path.substr(iter, right - iter + 1) + result; // /word 加入结果
                else
                    --cnt;
            }
            while(iter >= 0 && path[iter] == '/') --iter;
            continue;
        }
        if(result.empty()) return "/";
        return result;
    }
};
