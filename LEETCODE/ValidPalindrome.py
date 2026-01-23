class Solution(object):
    def isPalindrome(self, s):
        """
        :type s: str
        :rtype: bool
        """
        def valid(ch):
            n = ord(ch)
            if (n >= 97 and n <= 122) or (n >= 48 and n <= 57):
                return True
            return False

        s = s.lower()
        left, right = 0, len(s) - 1

        while left < right:
            if valid(s[left]) and valid(s[right]):
                if s[left] == s[right]:
                    left += 1
                    right -= 1
                else:
                    return False
            else:
                if not valid(s[left]):
                    left += 1
                else:
                    right -= 1
            

        return True
        