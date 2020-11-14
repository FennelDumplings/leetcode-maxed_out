// prob535: Encode and Decode TinyURL

/*
 * https://leetcode-cn.com/problems/encode-and-decode-tinyurl/
 */

#include <vector>
#include <string>

using namespace std;

char base64_code(const int& mask)
{
    if(mask <= 25)
        return 'A' + mask;
    else if(mask <= 51)
        return 'a' + mask - 26;
    else if(mask <= 61)
        return '0' + mask - 52;
    else if(mask == 62)
        return '-';
    else if(mask == 63)
        return '_';
    else
        throw "编码 mask 超出 6 bit 范围(0~63)";
}

int reverse_base64_code(const char& ch)
{
    if('A' <= ch && ch <= 'Z')
        return ch - 'A';
    else if('a' <= ch && ch <= 'z')
        return ch - 'a' + 26;
    else if('0' <= ch && ch <= '9')
        return ch - '0' + 52;
    else if(ch == '-')
        return 62;
    else if(ch == '_')
        return 63;
    else
        throw "解码 mask 超出 6 bit 范围(0~63)";
}

class Base64
{
public:
    string encode(string data) {
        int n = data.size();
        string result;
        int i = 0;
        while(i + 3 <= n)
        {
            // data[i, i+1, i+2]
            int block = 0;
            for(int j = 0; j < 3; ++j)
            {
                char ch = data[i + j];
                block <<= 8;
                block += ch;
            }
            // [23 18], [17 12], [11 6], [5 0]
            int l = 23;
            while(l > 0)
            {
                int r = l - 5;
                int mask = ((1 << 6) - 1) << r;
                result += base64_code((block & mask) >> r);
                l = r - 1;
            }
            i += 3;
        }
        if(n - i == 1)
        {
            int block = data[i];
            block <<= 4;
            // [11 6], [5 0]
            int l = 11;
            while(l > 0)
            {
                int r = l - 5;
                int mask = ((1 << 6) - 1) << r;
                result += base64_code((block & mask) >> r);
                l = r - 1;
            }
            result += "==";
        }
        else if(n - i == 2)
        {
            int block = data[i++];
            block <<= 8;
            block += data[i];
            block <<= 2;
            // [17 12], [11 6], [5 0]
            int l = 17;
            while(l > 0)
            {
                int r = l - 5;
                int mask = ((1 << 6) - 1) << r;
                result += base64_code((block & mask) >> r);
                l = r - 1;
            }
            result += '=';
        }
        return result;
    }

    string decode(string str) {
        string data;
        int n = str.size();
        int i = 0;
        while(i + 4 < n)
        {
            int block = 0;
            for(int j = 0; j < 4; ++j)
            {
                char base64_ch = str[i + j];
                block <<= 6;
                block += reverse_base64_code(base64_ch);
            }
            for(int j = 16; j >= 0; j -= 8)
            {
                int mask = ((1 << 8) - 1) << j;
                data += char((block & mask) >> j);
            }
            i += 4;
        }
        if(str[n - 2] == '=')
        {
            int block = 0;
            for(int j = 0; j < 2; ++j)
            {
                char base64_ch = str[i + j];
                block <<= 6;
                block += reverse_base64_code(base64_ch);
            }
            block >>= 4;
            int mask = (1 << 8) - 1;
            data += char(block & mask);
        }
        else if(str[n - 1] == '=')
        {
            int block = 0;
            for(int j = 0; j < 3; ++j)
            {
                char base64_ch = str[i + j];
                block <<= 6;
                block += reverse_base64_code(base64_ch);
            }
            block >>= 2;
            for(int j = 8; j >= 0; j -= 8)
            {
                int mask = ((1 << 8) - 1) << j;
                data += char((block & mask) >> j);
            }
        }
        else
        {
            int block = 0;
            for(int j = 0; j < 4; ++j)
            {
                char base64_ch = str[i + j];
                block <<= 6;
                block += reverse_base64_code(base64_ch);
            }
            for(int j = 16; j >= 0; j -= 8)
            {
                int mask = ((1 << 8) - 1) << j;
                data += char((block & mask) >> j);
            }
        }
        return data;
    }
};

class Solution_2 {
public:
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        return base64.encode(longUrl);
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        return base64.decode(shortUrl);
    }

private:
    Base64 base64;
};

#include <unordered_map>
#include <random>

class Solution {
public:
    Solution()
    {
        dre = std::default_random_engine();
        di = std::uniform_int_distribution<int>(0, 61);
    }

    string get_random_key()
    {
        string result;
        for(int i = 0; i < 6; ++i)
        {
            result += ALPHABET[di(dre)];
        }
        return result;
    }

    string encode(string longUrl) {
        string key = get_random_key();
        while(mapping.count(key) != 0)
            key = get_random_key();
        mapping[key] = longUrl;
        return "http://tinyurl.com/" + key;
    }

    string decode(string shortUrl) {
        auto it = shortUrl.find_last_of('/');
        string key = shortUrl.substr((it - shortUrl.begin()) + 1);
        return mapping[key];
    }

private:
    const string ALPHABET = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int IDX_LAST = 62;
    std::default_random_engine dre;
    std::uniform_int_distribution<int> di;
    unordered_map<string, string> mapping;
};
