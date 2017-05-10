#include <iostream>

using namespace std;
#include "../../src/czyMath.hpp"

typedef  double DATA_TYPE;
#define VectorDataCalcTest(funName)\
    void funName(const vector<DATA_TYPE>& data)\
    {\
        double res = czy::Math::funName(data.begin(),data.end());\
        cout << #funName "test:" << res << endl;\
    }

VectorDataCalcTest(sum)
VectorDataCalcTest(mean)
VectorDataCalcTest(var)
VectorDataCalcTest(std_var)

int main()
{
    cout << "czyMath test!" << endl;
    vector<DATA_TYPE> datas;
    cout << "datas:" << endl;
    for(int i=0;i<10;++i)
    {
        datas.push_back(i);
        cout << datas[i] << ",";
    }
    cout << endl;
    sum(datas);
    mean(datas);
    var(datas);
    std_var(datas);
    return 0;
}
