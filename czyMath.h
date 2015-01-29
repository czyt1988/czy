#ifndef CZYMATH_H
#define CZYMATH_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <functional>
#include <math.h>
#include <memory>

#ifndef INPUT
#define INPUT
#endif

#ifndef OUTPUT
#define OUTPUT
#endif

namespace czy{

///
/// \brief The Math namespace 用于处理简单数学计算
///
namespace Math
{

    const double PI = 3.1415926535897932384626;
    const double PI2 = 6.2831853071795864769252;

    ///
    /// \brief 对数组求和
    /// \param _begin 数据开始迭代器
    /// \param _end 数据结束迭代器
    ///
    template <typename IT> inline
    double sum(INPUT const IT _begin,INPUT const IT _end)
    {
        IT it = _begin;
        double total(0.0);
        for(;it!=_end;++it){
            total += *it;
        }
        return total;
    }
    ///
    /// \brief 求平均值的模版函数
    /// \param _begin 数据开始迭代器
    /// \param _end 数据结束迭代器
    ///
    template <typename IT> inline
    double mean(INPUT const IT _begin,INPUT const IT _end)
    {
        return sum(_begin,_end)/(_end - _begin);
    }
    ///
    /// \brief 求序列的方差 - 为n-1类型既是序列是随机抽样不是固定值
    /// \param _begin 数据开始迭代器
    /// \param _end 数据结束迭代器
    ///
    template <typename IT> inline
    double var(INPUT const IT _begin,INPUT const IT _end)
    {
        double m = Math::mean(_begin,_end);
        double d(0);
        IT it = _begin;
        for(;it!=_end;++it)
        {
            d += ((m - (*it)) * (m - (*it)));
        }
        size_t length = _end - _begin;
        if(length>1)
            length -= 1;//随机序列的方差要减去1
        return var/length;
    }
    ///
    /// \brief 求序列的标准差 - 为n-1类型既是序列是随机抽样不是固定值
    /// \param _begin 数据开始迭代器
    /// \param _end 数据结束迭代器
    ///
    template <typename IT> inline
    double std_var(INPUT const IT _begin,INPUT const IT _end)
    {
        double v = var(_begin,_end);
        return sqrt(v);
    }
    ///
    /// \brief 求序列的n阶中心矩
    ///
    /// 均值为1阶中心矩，方差为特殊的2阶矩
    /// \param _begin 数据开始迭代器
    /// \param _end 数据结束迭代器
    ///
    template <typename IT> inline
    double central_moment(INPUT const IT _begin,INPUT const IT _end,INPUT unsigned order)
    {
        double m = mean(_begin,_end);
        double tmp(0),res(0);
        size_t length = _end - _begin;
        for(IT it = _begin;it!=_end;++it)
        {
            tmp = ((*it) - m);
            res += pow(tmp,order);
        }
        res /= length;
        return res;
    }
    ///
    /// \brief 求序列的n阶原点矩
    /// \param _begin 数据开始迭代器
    /// \param _end 数据结束迭代器
    ///
    template <typename IT> inline
    double origin_moment(INPUT const IT _begin,INPUT const IT _end,INPUT unsigned order)
    {
        double res(0);
        size_t length = _end - _begin;
        for(IT it = _begin;it!=_end;++it)
        {
            res += pow(*it,order);
        }
        res /= length;
        return res;
    }
    ///
    /// \brief 求序列的斜度 - 3次矩
    /// \param _begin 数据开始迭代器
    /// \param _end 数据结束迭代器
    ///
    template <typename IT> inline
    double skewness(INPUT const IT _begin,INPUT const IT _end)
    {
        double s = std_var(_begin,_end);
        double res = central_moment(_begin,_end,3);//先求3阶中心距
        res /= (s*s*s);
        return res;
    }

    ///
    /// \brief 求序列的峰度(峭度) - 4次矩
    /// \param _begin 数据开始迭代器
    /// \param _end 数据结束迭代器
    ///
    template <typename IT> inline
    double kurtosis(INPUT const IT _begin,INPUT const IT _end)
    {
        double v = var(_begin,_end);
        double res = central_moment(_begin,_end,4);//先求4阶中心距
        res /= (v*v);
        return res;
    }
    ///
    /// \brief 求序列的峰峰值
    /// \param _begin 数据开始迭代器
    /// \param _end 数据结束迭代器
    ///
    template <typename IT> inline
    double peak_to_peak_value(INPUT const IT _begin,INPUT const IT _end)
    {
        return (*std::max_element(_begin,_end) - *std::min_element(_begin,_end));
    }
    ///
    /// \brief 获取统计参数，包括和，均值，方差，标准差，斜度，峭度
    /// \param _begin 数据开始迭代器
    /// \param _end 数据结束迭代器
    /// \param OUTPUT d_sum 序列的和
    /// \param OUTPUT d_mean 序列的均值
    /// \param OUTPUT d_var 序列的方差
    /// \param OUTPUT d_std_var 序列的标准差
    /// \param OUTPUT d_skewness 序列的斜度
    /// \param OUTPUT d_kurtosis 序列的峭度
    ///
    template <typename IT> inline
    void get_statistics(INPUT const IT _begin,INPUT const IT _end
                       ,OUTPUT double& d_sum
                       ,OUTPUT double& d_mean
                       ,OUTPUT double& d_var
                       ,OUTPUT double& d_std_var
                       ,OUTPUT double& d_skewness
                       ,OUTPUT double& d_kurtosis)
    {
        size_t length = _end - _begin;
        IT it = _begin;
        double d(0.0),tmp(0.0);

        for(;it!=_end;++it){
            d += *it;
        }
        d_sum = d;
        //均值
        d_mean = d_sum / length;
        //方差
        for(d=0,it = _begin;it!=_end;++it)
        {
            d += ((d_mean - (*it)) * (d_mean - (*it)));
        }
        if(length>1)
            d_var = d/(length-1);//随机序列的方差要减去1
        else
            d_var = d/length;
        //标准差
        d_std_var = sqrt(d_var);
        //斜度,峭度
        double dk(0.0),tmp2(0.0);
        for(d=0,it = _begin;it!=_end;++it)
        {
            tmp = ((*it) - d_mean);
            tmp2 = tmp*tmp*tmp;
            d += tmp2;
            dk += tmp2*tmp;
        }
        d_skewness /= (length*d_std_var*d_std_var*d_std_var);
        d_kurtosis /= (length*d_var*d_var);
    }

    //////////////////////////////////////////////////////////////////////////
}
}


#endif // CZYMATH_H
