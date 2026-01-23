class Solution(object):
    def romanToInt(self, s):
        """
        :type s: str
        :rtype: int
        """
        
        symbol = {
            "M": 1000,
            "D": 500,
            "C": 100,
            "L": 50,
            "X": 10,
            "V": 5,
            "I": 1
        }

        result = 0
        current = 0
        prev = 1001
        for i in s:
            current = symbol[i]
            if prev < current:
                current -= 2*prev
            result += current
            prev = current

        return result