class Solution(object):
    def intersection(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: List[int]
        """
        set1 = set()

        for i in range(len(nums1)):
            set1.add(nums1[i])


        inter = set()
        for i in range(len(nums2)):
            if nums2[i] in set1:
                inter.add(nums2[i])

        return list(inter)