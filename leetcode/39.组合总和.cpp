/*
 * @lc app=leetcode.cn id=39 lang=cpp
 *
 * [39] 组合总和
 */
#include <vector>

using namespace std;

// @lc code=start
class Solution {
public:
  vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> result;
    vector<int> curResult; // 当前回溯过程中挑选的数字
    backtrace(candidates, target, 0, curResult, 0, result);
    return result;
  }

  void backtrace(vector<int> &candidates, int target, int curIndex,
                 vector<int> &curResult, int curSum,
                 vector<vector<int>> &result) {
    for (int i = curIndex; i < candidates.size(); i++) {
      int num = candidates[i];
      do {
        curResult.emplace_back(num);
        curSum += num;
        if (curSum == target) {
          result.emplace_back(curResult);
          break;
        }
        if (curSum > target) {
          break;
        }
        backtrace(candidates, target, i, curResult, curSum, result);
      } while (false);
      curResult.pop_back();
      curSum -= num;
    }
  }
};
// @lc code=end
