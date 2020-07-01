// prob271: Encode and Decode Strings

/*
 * Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.
 * Machine 1 (sender) has the function:
 * string encode(vector<string> strs) {
 *   // ... your code
 *   return encoded_string;
 * }
 * Machine 2 (receiver) has the function:
 * vector<string> decode(string s) {
 *   //... your code
 *   return strs;
 * }
 * So Machine 1 does:
 * string encoded_string = encode(strs);
 * and Machine 2 does:
 * vector<string> strs2 = decode(encoded_string);
 * strs2 in Machine 2 should be the same as strs in Machine 1.
 * Implement the encode and decode methods.
 */

/*
 * Note:
 * The string may contain any possible characters out of 256 valid ascii characters. Your algorithm should be generalized enough to work on any possible characters.
 * Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.
 * Do not rely on any library method such as eval or serialize methods. You should implement your own encode/decode algorithm.
 */

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

// 非 ASCII 分隔符
class Codec {
public:

    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        if(strs.empty()) return "";
        string result;
        char p = (char)256;
        for(const string& str: strs)
            result += str + p;
        return result;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        if(s.empty()) return {};
        vector<string> result;
        int n = s.size();
        int left = 0;
        char p = (char)256;
        while(left < n)
        {
            int right = left;
            while(right < n && s[right] != p)
                ++right;
            result.push_back(s.substr(left, right - left));
            left = right + 1;
        }
        return result;
    }
};

// 分块编码
class Codec_2 {
public:

    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        if(strs.empty()) return "";
        string result = "";
        for(const string& str: strs)
        {
            string len_str;
            int len = str.size();
            stringstream ss;
            ss << setw(4) << setfill('0') << len;
            ss >> len_str;
            result += len_str + str;
        }
        return result;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        if(s.empty()) return {};
        vector<string> result;
        int n = s.size();
        int left = 0;
        while(left < n)
        {
            string len_str = s.substr(left, 4);
            stringstream ss;
            int len;
            ss << len_str;
            ss >> len;
            left += 4;
            string str = s.substr(left, len);
            result.push_back(str);
            left += len;
        }
        return result;
    }
};
