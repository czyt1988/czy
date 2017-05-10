#include <iostream>

using namespace std;
#include "../../src/czyMath.hpp"

void sum()
{
    typedef  double DATA_TYPE;
    vector<DATA_TYPE> datas;
    cout << endl;
    cout << "datas:" << endl;
    for(int i=0;i<10;++i)
    {
        datas.push_back(i);
        cout << datas[i] << ",";
    }
    cout << endl;
    double res = czy::Math::sum(datas.begin(),datas.end());
    cout << "sum test:" << res << endl;
    //45
}
void mean()
{
    typedef  double DATA_TYPE;
    vector<DATA_TYPE> datas;
    cout << endl;
    cout << "datas:" << endl;
    for(int i=0;i<10;++i)
    {
        datas.push_back(i);
        cout << datas[i] << ",";
    }
    cout << endl;
    double res = czy::Math::mean(datas.begin(),datas.end());
    cout << "mean test:" << res << endl;
    //4.5
}
void var()
{
    typedef  double DATA_TYPE;
    vector<DATA_TYPE> datas;
    cout << endl;
    cout << "datas:" << endl;
    for(int i=0;i<10;++i)
    {
        datas.push_back(i);
        cout << datas[i] << ",";
    }
    cout << endl;
    double res = czy::Math::var(datas.begin(),datas.end());
    cout << "var test:" << res << endl;
    //9.1667
}
void std_var()
{
    typedef  double DATA_TYPE;
    vector<DATA_TYPE> datas;
    cout << endl;
    cout << "datas:" << endl;
    for(int i=0;i<10;++i)
    {
        datas.push_back(i);
        cout << datas[i] << ",";
    }
    cout << endl;
    double res = czy::Math::std_var(datas.begin(),datas.end());
    cout << "std_var test:" << res << endl;
    //9.1667
}
int main()
{
    cout << "czyMath test!" << endl;
    sum();
    mean();
    var();
    std_var();
    return 0;
}
