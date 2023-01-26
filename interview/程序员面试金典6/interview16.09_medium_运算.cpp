// interview16.09: 运算

/*
 * https://leetcode-cn.com/problems/operations-lcci/
 */

#include <vector>
#include <climits>

using namespace std;

class Operations {
private:
    vector<int> negs, poss; // 存的是[-1, -2, -4...]、[1, 2, 4...]，取反和判断溢出时用

    int neg(int a) {
        if(!a) return 0;

        int result = 0;

        if(a > 0) {
            // 从绝对值最大的部分开始填充
            for(auto p = negs.rbegin(); p != negs.rend(); p++) {
                if(*p + a < 0) continue;

                a += *p;
                result += *p;
            }
        } else {
            for(auto p = poss.rbegin(); p != poss.rend(); p++) {
                if(*p + a > 0) continue;

                a += *p;
                result += *p;
            }
        }
        return result;
    }
public:
    Operations() {
        // 构造poss和negs
        int p = 1, n = -1;
        poss.push_back(p);
        negs.push_back(n);

        for(int i = 0; i < 30; i++) {
            p += p;
            n += n;

            poss.push_back(p);
            negs.push_back(n);
        }
    }

    int minus(int a, int b) {
        return a + neg(b);
    }

    int multiply(int a, int b) {
        if(!a || !b) return 0;
        if(a == 1) return b;        // 这一步是针对b = INT_MIN的情况，防止下一步取neg时溢出
        if(b < 0) return neg(multiply(a, neg(b)));

        int result = a;
        int times = 1;              // times表示当前结果里已经累加了几个a了

        // times < poss[30]是为了防止溢出
        while(times < poss[30] && times + times <= b) {
            result += result;
            times += times;
        }
        result += multiply(a, minus(b, times));

        return result;
    }

    int divide(int a, int b) {
        if(!a) return 0;

        int result = 1;
        // 只写同号的情况，非同号时用neg转化成同号，但是要注意溢出
        if(a > 0) {
            if(b == INT_MIN) return 0;          // 防止下一句取neg的时候溢出
            if(b < 0) return neg(divide(a, neg(b)));
            if(a < b) return 0;

            int acc = b;                        // 不断往acc里填充b，直到acc达到a
            while(acc < poss[30] && a >= acc + acc) {
                result += result;               // result表示已经填充了几个b了
                acc += acc;
            }
            result += divide(minus(a, acc), b);
        } else {
            if(b == 1) return a;                // 防止若a=INT_MIN造成下一句运算时溢出
            if(b > 0) return neg(divide(a, neg(b)));
            if(a > b) return 0;

            int acc = b;
            while(acc >= negs[30] && a <= acc + acc) {
                result += result;
                acc += acc;
            }
            result += divide(minus(a, acc), b);
        }
        return result;
    }
};

