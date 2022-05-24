class Solution(object):
    def isValid(self, s):
        """
        :type s: str
        :rtype: bool
        """
        hash = { "(" : ")", "{" : "}", "[" : "]" }
        open = []
        for symbol in s:
            if symbol in hash.keys():
                open.append(symbol)
            elif open == [] or symbol != hash[open.pop()]:
                return False

        return open == []
