#pragma once
#include <string>
using namespace std;
class Date
{
public:
    Date(string srcDate)
    {
        string strYear = srcDate.substr(0, 4), strMonth = srcDate.substr(5, 7);
        _year = stoi(strYear);
        _month = stoi(strMonth);
    }
    int getMonth(){return _month;}
    int getYear(){return _year;}

private:
    int _month;
    int _year;
};
