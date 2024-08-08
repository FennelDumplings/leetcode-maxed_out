import re

class Solution:
    chunk_IPv4 = r'([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])'
    pattern_IPv4 = re.compile(r'^(' + chunk_IPv4 + r'\.){3}' + chunk_IPv4 + r'$')

    chunk_IPv6 = r'([0-9a-fA-F]{1,4})'
    pattern_IPv6 = re.compile(r'^(' + chunk_IPv6 + r'\:){7}' + chunk_IPv6 + r'$')

    def validIPAddress(self, IP: str) -> str:
        if '.' in IP:
            return "IPv4" if self.pattern_IPv4.match(IP) else "Neither"
        if ':' in IP:
            return "IPv6" if self.pattern_IPv6.match(IP) else "Neither"
        return "Neither"
