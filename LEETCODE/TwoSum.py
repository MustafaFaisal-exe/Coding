class Solution(object):
    def twoSum(self, nums, target):
        track = {}
        for i in range(len(nums)):
            if target - nums[i] in track:
                return [track[target-nums[i]], i]
            else:
                track[nums[i]] = i