class Solution:
    def destCity(self, paths: List[List[str]]) -> str:
        setting1 = set()
        setting2 = set()
        for [s, t] in paths:
            if s in setting2:
                setting2.remove(s)
            else:
                setting1.add(s)
            if t in setting1:
                setting1.remove(t)
            else:
                setting2.add(s)
        return list(setting2)[0]
