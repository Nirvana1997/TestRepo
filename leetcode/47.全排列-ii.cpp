/*
 * @lc app=leetcode.cn id=47 lang=cpp
 *
 * [47] 全排列 II
 */

//  #include <vector>
//  #include <set>
 
//  using namespace std;

// @lc code=start
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<vector<int>> result;
        set<int> usedIdx;
        vector<int> tmpResult(nums.size());
        backtrace(nums, usedIdx, 0, tmpResult, result);        
        return result;
    }

    /*
    * 回溯
    * nums：题目数组
    * usedIdx：使用过的数组对应下标
    * curIdx：当前正在填入的idx
    * tmpResult：组合出的结果
    * result：最终结果
    */
    void backtrace(vector<int>& nums, set<int>& usedIdx, int idx, vector<int>& tmpResult, vector<vector<int>>& result)
    {
        static const int DEFAULT_LAST = 100; // 记录lastNum的初始默认值

        if (idx == nums.size())
        {
            result.emplace_back(tmpResult);
            return;
        }
        // int lastNum = DEFAULT_LAST;
        for (int i = 0; i < nums.size();i++)
        {
            // 对应位置数字已经用过或者与上一个使用的数字相同
            if (usedIdx.find(i) != usedIdx.end() || (i > 0 && nums[i - 1] == nums[i] && usedIdx.find(i - 1) == usedIdx.end()))
            {
                continue;
            }
            usedIdx.emplace(i);
            tmpResult[idx] = nums[i];
            // lastNum = nums[i];
            idx++;
            backtrace(nums, usedIdx, idx, tmpResult, result);
            usedIdx.erase(i);
            idx--;
            // lastNum = DEFAULT_LAST;
        }
    }
};
// @lc code=end

// int main()
// {
//     Solution s;
//     vector<int> v = {1,1,2};
//     s.permuteUnique(v);
//     return 0;
// }
