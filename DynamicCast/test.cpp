#include <sys/time.h>
#include <unistd.h>

#include <algorithm>
#include <ctime>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

unsigned long long getUSec()
 {
   struct timeval time;
   gettimeofday(&time, NULL);
   return time.tv_sec * 1000000 + time.tv_usec;
 }

 enum EntryType
 {
   ENTRYTYPE_MIN = 0,
   ENTRYTYPE_USER = 1,
   ENTRYTYPE_NPC = 2,
   ENTRYTYPE_MAX
 };

 class SceneEntry
 {
  public:
   SceneEntry(unsigned long long id, const std::string& name);
   virtual ~SceneEntry() = default;

   virtual EntryType getType() const
   {
     return ENTRYTYPE_MIN;
   }

  protected:
   unsigned long long m_id = 0;
   std::string m_name;
 };

 class SceneUser : public SceneEntry
 {
  public:
   SceneUser(unsigned long long id, const std::string& name);
   virtual ~SceneUser() = default;

   virtual EntryType getType() const
   {
     return ENTRYTYPE_USER;
   }
   static SceneUser* get(SceneEntry* p)
   {
     return p != nullptr && p->getType() == ENTRYTYPE_USER ? (SceneUser*)(p) : nullptr;
   }
 };

class SceneNpc : public SceneEntry
 {
  public:
  SceneNpc(unsigned long long id, const std::string& name);
  virtual ~SceneNpc() = default;
  virtual EntryType getType() const
   {
     return ENTRYTYPE_NPC;
   }
   inline static SceneNpc* get(SceneEntry* p)
   {
     return p != nullptr && p->getType() == ENTRYTYPE_NPC ? (SceneNpc*)(p) : nullptr;
   }
 };

 SceneEntry::SceneEntry(unsigned long long id, const std::string& name) : m_id(id), m_name(name)
 {
 }

 SceneUser::SceneUser(unsigned long long id, const std::string& name) : SceneEntry(id, name)
 {
 }

 SceneNpc::SceneNpc(unsigned long long id, const std::string& name) : SceneEntry(id, name)
 {
 }

int main()
{
  SceneUser* pUser = new SceneUser(1, "xiaoming");
  int count = 0;
  while (std::cin >> count)
  {
    int count2 = 0;
    unsigned long long startTime = getUSec();
    for (count2 = 0; count2 < count; ++count2)
    {
      SceneUser* pUser2 = (SceneUser*)(pUser);
    }
    unsigned long long endTime = getUSec();
    std::cout << "显式转换,次数:" << count2 << ",耗时:" << endTime - startTime << std::endl;

    unsigned long long startTime2 = getUSec();
    for (count2 = 0; count2 < count; ++count2)
    {
      SceneUser* pUser2 = static_cast<SceneUser*>(pUser);
    }
    unsigned long long endTime2 = getUSec();
    std::cout << "static_cast,次数:" << count2 << ",耗时:" << endTime2 - startTime2 << std::endl;

    unsigned long long startTime3 = getUSec();
    for (count2 = 0; count2 < count; ++count2)
    {
      SceneUser* pUser2 = dynamic_cast<SceneUser*>(pUser);
    }
    unsigned long long endTime3 = getUSec();
    std::cout << "dynamic_cast,次数:" << count2 << ",耗时:" << endTime3 - startTime3 << std::endl;
  }
  delete pUser;
  return 0;
}
