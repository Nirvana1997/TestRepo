#include <iostream>
#include <sstream>
#include <stack>
#include <unordered_map>

using namespace std;

string numberToWords(int num);
string oneNumToString(int oneNum);
string twoNumToString(int num);
string threeNumToString(int num);
int main()
{
    cout << numberToWords(1199) << endl;
    return 0;
}

static unordered_map<int, string> illonMap = {
    {1, "thousand"},
    {2, "million"},
    {3, "billion"},
    {4, "zillion"},
};

string numberToWords(int num)
{
    int bitNum = 0; // 有几个3位
    stack<string> stkNum;
    // 从右往左，每3位解析
    while (num != 0)
    {
        stkNum.push(threeNumToString(num % 1000));
        num /= 1000;
        bitNum++;
    }
    stringstream ss;
    while (stkNum.empty() == false)
    {
        if (stkNum.size() == 1)
        {
            ss << stkNum.top();
            break;
        }
        if (stkNum.top().empty() == false)
        {
            ss << stkNum.top() << " "
               << illonMap[bitNum - 1] << " ";
            bitNum--;
        }
        stkNum.pop();
    }
    string res;
    return ss.str();
}

string oneNumToString(int oneNum)
{
    switch (oneNum)
    {
    case 0:
        return "";
    case 1:
        return "one";
    case 2:
        return "two";
    case 3:
        return "three";
    case 4:
        return "four";
    case 5:
        return "five";
    case 6:
        return "six";
    case 7:
        return "seven";
    case 8:
        return "eight";
    case 9:
        return "nine";
    }
    return "";
}

string twoNumToString(int num)
{
    if (num < 10)
    {
        return oneNumToString(num);
    }
    else if (num >= 10 && num <= 19)
    {
        switch (num)
        {
        case 10:
            return "ten";
        case 11:
            return "eleven";
        case 12:
            return "twelve";
        case 13:
            return "thirteen";
        case 14:
            return "fourteen";
        case 15:
            return "fifteen";
        case 16:
            return "sixteen";
        case 17:
            return "seventeen";
        case 18:
            return "eighteen";
        case 19:
            return "nineteen";
        }
    }
    else
    {
        string res;
        switch (num / 10)
        {
        case 2:
            res = "twenty";
            break;
        case 3:
            res = "thirty";
            break;
        case 4:
            res = "forty";
            break;
        case 5:
            res = "fifty";
            break;
        case 6:
            res = "sixty";
            break;
        case 7:
            res = "seventy";
            break;
        case 8:
            res = "eighty";
            break;
        case 9:
            res = "ninty";
            break;
        }
        if (num % 10 != 0)
        {
            res += " " + oneNumToString(num % 10);
        }
        return res;
    }
    return "";
}

string threeNumToString(int num)
{
    string hundred = oneNumToString(num / 100);
    string twoNum = twoNumToString(num % 100);
    if (hundred.empty() == false)
    {
        return hundred + " hundred " + twoNum;
    }
    else
    {
        return twoNum;
    }
}