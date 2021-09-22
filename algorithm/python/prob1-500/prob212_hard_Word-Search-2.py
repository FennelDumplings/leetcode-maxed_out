ALPHABETS = 26

class TrieNode:
    def __init__(self):
        self.terminal = False
        self.children = [None] * ALPHABETS
        self.word = ""

    def get_nxt(self, ch):
        return self.children[ord(ch) - ord('a')]

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word: str) -> None:
        node_iter = self.root
        for c in word:
            if node_iter.children[ord(c) - ord('a')] is None:
                node_iter.children[ord(c) - ord('a')] = TrieNode()
            node_iter = node_iter.children[ord(c) - ord('a')]
        node_iter.terminal = True
        node_iter.word = word

    def get_root(self):
        return self.root


class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        n = len(board)
        m = len(board[0])
        self.dx = [1, -1, 0, 0]
        self.dy = [0, 0, 1, -1]
        trie = Trie()
        for word in words:
            trie.insert(word)
        result = []
        visited = []
        for i in range(n):
            visited.append([False] * m)
        for i in range(n):
            for j in range(m):
                node_iter = trie.get_root()
                visited[i][j] = True
                self.dfs(board, visited, i, j, result, node_iter)
                visited[i][j] = False
        return result

    def dfs(self, board, visited, i, j, result, node_iter):
        nxt = node_iter.get_nxt(board[i][j])
        if nxt is None:
            return
        node_iter = nxt
        if node_iter.terminal:
            result.append(node_iter.word)
            node_iter.terminal = False
        n = len(board)
        m = len(board[0])
        for d in range(4):
            x = i + self.dx[d]
            y = j + self.dy[d]
            if x < 0 or x >= n or y < 0 or y >= m:
                continue
            if visited[x][y]:
                continue
            visited[x][y] = True
            self.dfs(board, visited, x, y, result, node_iter)
            visited[x][y] = False
