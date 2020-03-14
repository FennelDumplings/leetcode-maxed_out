// prob68: Text Justification

/*
 * Given an array of words and a width maxWidth, format the text such that each line has exactly maxWidth characters
 * and is fully (left and right) justified.
 * You should pack your words in a greedy approach; that is, pack as many words as you can in each line.
 * Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.
 * Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line
 * do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.
 * For the last line of text, it should be left justified and no extra space is inserted between words.
 */

/*
 * Note:
 * A word is defined as a character sequence consisting of non-space characters only.
 * Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
 * The input array words contains at least one word.
 */

/*
 * Example 1:
 * Input:
 * words = ["This", "is", "an", "example", "of", "text", "justification."]
 * maxWidth = 16
 * Output:
 * [
 *    "This    is    an",
 *    "example  of text",
 *    "justification.  "
 * ]
 * Example 2:
 * Input:
 * words = ["What","must","be","acknowledgment","shall","be"]
 * maxWidth = 16
 * Output:
 * [
 *   "What   must   be",
 *   "acknowledgment  ",
 *   "shall be        "
 * ]
 * Explanation: Note that the last line is "shall be    " instead of "shall     be",
 *              because the last line must be left-justified instead of fully-justified.
 *              Note that the second line is also left-justified becase it contains only one word.
 * Example 3:
 * Input:
 * words = ["Science","is","what","we","understand","well","enough","to","explain",
 *          "to","a","computer.","Art","is","everything","else","we","do"]
 * maxWidth = 20
 * Output:
 * [
 *   "Science  is  what we",
 *   "understand      well",
 *   "enough to explain to",
 *   "a  computer.  Art is",
 *   "everything  else  we",
 *   "do                  "
 * ]
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int n = words.size();
        int left = 0;
        string row_result = "";
        vector<string> result;
        while(left < n)
        {
            row_result.clear();
            int len = words[left].size();
            row_result += words[left];
            int right = left + 1;
            while(right < n && len + 1 + (int)words[right].size() <= maxWidth)
            {
                len += 1 + (int)words[right].size();
                ++right;
            }
            int word_num = right - left;
            int blank_num = maxWidth - (len - (word_num - 1));
            if(right == n || word_num == 1)
            {
                for(int i = left + 1; i < right; ++i)
                {
                    row_result += ' ' + words[i];
                    --blank_num;
                }
                string blank(blank_num, ' ');
                row_result += blank;
                result.push_back(row_result);
                left = right;
                continue;
            }
            // word_num >= 2
            int blank_len = blank_num / (word_num - 1);
            int blank_long = blank_num % (word_num - 1);
            string blank(blank_len, ' ');
            int cnt_long = 0;
            for(int i = left + 1; i < right; ++i)
            {
                if(cnt_long < blank_long)
                {
                    ++cnt_long;
                    row_result += blank + ' ' + words[i];
                }
                else
                    row_result += blank + words[i];
            }
            result.push_back(row_result);
            left = right;
        }
        return result;
    }
};
