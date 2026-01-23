class Solution(object):
    def addBinary(self, a, b):
        """
        :type a: str
        :type b: str
        :rtype: str
        """
        if (len(a) > len(b)):
            b = b.zfill(len(a))
            n = len(a)
        else:
            a = a.zfill(len(b))
            n = len(b)

        res = ""
        carry = 0
        for i in range(n - 1, -1, -1):
            s = int(a[i]) + int(b[i]) + carry
            if s == 3:
                res = "1" + res
                carry = 1
            else:
                if s == 2:
                    res = "0" + res
                    carry = 1
                else:
                    if s == 1:
                        res = "1" + res
                        carry = 0
                    else:
                        res = "0" + res
                        carry = 0

        if (carry == 1):        
            res = str(carry) + res
        return res