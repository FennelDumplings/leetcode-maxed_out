class Solution:
    def capitalizeTitle(self, title: str) -> str:
        words = []
        for s in title.split():
            if len(s) <= 2:
                words.append(s.lower())
            else:
                words.append(s[0].capitalize() + s[1:].lower())
        return " ".join(words)

