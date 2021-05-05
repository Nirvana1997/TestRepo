#include <algorithm>
#include <iostream>
#include <sys/time.h>
#include <unordered_map>
#include <vector>

using namespace std;

enum CASE
{
    CASE_1,
    CASE_2,
    CASE_3,
    CASE_4,
    CASE_5,
};

struct Param
{
    int param = 0;
};

unordered_map<int, function<void(Param)> > mapFunc =
    {
        {CASE_1, [](Param param) {}},
        {CASE_2, [](Param param) {}},
        {CASE_3, [](Param param) {}},
        {CASE_4, [](Param param) {}},
        {CASE_5, [](Param param) {}},
};

vector<pair<int, function<void(Param)> > > vectorFunc =
    {
        make_pair(CASE_1, [](Param param) {}),
        make_pair(CASE_2, [](Param param) {}),
        make_pair(CASE_3, [](Param param) {}),
        make_pair(CASE_4, [](Param param) {}),
        make_pair(CASE_5, [](Param param) {}),
};

void handleWithMap(CASE eCase, Param param)
{
    auto it = mapFunc.find((int)eCase);
    if (it != mapFunc.end())
    {
        it->second(param);
    }
    else
    {
        cout << "error" << endl;
    }
}

struct FindFunc
{
    FindFunc(CASE eCase) : m_eCase(eCase)
    {
    }

    bool operator()(const pair<int, function<void(Param)> > p) const
    {
        return m_eCase == p.first;
    }

    CASE m_eCase;
};

void handleWithVector(CASE eCase, Param param)
{
    auto it = find_if(vectorFunc.begin(), vectorFunc.end(), [&](const pair<int, function<void(Param)> > &func) -> bool {
        return eCase == func.first;
    });
    if (it != vectorFunc.end())
    {
        it->second(param);
    }
    else
    {
        cout << "error" << endl;
    }
}

void handleWithSwitch(CASE eCase, Param param)
{
    switch (eCase)
    {
    case CASE_1:
    {
    }
    break;
    case CASE_2:
    {
    }
    break;
    case CASE_3:
    {
    }
    break;
    case CASE_4:
    {
    }
    break;
    case CASE_5:
    {
    }
    break;
    default:
    {
    }
    break;
    }
}

int main()
{
    int times = 10000000;
    struct timeval start;
    struct timeval end;
    gettimeofday(&start, NULL);
    srand(123);
    for (int i = 0; i < times; i++)
    {
        CASE randCase = static_cast<CASE>(rand() % 5);
        handleWithMap(randCase, Param());
    }
    gettimeofday(&end, NULL);
    double time_use = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    cout.setf(ios::fixed);
    cout << "map:" << time_use / 1000 << "ms" << endl;

    gettimeofday(&start, NULL);
    srand(123);
    for (int i = 0; i < times; i++)
    {
        CASE randCase = static_cast<CASE>(rand() % 5);
        handleWithSwitch(randCase, Param());
    }
    gettimeofday(&end, NULL);
    time_use = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    cout << "switch:" << time_use / 1000 << "ms" << endl;

    gettimeofday(&start, NULL);
    srand(123);
    for (int i = 0; i < times; i++)
    {
        CASE randCase = static_cast<CASE>(rand() % 5);
        handleWithVector(randCase, Param());
    }
    gettimeofday(&end, NULL);
    time_use = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    cout << "vector:" << time_use / 1000 << "ms" << endl;

    return 0;
}