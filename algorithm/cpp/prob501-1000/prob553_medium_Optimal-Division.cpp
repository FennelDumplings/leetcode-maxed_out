#include <string>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    string optimalDivision(vector<int>& nums) {
        int n = nums.size();
        if(n == 1)
        {
            return to_string(nums[0]);
        }
        string cur;
        stack<double> st;
        string result;
        double max_computed_result = 0.0;
        generate(nums, 0, cur, st, max_computed_result, result);
        return result;
    }

private:
    void generate(const vector<int>& nums, int i, string cur, stack<double> st, double& max_computed_result, string& result)
    {
        int n = nums.size();
        if(i == n - 1)
        {
            // 最后一个元素
            // 不可能有左括号
            // 此前有多少个左括号(st内元素个数-1)，需要全部结算(有多少左括号，补多少右括号)
            // 直接更新 cur 和 computed_result，然后结果比较，最后返回
            cur += to_string(nums[i]);
            double tmp = nums[i];
            while(st.size() > 1)
            {
                cur += ")";
                tmp = st.top() / tmp;
                st.pop();
            }
            double computed_result = st.top() / tmp;
            if(computed_result > max_computed_result)
            {
                max_computed_result = computed_result;
                result = cur;
            }
        }
        else if(i == 0)
        {
            // 第一个元素
            // 不可能有左括号，也不可能有右括号
            // 直接更新 cur 和 st，然后递归处理 i + 1，最后返回
            cur += to_string(nums[i]);
            cur += '/';
            st.push(nums[i]);
            generate(nums, i + 1, cur, st, max_computed_result, result);
        }
        else
        {
            // 中间部分 a[1..n-2]，
            // 可能有左括号
            // 如果添加左括号，则没有右括号
            // 如果不添加左括号，则可能有若干个右括号(结算此前的左括号)
            //     假设此前有 k 个左括号(st内的元素个数-1)，那么结算个数可能 0,1,...,k
            // 分类讨论

            // 添加左括号
            cur += "(";
            cur += to_string(nums[i]);
            cur += "/";
            st.push(nums[i]);
            generate(nums, i + 1, cur, st, max_computed_result, result);
            st.pop();
            while(cur.back() != '(')
                cur.pop_back();
            cur.pop_back();

            // 不添加左括号
            cur += to_string(nums[i]);
            // 不加右括号
            cur += "/";
            double tmp = st.top() / nums[i];
            st.pop();
            st.push(tmp);
            generate(nums, i + 1, cur, st, max_computed_result, result);
            cur.pop_back();
            // 添加右括号
            while(st.size() > 1)
            {
                cur += ")";
                cur += "/";
                double tmp = st.top();
                st.pop();
                tmp = st.top() / tmp;
                st.pop();
                st.push(tmp);
                generate(nums, i + 1, cur, st, max_computed_result, result);
                cur.pop_back();
            }
        }
    }
};
