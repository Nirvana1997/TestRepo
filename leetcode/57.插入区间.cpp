/*
 * @lc app=leetcode.cn id=57 lang=cpp
 *
 * [57] 插入区间
 */

// @lc code=start
class Solution {
public:
  vector<vector<int>> insert(vector<vector<int>> &intervals,
                             vector<int> &newInterval) {
    bool bNeedMerge = false; // 若合并过，最后需要判断是否需要向后继续合并
    auto it = intervals.begin();
    for (; it != intervals.end(); it++) {
      // it对应集合整体小于new
      if (newInterval[0] > (*it)[1]) {
        continue;
      }
      // it对应集合整体大于new
      else if (newInterval[1] < (*it)[0]) {
        intervals.insert(it, newInterval);
        return intervals;
      }
      // it与new相交
      else {
        // 合并集合
        (*it)[0] = (*it)[0] > newInterval[0] ? newInterval[0] : (*it)[0];
        (*it)[1] = (*it)[1] > newInterval[1] ? (*it)[1] : newInterval[1];
        bNeedMerge = true;
        break;
      }
    }
    if (bNeedMerge == false) {
      intervals.emplace_back(newInterval);
    } else {
      auto itMerge = it + 1;
      for (; itMerge != intervals.end(); itMerge++) {
        if ((*it)[1] >= (*itMerge)[0]) {
          (*it)[1] = (*it)[1] > (*itMerge)[1] ? (*it)[1] : (*itMerge)[1];
        } else {
          break;
        }
      }
      if (it + 1 != itMerge) {
        intervals.erase(it + 1, itMerge);
      }
    }
    return intervals;
  }
};
// @lc code=end
