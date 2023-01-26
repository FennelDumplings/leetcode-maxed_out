#include <regex>
#include <string>

using namespace std;

class Solution {
public:
    string validIPAddress(string IP) {
        string ipv4_chunk = "([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])";
        string pattern_ipv4 = "^(" + ipv4_chunk + "\\.){3}" + ipv4_chunk + "$";
        string ipv6_chunk = "([0-9a-fA-F]{1,4})";
        string pattern_ipv6 = "^(" + ipv6_chunk + "\\:){7}" + ipv6_chunk + "$";
        regex reg_ipv4(pattern_ipv4);
        regex reg_ipv6(pattern_ipv6);
        if(regex_match(IP, reg_ipv4))
            return "IPv4";
        if(regex_match(IP, reg_ipv6))
            return "IPv6";
        return "Neither";
    }
};
