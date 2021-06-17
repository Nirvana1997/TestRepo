#include <algorithm>
#include <iostream>
#include <sys/time.h>
#include <unordered_map>
#include <vector>
#include "macro_loop.h"

using namespace std;

#define MARCO_LOOP_X 5

#define DECLARE(n) CASE_##n,
#define MACRO_LOOP_CMD(n) DECLARE(n)
enum CASE
{
    MACRO_LOOP(MARCO_LOOP_X)
};
#undef DECLARE 
#undef MACRO_LOOP_CMD

struct Param
{
    int param = 0;
};

void handleFunc(Param& param)
{
}

#define DECLARE(n) {CASE_##n, [](Param& param) {handleFunc(param);}},
#define MACRO_LOOP_CMD(n) DECLARE(n)
unordered_map<int, function<void(Param&)> > mapFunc =
{
    MACRO_LOOP(MARCO_LOOP_X)
};
#undef DECLARE
#undef MACRO_LOOP_CMD

#define DECLARE(n) make_pair(CASE_##n, [](Param& param) {handleFunc(param);}),
#define MACRO_LOOP_CMD(n) DECLARE(n)
vector<pair<int, function<void(Param&)> > > vectorFunc =
{
    MACRO_LOOP(MARCO_LOOP_X)
};
#undef DECLARE
#undef MACRO_LOOP_CMD

#define DECLARE(n) [](Param& param) {handleFunc(param);},
#define MACRO_LOOP_CMD(n) DECLARE(n)
function<void(Param&)> arrayFunc[] =
{
  MACRO_LOOP(MARCO_LOOP_X)
};
#undef DECLARE
#undef MACRO_LOOP_CMD

typedef void (*FUNC_POINT)(Param&);

#define DECLARE(n) handleFunc,
#define MACRO_LOOP_CMD(n) DECLARE(n)
FUNC_POINT arrayFuncPoint[] =
{
  MACRO_LOOP(MARCO_LOOP_X)
};
#undef DECLARE
#undef MACRO_LOOP_CMD

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

    bool operator()(const pair<int, function<void(Param&)> > p) const
    {
        return m_eCase == p.first;
    }

    CASE m_eCase;
};

void handleWithVector(CASE eCase, Param param)
{
    auto it = find_if(vectorFunc.begin(), vectorFunc.end(), [&](const pair<int, function<void(Param&)> > &func) -> bool {
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

#define DECLARE(n)     case CASE_##n:handleFunc(param);break;
#define MACRO_LOOP_CMD(n) DECLARE(n)
void handleWithSwitch(CASE eCase, Param param)
{
    switch (eCase)
    {
        MACRO_LOOP(MARCO_LOOP_X)
    default:
    {
    }
    break;
    }
}
#undef DECLARE 
#undef MACRO_LOOP_CMD

void handleWithArray(CASE eCase, Param param)
{
    arrayFunc[eCase](param);
}

void handleWithArrayPoint(CASE eCase, Param param)
{
    arrayFuncPoint[eCase](param);
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
        CASE randCase = static_cast<CASE>(rand() % MARCO_LOOP_X);
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
        CASE randCase = static_cast<CASE>(rand() % MARCO_LOOP_X);
        handleWithSwitch(randCase, Param());
    }
    gettimeofday(&end, NULL);
    time_use = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    cout << "switch:" << time_use / 1000 << "ms" << endl;

    gettimeofday(&start, NULL);
    srand(123);
    for (int i = 0; i < times; i++)
    {
        CASE randCase = static_cast<CASE>(rand() % MARCO_LOOP_X);
        handleWithVector(randCase, Param());
    }
    gettimeofday(&end, NULL);
    time_use = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    cout << "vector:" << time_use / 1000 << "ms" << endl;

    gettimeofday(&start, NULL);
    srand(123);
    for (int i = 0; i < times; i++)
    {
        CASE randCase = static_cast<CASE>(rand() % MARCO_LOOP_X);
        handleWithArray(randCase, Param());
    }
    gettimeofday(&end, NULL);
    time_use = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    cout << "array:" << time_use / 1000 << "ms" << endl;

    gettimeofday(&start, NULL);
    srand(123);
    for (int i = 0; i < times; i++)
    {
        CASE randCase = static_cast<CASE>(rand() % MARCO_LOOP_X);
        handleWithArray(randCase, Param());
    }
    gettimeofday(&end, NULL);
    time_use = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    cout << "pointArray:" << time_use / 1000 << "ms" << endl;

    return 0;
}
