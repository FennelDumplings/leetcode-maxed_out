import copy

ALPHABETS = 26

class TrieNode:
    def __init__(self):
        self.terminate = False
        self.children = [None] * ALPHABETS

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word):
        node_iter = self.root
        for ch in word:
            if node_iter.children[ord(ch) - ord('a')] is None:
                node_iter.children[ord(ch) - ord('a')] = TrieNode()
            node_iter = node_iter.children[ord(ch) - ord('a')]
        node_iter.terminate = True

    def get_root(self):
        return self.root

    def get_nxt(self, ch, node_iter):
        return node_iter.children[ord(ch) - ord('a')]

    def show(self):
        word = []
        self.dfs(self.root, word)

    def dfs(self, node, word):
        if node.terminate:
            print("".join(word))
        for i in range(ALPHABETS):
            if node.children[i] is None:
                continue
            print(i)
            nxt = node.children[i]
            ch = chr(ord('a') + i)
            word += ch
            self.dfs(nxt, word)
            word.pop()


class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        n = len(board)
        m = len(board[0])
        self.dx = [1, -1, 0, 0]
        self.dy = [0, 0, 1, -1]
        trie = Trie()
        for word in words:
            trie.insert(word)
        visited = []
        result = []
        cur = []
        node_iter = trie.get_root()
        for i in range(n):
            for j in range(m):
                visited = [[False] * m] * n
                visited[i][j] = True
                cur += board[i][j]
                self.dfs(board, visited, i, j, cur, result, trie, copy.copy(node_iter))
                cur.pop()
                visited[i][j] = False
        return result

    def dfs(self, board, visited, i, j, cur, result, trie, node_iter):
        nxt = trie.get_nxt(board[i][j], node_iter)
        if nxt is None:
            return
        node_iter = nxt
        if node_iter.terminate:
            print("".join(cur))
            result.append("".join(cur))
            node_iter.terminate = False
        n = len(board)
        m = len(board[0])
        for d in range(4):
            x = i + self.dx[d]
            y = j + self.dy[d]
            if x < 0 or x >= n or y < 0 or y >= m or visited[x][y]:
                continue
            visited[x][y] = True
            cur += board[x][y]
            self.dfs(board, visited, x, y, cur, result, trie, copy.copy(node_iter))
            cur.pop()
            visited[x][y] = False
