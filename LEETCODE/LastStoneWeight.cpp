class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        while (stones.size() != 1) {
            sort(stones.begin(), stones.end());
            stones[stones.size() - 2] = stones[stones.size() - 1] - stones[stones.size() - 2];
            stones.resize(stones.size() - 1);
        }
        return stones[0];
   }
};