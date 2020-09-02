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
class Codec_3 {
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

// 哈夫曼
#include <climits>
#include <unordered_map>

struct HFNode
{
    char data;
    int weight;
    int parent, left, right;
};

struct HFCode
{
    char data;
    string code;
};

class HuffmanTree
{
public:
    HuffmanTree(){}
    ~HuffmanTree(){}

    void build(const string& v, const vector<int>& w)
    {
        int size = v.size();
        length = 2 * size;
        // 节点共 size * 2 - 1 个，放在 elem[1..2*size-1] 中
        elem = vector<HFNode>(length);

        int min1, min2;
        int x, y;

        // size 个叶子节点放在 elem[size..2*size-1]
        for(int i = size; i < length; i++)
        {
            elem[i].weight = w[i - size];
            elem[i].data = v[i - size];
            elem[i].parent = elem[i].left = elem[i].right = 0;
        }

        // size - 1 个非叶子节点: elem[1..size-1]
        for(int i = size - 1; i > 0; i--)
        {
            min1 = min2 = INT_MAX;
            x = y = 0;
            for(int j = i + 1; j < length; j++)
            {
                if(elem[j].parent == 0)
                {
                    if(elem[j].weight < min1)
                    {
                        min2 = min1;
                        min1 = elem[j].weight;
                        x=y;
                        y=j;
                    }
                    else if(elem[j].weight<min2)
                    {
                        min2 = elem[j].weight;
                        x=j;
                    }
                }
            }
            elem[i].weight = min1 + min2;
            elem[i].left = x;
            elem[i].right = y;
            elem[i].parent = 0;
            elem[x].parent = i;
            elem[y].parent = i;
        }
    }

    vector<HFCode> get_code()
    {
        int n_leaf = length / 2; // 叶节点个数
        vector<HFCode> result(n_leaf);
        int p, s;
        // [n_leaf..length - 1] 为 elem 中的 n_leaf 个叶节点
        for(int i = n_leaf; i < length; i++)
        {
            result[i - n_leaf].data = elem[i].data;
            result[i - n_leaf].code = "";
            p = elem[i].parent;
            s = i;
            while(p)
            {
                if(elem[p].left == s)
                    result[i - n_leaf].code = '0' + result[i - n_leaf].code;
                else
                    result[i - n_leaf].code = '1' + result[i - n_leaf].code;
                s = p;
                p = elem[p].parent;
            }
        }
        return result;
    }

    string encode(const string& data)
    {
        vector<HFCode> hfcode = get_code();
        unordered_map<char, string> hfcode_map;
        for(const HFCode &code_info: hfcode)
            hfcode_map[code_info.data] = code_info.code;
        string result;
        for(const char &item: data)
            result += hfcode_map[item];
        return result;
    }

    string decode(const string& seq)
    {
        string data;
        int n = seq.size();
        int iter = 0;
        while(iter < n)
        {
            int node = 1; // 根节点是 1
            while(elem[node].left != 0)
            {
                if(seq[iter] == '0')
                    node = elem[node].left;
                else
                    node = elem[node].right;
                ++iter;
            }
            data.push_back(elem[node].data);
        }
        return data;
    }

    int charset_size()
    {
        return length / 2;
    }

private:
    vector<HFNode> elem;
    int length;
};


class Codec {
public:
    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        if(strs.empty()) return "";
        unordered_map<char, int> mapping = stat(strs);
        string v;
        vector<int> w;
        for(const auto &item: mapping)
        {
            v.push_back(item.first);
            w.push_back(item.second);
        }
        hftree.build(v, w);
        string seq;
        if(hftree.charset_size() <= 1)
        {
            p = (char)256;
            for(const string& str: strs)
                seq += str + p;
        }
        else
        {
            p = '2';
            for(const string& str: strs)
                seq += hftree.encode(str) + p;
        }
        return seq;
    }

    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        if(s.empty()) return {};
        vector<string> result;
        int n = s.size();
        int left = 0;
        while(left < n)
        {
            int right = left;
            while(right < n && s[right] != p)
                ++right;
            string seq = s.substr(left, right - left);
            string d_seq;
            if(hftree.charset_size() <= 1)
                d_seq = seq;
            else
                d_seq = hftree.decode(seq);
            result.push_back(d_seq);
            left = right + 1;
        }
        return result;
    }

private:
    HuffmanTree hftree;
    char p;

    unordered_map<char, int> stat(const vector<string>& strs)
    {
        unordered_map<char, int> mapping;
        for(const string& str: strs)
        {
            for(const char& ch: str)
                ++mapping[ch];
        }
        return mapping;
    }
};
