// prob418: Sentence Screen Fitting

/*
 * Given a rows x cols screen and a sentence represented by a list of non-empty words, find how many times the given sentence can be fitted on the screen.
 * Note:
 * A word cannot be split into two lines.
 * The order of words in the sentence must remain unchanged.
 * Two consecutive words in a line must be separated by a single space.
 * Total words in the sentence won't exceed 100.
 * Length of each word is greater than 0 and won't exceed 10.
 * 1 ≤ rows, cols ≤ 20,000.
 */

/*
 * Example 1:
 * Input:
 * rows = 2, cols = 8, sentence = ["hello", "world"]
 * Output:
 * 1
 * Explanation:
 * hello---
 * world---
 * The character '-' signifies an empty space on the screen.
 * Example 2:
 * Input:
 * rows = 3, cols = 6, sentence = ["a", "bcd", "e"]
 * Output:
 * 2
 * Explanation:
 * a-bcd-
 * e-a---
 * bcd-e-
 * The character '-' signifies an empty space on the screen.
 * Example 3:
 * Input:
 * rows = 4, cols = 5, sentence = ["I", "had", "apple", "pie"]
 * Output:
 * 1
 * Explanation:
 * I-had
 * apple
 * pie-I
 * had--
 * The character '-' signifies an empty space on the screen.
 */

#include <vector>
#include <string>

using namespace std;

// 最朴素的模拟： 逐行，逐词
class Solution {
public:
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        int ans = 0;
        int i = 0;
        int iter = 0; // 当前在 sentence 中的位置
        int N = sentence.size();
        while(i < rows)
        {
            int j = 0;
            while(j < cols)
            {
                int remain = cols - j;
                int nxt_len = sentence[iter].size();
                if(j == 0 && remain < nxt_len)
                    return 0;
                if(nxt_len > remain)
                    break;
                j += nxt_len;
                ++j; // 词跟词之间的空格
                ++iter;
                if(iter == N)
                {
                    ++ans;
                    iter = 0;
                }
            }
            ++i;
        }
        return ans;
    }
};

// 朴素模拟基础上，在每行遇到句子重新开始时，直接求一次 x = (剩余空格数 + 1) / (句子单词总长 + 单词个数)
// 例如剩余 15 空位，2 个词，一个长 2 ，一个长 4，则计算式为 x = (15 + 1) / (2 + 4 + 2) = 2
// 下一个位置为 j + (句子单词总长 + 单词个数) * x - 1
class Solution_2 {
public:
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        int ans = 0;
        int i = 0;
        int iter = 0; // 当前在 sentence 中的位置
        int N = sentence.size();
        int len_s = 0; // 句子单词总长 + 单词个数(每个词末尾一个空格)
        for(const string &w: sentence)
        {
            if((int)w.size() > cols)
                return 0;
            len_s += (w.size()) + 1;
        }
        while(i < rows)
        {
            int j = 0;
            while(j < cols)
            {
                int remain = cols - j;
                if(iter == 0)
                {
                    int x = (remain + 1) / (len_s);
                    if(x > 0)
                    {
                        j += len_s * x;
                        remain = cols - j;
                        ans += x;
                    }
                }
                int nxt_len = sentence[iter].size();
                if(nxt_len > remain)
                    break;
                j += nxt_len;
                ++j; // 词跟词之间的空格
                ++iter;
                if(iter == N)
                {
                    ++ans;
                    iter = 0;
                }
            }
            ++i;
        }
        return ans;
    }
};

// 没行都完整算
// 直接用宽度除以句子加上空格的长度之和，可以快速的得到能装下的个数。
// 难点在于剩下的空格不足以放下一个单词，所以并不是每个位子都是可用的，我们需要记录有效空位的个数。
class Solution_3 {
public:
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        string all = "";
        for (string word : sentence) all += (word + " ");
        int valid = 0, len = all.size();
        for (int i = 0; i < rows; ++i) {
            valid += cols;
            if (all[valid % len] == ' ')
            {
                // 当 all[start%len]==' ' 的时候，此时start应该自增1，因为虽然剩余的位置刚好填满了单词，后面不用再加空格了，但是我们再算有效空位个数的时候还是要加上这个空格的。
                ++valid;
            }
            else
            {
                // 这里我们需要移除不合法的空位
                while (valid > 0 && all[(valid - 1) % len] != ' ')
                {
                    --valid;
                }
            }
        }
        return valid / len;
    }
};



