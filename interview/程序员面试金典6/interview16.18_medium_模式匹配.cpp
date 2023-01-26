// interview16.08: 模式匹配

/*
 * 你有两个字符串，即pattern和value。 pattern字符串由字母"a"和"b"组成，用于描述字符串中的模式。例如，字符串"catcatgocatgo"匹配模式"aabab"（其中"cat"是"a"，"go"是"b"），该字符串也匹配像"a"、"ab"和"b"这样的模式。但需注意"a"和"b"不能同时表示相同的字符串。编写一个方法判断value字符串是否匹配pattern字符串。
 */

/*
 * 示例 1：
 * 输入： pattern = "abba", value = "dogcatcatdog"
 * 输出： true
 * 示例 2：
 * 输入： pattern = "abba", value = "dogcatcatfish"
 * 输出： false
 * 示例 3：
 * 输入： pattern = "aaaa", value = "dogcatcatdog"
 * 输出： false
 * 示例 4：
 * 输入： pattern = "abba", value = "dogdogdogdog"
 * 输出： true
 * 解释： "a"="dogdog",b=""，反之也符合规则
 */

/*
 * 提示：
 * 0 <= len(pattern) <= 1000
 * 0 <= len(value) <= 1000
 * 你可以假设pattern只包含字母"a"和"b"，value仅包含小写字母。
 */

#include <string>

using namespace std;

class Solution {
public:
    bool patternMatching(string pattern, string value) {
        if(value.empty() && pattern.empty()) return true;
        if(pattern.empty()) return false;
        int m = pattern.size(), n = value.size();
        int na = 0;
        for(char ch: pattern)
            if(ch == 'a')
                ++na;
        int nb = m - na;
        if(value.empty())
        {
            if(na == 0 || nb == 0)
                return true;
            return false;
        }
        if(nb == 0)
        {
            int lb = 0;
            if(n % na != 0)
                return false;
            int la = n / na;
            return check(pattern, value, la, lb);
        }
        if(na == 0)
        {
            int la = 0;
            if(n % nb != 0)
                return false;
            int lb = n / nb;
            return check(pattern, value, la, lb);
        }
        // na * la + (m - na) * lb = n
        for(int la = 0; (n - na * la) / nb >= 0; ++la)
        {
            if((n - na * la) % nb != 0) continue;
            int lb = (n - na * la) / (m - na);
            if(check(pattern, value, la, lb))
                return true;
        }
        return false;
    }

private:
    bool check(const string& pattern, const string& value, int la, int lb)
    {
        int m = pattern.size();
        int pos = 0; // 枚举 pattern 到 i 位置时，value 中的对应位置
        string sa = "#", sb = "#";
        bool matched = true;
        for(int i = 0; i < m; ++i)
        {
            if(pattern[i] == 'a')
            {
                string sub_str = value.substr(pos, la);
                if(sa == "#")
                {
                    sa = sub_str;
                    if(sa == sb)
                        return false;
                }
                else
                {
                    if(sa != sub_str)
                    {
                        matched = false;
                        break;
                    }
                }
                pos += la;
            }
            else
            {
                string sub_str = value.substr(pos, lb);
                if(sb == "#")
                {
                    sb = sub_str;
                    if(sa == sb)
                        return false;
                }
                else
                {
                    if(sb != sub_str)
                    {
                        matched = false;
                        break;
                    }
                }
                pos += lb;
            }
        }
        return matched;
    }
};
