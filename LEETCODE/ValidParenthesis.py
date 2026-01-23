class Solution(object):
    def isValid(self, s):
        """
        :type s: str
        :rtype: bool
        """

        parenthesis = {
            "]": "[",
            ")": "(",
            "}": "{"
        }
        
        stack = []
        sp = -1

        for i in s:
            if i == "(" or i == "[" or i == "{":
                stack.append(i)
                sp += 1
            else:
                if sp == -1:
                    return False

                if stack[sp] == parenthesis[i]:
                    stack.pop()
                    sp -= 1
                else:
                    return False

        return len(stack) == 0