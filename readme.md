# 数据计算的C++封装

- czy.h: 基本全局定义
- czyMath.hpp：基本数据计算封装，包括统计类的以及一些数据处理的基本算法
- czyDsp.hpp: 信号处理的封装
- czyFit: 曲线拟合的封装

## czyMath.hpp

### sum

对数组求和

```cpp
void sum()
{
    typedef  double DATA_TYPE;
    vector<DATA_TYPE> datas;
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
```

### mean

求平均值

```cpp
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
```

### var

求方差

```cpp
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
```

### std_var

求标准差

```cpp
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
    //3.02765
}
```
