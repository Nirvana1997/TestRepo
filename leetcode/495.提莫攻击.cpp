/*
 * @lc app=leetcode.cn id=495 lang=cpp
 *
 * [495] 提莫攻击
 */

// @lc code=start
class Solution {
public:
    int findPoisonedDuration(vector<int>& timeSeries, int duration) {
        int result = 0;
        int nextEndTime = 0; // 上一次毒结束时间
        for (int time : timeSeries)
        {
            // 扣除重叠部分
            if (nextEndTime != 0 && time < nextEndTime)
            {
                result += duration + time - nextEndTime;
            }
            else
            {
                result += duration;
            }
            nextEndTime = time + duration;
        }
        return result;
    }
};
// @lc code=end

