class Solution:
    def strongPasswordCheckerII(self, password: str) -> bool:
        n = len(password)
        if n < 8:
            return False
        lowercase = set([chr(i) for i in range(97, 123)])
        uppercase = set([chr(i) for i in range(65, 91)])
        digit = set([str(i) for i in range(10)])
        special = set("!@#$%^&*()-+")
        settings = [lowercase, uppercase, digit, special]
        flags = [False] * 4
        for i, ch in enumerate(password):
            if i < n - 1 and ch == password[i + 1]:
                return False
            for j, setting in enumerate(settings):
                flags[j] = ch in setting
        for flag in flags:
            if not flag:
                return False
        return True
