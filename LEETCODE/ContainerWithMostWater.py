class Solution:
    def maxArea(self, height: List[int]) -> int:
        l = 0
        r = len(height) - 1

        maxArea = 0
        currentArea = 0

        while (l < r):
            currentArea = abs(r - l) * min(height[l], height[r])
            if (currentArea > maxArea):
                maxArea = currentArea

            if (height[l] < height[r]):
                l += 1
            else:
                r -= 1
        
        return maxArea