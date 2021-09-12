/*
 * @lc app=leetcode.cn id=692 lang=cpp
 *
 * [692] 前K个高频单词
 */

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

using namespace std;

// @lc code=start
class Solution
{
 public:
  vector<string> topKFrequent(vector<string>& words, int k)
  {
    map<string, int> mapWord2Num;
    for (auto& word : words)
    {
      mapWord2Num[word]++;
    }
    // 由大到小排序
    list<pair<string, int>> listStat;
    for (auto& word2num : mapWord2Num)
    {
      if (listStat.size() >= k)
      {
        if (word2num.second <= listStat.back().second)
        {
          continue;
        }
        else
        {
          listStat.pop_back();
        }
      }
      if (listStat.empty() == true)
      {
        listStat.emplace_back(word2num);
      }
      else
      {
        if (listStat.begin()->second < word2num.second)
        {
          listStat.push_front(word2num);
          continue;
        }
        auto it = listStat.begin();
        for (; it != listStat.end(); it++)
        {
          if (it->second < word2num.second)
          {
            break;
          }
        }
        listStat.insert(it, word2num);
      }
    }
    vector<string> result;
    for (auto& pair : listStat)
    {
      result.emplace_back(pair.first);
    }
    return result;
  }
};
// @lc code=end

int main()
{
  Solution s;
  vector<string> vec = {"i", "love", "leetcode", "i", "love", "coding"};
  s.topKFrequent(vec, 3);
  //   list<int> num;
  //   num.insert(num.begin(), 1);
  //   num.insert(num.begin(), 2);

  //   for (auto x : num)
  //   {
  //     cout << x << endl;
  //   }

  return 0;
}