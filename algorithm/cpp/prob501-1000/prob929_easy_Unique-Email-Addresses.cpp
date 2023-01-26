// prob929: Unique Email Addresses

/*
 * Every email consists of a local name and a domain name, separated by the @ sign.
 * For example, in alice@leetcode.com, alice is the local name, and leetcode.com is the domain name.
 * Besides lowercase letters, these emails may contain '.'s or '+'s.
 * If you add periods ('.') between some characters in the local name part of an email address, mail sent there
 * will be forwarded to the same address without dots in the local name.  For example, "alice.z@leetcode.com"
 * and "alicez@leetcode.com" forward to the same email address.  (Note that this rule does not apply for domain names.)
 * If you add a plus ('+') in the local name, everything after the first plus sign will be ignored. This
 * allows certain emails to be filtered, for example m.y+name@email.com will be forwarded to my@email.com.  (Again, this rule does not apply for domain names.)
 * It is possible to use both of these rules at the same time.
 * Given a list of emails, we send one email to each address in the list.  How many different addresses actually receive mails? 
 */

/*
 * Example 1:
 * Input: ["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com","testemail+david@lee.tcode.com"]
 * Output: 2
 * Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com" actually receive mails
 */

/*
 * Note:
 * 1 <= emails[i].length <= 100
 * 1 <= emails.length <= 100
 * Each emails[i] contains exactly one '@' character.
 * All local and domain names are non-empty.
 * Local names do not start with a '+' character.
 */

#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int numUniqueEmails(vector<string>& emails) {
        if(emails.empty()) return 0;
        int n = emails.size();
        unordered_set<string> setting;
        for(int i = 0; i < n; ++i)
        {
            string &email = emails[i];
            // 记录第一个 + 位置
            string email_key;
            int m = email.size();
            int j = 0;
            bool flag = false;
            for(; j < m; ++j)
            {
                if(email[j] == '@') break;
                if(flag) continue;
                if(email[j] == '.') continue;
                if(email[j] == '+')
                {
                    flag = true;
                    continue;
                }
                email_key += email[j];
            }
            email_key += email.substr(j);
            setting.insert(email_key);
        }
        return setting.size();
    }
};
