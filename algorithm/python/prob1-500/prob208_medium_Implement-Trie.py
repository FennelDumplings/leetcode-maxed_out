ALPHABETS = 26;

class TrieNode:
    def __init__(self):
        self.terminal = False
        self.children = [None] * ALPHABETS

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

    def search(self, word: str) -> bool:
        node_iter = self._find(word)
        return node_iter is not None and node_iter.terminal

    def startsWith(self, prefix: str) -> bool:
        return self._find(prefix) is not None

    def _find(self, prefix):
        node_iter = self.root
        for c in prefix:
            node_iter = (node_iter.children)[ord(c) - ord('a')]
            if node_iter is None:
                break
        return node_iter
