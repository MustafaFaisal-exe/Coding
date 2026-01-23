class Solution(object):
    def plusOne(self, digits):
        """
        :type digits: List[int]
        :rtype: List[int]
        """
        summ = 0
        carry = 1
        result = []
        for i in range(len(digits) - 1, -1, -1):
            summ = (digits[i] + carry) % 10
            carry = (digits[i] + carry) / 10
            result.append(summ)
        
        if (carry):
            result.append(1)
            
        return result[::-1]