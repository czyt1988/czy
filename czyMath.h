#ifndef CZYMATH_H
#define CZYMATH_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <functional>
#include <math.h>
#include <memory>

namespace czy{
#ifndef INPUT
#define INPUT
#endif

#ifndef OUTPUT
#define OUTPUT
#endif
    ///
    /// \brief The Math namespace 用于处理简单数学计算
    ///
    namespace Math
    {

        const double PI = 3.1415926535897932384626;
        const double PI2 = 6.2831853071795864769252;

//        ///
//        /// \brief 判断一个数字是否是2的n次幂
//        /// \param 如果该数字为2的n次幂则返回true，否则返回false
//        /// \return
//        ///
//        bool IsPowOfTwo(size_t num)
//        {
//            return !(num &(num-1));
//        }
        ///
        /// \brief 对数组求和
        /// \param pArr 需要求解的数组指针
        /// \param length 指针长度
        ///
        template <typename T>
        double Sum(const T* pArr,size_t length)
        {
            double total(0.0);
            for(size_t i(0);i<length;++i){
                total += pArr[i];
            }
            return total;
        }
        ///
        /// \brief 对数组求和 形式为vector
        ///
        template <typename T>
        double Sum(const std::vector<T>& v)
        {
            double total(0.0);
            auto iteEnd = v.end();
            for(auto ite = v.begin();ite != iteEnd;++ite){
                total += (*ite);
            }
            return total;
        }
        ///
        /// \brief 求平均值的模版函数
        /// \param pArr 需要求解的数组指针
        /// \param length 指针长度
        ///
        template <typename T>
        double Mean(const T* pArr,size_t length)
        {
            return Sum(pArr,length)/length;
        }
        ///
        /// \brief 求vector元素的平均值
        /// \param v 需要求解均值的vector
        /// 例如：double avx = czy::Math::Mean<double>(x);其中x是个vector<double>
        ///
        template <typename T>
        double Mean(const std::vector<T>& v)
        {
            return Mean<T>(&v[0],v.size());
        }
        ///
        /// \brief 求序列的方差 - 为n-1类型既是序列是随机抽样不是固定值
        /// \param pArr 需要求解的数组指针
        /// \param length 指针长度
        ///
        template <typename T>
        double Var(const T* pArr,size_t length)
        {
            double mean = Math::Mean(pArr,length);
            double var(0);
            for(size_t i(0);i<length;++i)
            {
                var += (mean - pArr[i]) * (mean - pArr[i]);
            }
            if(length>1)
                length -= 1;//随机序列的方差要减去1
            return var/length;
        }
        template <typename T>
        double Var(const std::vector<T>& v)
        {
            return Var<T>(&v[0],v.size());
        }
        ///
        /// \brief 求序列的标准差 - 为n-1类型既是序列是随机抽样不是固定值
        /// \param pArr 需要求解的数组指针
        /// \param length 指针长度
        ///
        template <typename T>
        double StdVar(const T* pArr,size_t length)
        {
            double var = Var(pArr,length);
            return sqrt(var);
        }
        template <typename T>
        double StdVar(const std::vector<T>& v)
        {
            return StdVar<T>(&v[0],v.size());
        }
        ///
        /// \brief 求序列的斜度 - 3次矩
        /// \param pArr 需要求解的数组指针
        /// \param length 指针长度
        ///
        template <typename T>
        double Skewness(const T* pArr,size_t length)
        {
            double s = StdVar(pArr,length);
            double m = Mean(pArr,length);
            double tmp(0),res(0);
            for(size_t i(0);i<length;++i)
            {
                tmp = (pArr[i] - m);
                res += (tmp*tmp*tmp);
            }
            res /= (length*s*s*s);
            return res;
        }
        template <typename T>
        double Skewness(const std::vector<T>& v)
        {
            return Skewness<T>(&v[0],v.size());
        }
        ///
        /// \brief 求序列的峰度(峭度) - 4次矩
        /// \param pArr 需要求解的数组指针
        /// \param length 指针长度
        ///
        template <typename T>
        double Kurtosis(const T* pArr,size_t length)
        {
            double v = Var(pArr,length);
            double m = Mean(pArr,length);
            double tmp(0),res(0);
            for(size_t i(0);i<length;++i)
            {
                tmp = (pArr[i] - m);
                res += (tmp*tmp*tmp*tmp);
            }
            res /= (length*v*v);
            return res;
        }
        template <typename T>
        double Kurtosis(const std::vector<T>& v)
        {
            return Kurtosis<T>(&v[0],v.size());
        }
        ///
        /// \brief 获取统计参数，包括和，均值，方差，标准差，斜度，峭度
        ///
        template <typename T>
        void GetStatistics(const T* pArr,size_t length
                           ,double& sum,double& mean,double& var,double& stdVar,double& skewness,double& kurtosis)
        {
            for(size_t i(0);i<length;++i){
                sum += pArr[i];
            }
            mean = sum / length;
            for(size_t i(0);i<length;++i)
            {
                var += (mean - pArr[i]) * (mean - pArr[i]);
            }
            length>1 ? var /= (length-1) : var /= length;
            stdVar = sqrt(var);
            double tmp(0);
            for(size_t i(0);i<length;++i)
            {
                tmp = (pArr[i] - mean);
                skewness += tmp*tmp*tmp;
            }
            skewness /= length*stdVar*stdVar*stdVar;
            for(size_t i(0);i<length;++i)
            {
                tmp = (pArr[i] - mean);
                kurtosis += tmp*tmp*tmp*tmp;
            }
            kurtosis /= length*var*var;
        }
        template <typename T>
        void GetStatistics(const std::vector<T>& v
                           ,double& sum,double& mean,double& var,double& stdVar,double& skewness,double& kurtosis)
        {
            return GetStatistics<T>(&v[0],v.size(),sum,mean,var,stdVar,skewness,kurtosis);
        }

		//////////////////////////////////////////////////////////////////////////
    }
}


#endif // CZYMATH_H
