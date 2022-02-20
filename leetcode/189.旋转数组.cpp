/*
 * @lc app=leetcode.cn id=189 lang=cpp
 *
 * [189] 旋转数组
 */

#include <iostream>
#include <vector>

using namespace std;

// @lc code=start
class Solution
{
 public:
  void rotate(vector<int>& nums, int k)
  {
    k = k % nums.size();
    if (k == 0)
    {
      return;
    }
    // 保留最后一段需要放至开头的
    vector<int> restNums(nums.end() - k, nums.end());
    // for (auto i : restNums)
    // {
    //   cout << i;
    // }
    // cout << endl;

    // 旋转到目标点后暂时被替换的数据
    int replaced = 0;
    // 按index: 0,k,2k,..,1,k+1,2k+1的顺序遍历
    for (int i = 0; i < k; i++)
    {
      int index = i;
      replaced = nums[index];
      while (index < nums.size())
      {
        if (index + k < nums.size())
        {
          int toReplace = nums[index + k];
          nums[index + k] = replaced;
          replaced = toReplace;
          index += k;
        }
        else
        {
          break;
        }
      }
    }
    // 替换开头一段
    for (int i = 0; i < restNums.size(); i++)
    {
      nums[i] = restNums[i];
    }
  }
};
// @lc code=end

int main()
{
  Solution s;
  vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8};
  s.rotate(v, 2);
  for (auto i : v)
  {
    cout << i;
  }
  return 0;
}