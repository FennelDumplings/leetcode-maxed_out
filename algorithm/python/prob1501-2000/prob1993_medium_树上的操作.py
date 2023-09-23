class LockingTree:

    def __init__(self, parent: List[int]):
        self.parent = parent
        n = len(parent)

        self.g = [[] for _ in range(n)]
        for v in range(n):
            u = parent[v]
            if u != -1:
                self.g[u].append(v)

        self.mapping = [-1] * n # num -> user


    def lock(self, num: int, user: int) -> bool:
        if self.mapping[num] == -1:
            self.mapping[num] = user
            return True
        return False


    def unlock(self, num: int, user: int) -> bool:
        if self.mapping[num] == user:
            self.mapping[num] = -1
            return True
        return False


    def upgrade(self, num: int, user: int) -> bool:
        if self.mapping[num] != -1:
            return False
        if not self.up(num):
            return False
        ans = False
        for son in self.g[num]:
            ans = self.dfs(son) or ans
        if ans:
            self.mapping[num] = user
        return ans


    def up(self, u: int) -> bool:
        while u != -1:
            if self.mapping[u] != -1:
                return False
            u = self.parent[u]
        return True


    def dfs(self, u: int) -> bool:
        ans = self.mapping[u] != -1
        if ans:
            self.mapping[u] = -1
        for v in self.g[u]:
            ans = self.dfs(v) or ans
        return ans
