#ifndef CZYMATH_FIT_H
#define CZYMATH_FIT_H

#include <czyMath.h>
namespace gsl{
    #include <gsl/gsl_fit.h>
    #include <gsl/gsl_cdf.h>    /* 提供了 gammaq 函数 */
    #include <gsl/gsl_vector.h> /* 提供了向量结构*/
    #include <gsl/gsl_matrix.h>
    #include <gsl/gsl_multifit.h>
}

namespace czy {
///
/// \brief The Math class 用于处理简单数学计算
///
    namespace Math{
        using namespace gsl;
    ///
    /// \brief 拟合类，封装了gsl的拟合算法
    ///
    /// 实现线性拟合和多项式拟合
    ///
        class fit{
        public:
            fit(){}
            ~fit(){}
        private:
            std::map<double,double> m_factor;//记录各个点的系数，key中0是0次方，1是1次方，value是对应的系数
            std::map<double,double> m_err;
            double m_cov;//相关度
            double m_ssr;//回归平方和
            double m_sse;//(剩余平方和)
            double m_rmse;//RMSE均方根误差
            double m_wssr;
            double m_goodness;//基于wssr的拟合优度
            void clearAll(){
                m_factor.clear();m_err.clear();
            }
        public:
            //计算拟合的显著性
            static  void getDeterminateOfCoefficient(
                const double* y,const double* yi,size_t length
                ,double& out_ssr,double& out_sse,double& out_sst,double& out_rmse,double& out_RSquare)
            {
                double y_mean = mean(y,y+length);
                out_ssr = 0.0;
                for (size_t i =0;i<length;++i)
                {
                    out_ssr += ((yi[i]-y_mean)*(yi[i]-y_mean));
                    out_sse += ((y[i] - yi[i])*(y[i] - yi[i]));
                }
                out_sst = out_ssr + out_sse;
                out_rmse = sqrt(out_sse/(double(length)));
                out_RSquare = out_ssr/out_sst;
            }

            double getFactor(double n)
            {
                auto ite = m_factor.find(n);
                if (ite == m_factor.end())
                    return 0.0;
                return ite->second;
            }
            size_t getFactorSize()
            {
                return m_factor.size();
            }
            //直线拟合
            static int linearFit(
                const double *x       /* 数据点的横坐标值数组 */
                ,const size_t xstride  /* 横坐标值数组索引步长 xstride 与 ystride 的值设为 1，表示数据点集 {(xi,yi)|i=0,1,⋯,n−1} 全部参与直线的拟合；*/
                ,const double *y       /* 数据点的纵坐标值数组 */
                ,const size_t ystride  /* 纵坐标值数组索引步长 */
                ,size_t n              /* 数据点的数量 */
                ,double& out_intercept /* 计算的截距 */
                ,double& out_slope     /* 计算的斜率 */
                ,double& out_interceptErr /* 计算的截距误差 */
                ,double& out_slopeErr /* 计算的斜率误差 */
                ,double& out_cov /* 计算的斜率和截距的相关度 */
                ,double& out_wssr //拟合的wssr值
                )
            {
                return gsl_fit_linear(x,xstride,y,ystride,n
                    ,&out_intercept,&out_slope,&out_interceptErr,&out_slopeErr,&out_cov,&out_wssr);
            }
            bool linearFit(const double *x,const double *y,size_t n)
            {
                clearAll();
                m_factor[0]=0;m_err[0]=0;
                m_factor[1]=1;m_err[1]=0;
                int r = linearFit(x,1,y,1,n
                    ,m_factor[0],m_factor[1],m_err[0],m_err[1],m_cov,m_wssr);
                if (0 != r)
                    return false;
                m_goodness = gsl_cdf_chisq_Q(m_wssr/2.0,(n-2)/2.0);//计算优度
                {
                    std::vector<double> yi;
                    getYis(x,n,yi);
                    double t;
                    getDeterminateOfCoefficient(y,&yi[0],n,m_ssr,m_sse,t,m_rmse,t);
                }
                return true;
            }
            bool linearFit(const std::vector<double>& x,const std::vector<double>& y)
            {
                size_t n = x.size() > y.size() ? y.size() :x.size();
                return linearFit(&x[0],&y[0],n);
            }
            ///
            /// \brief 多项式拟合
            /// \param poly_n 阶次，如c0+C1x是1，若c0+c1x+c2x^2则poly_n是2
            static int polyfit(const double *x
                ,const double *y
                ,size_t xyLength
                ,unsigned poly_n
                ,std::vector<double>& out_factor
                ,double& out_chisq)//拟合曲线与数据点的优值函数最小值 ,χ2 检验
            {
                gsl_matrix *XX = gsl_matrix_alloc(xyLength, poly_n + 1);
                gsl_vector *c = gsl_vector_alloc(poly_n + 1);
                gsl_matrix *cov = gsl_matrix_alloc(poly_n + 1, poly_n + 1);
                gsl_vector *vY = gsl_vector_alloc(xyLength);

                for(size_t i = 0; i < xyLength; i++)
                {
                    gsl_matrix_set(XX, i, 0, 1.0);
                    gsl_vector_set (vY, i, y[i]);
                    for(long j = 1; j <= poly_n; j++)
                    {
                        gsl_matrix_set(XX, i, j, pow(x[i], j));
                    }
                }
                gsl_multifit_linear_workspace *workspace = gsl_multifit_linear_alloc(xyLength, poly_n + 1);
                int r = gsl_multifit_linear(XX, vY, c, cov, &out_chisq, workspace);
                gsl_multifit_linear_free(workspace);
                out_factor.resize(c->size,0);
                for (size_t i=0;i<c->size;++i)
                {
                    out_factor[i] = gsl_vector_get(c,i);
                }

                gsl_vector_free(vY);
                gsl_matrix_free(XX);
                gsl_matrix_free(cov);
                gsl_vector_free(c);

                return r;
            }
            bool polyfit(const double *x
                ,const double *y
                ,size_t xyLength
                ,unsigned poly_n)
            {
                double chisq;
                std::vector<double> factor;
                int r = polyfit(x,y,xyLength,poly_n,factor,chisq);
                if (0 != r)
                    return false;
                m_goodness = gsl_cdf_chisq_Q(chisq/2.0,(xyLength-2)/2.0);//计算优度

                clearAll();
                for (int i=0;i<poly_n+1;++i)
                {
                    m_factor[i]=factor[i];
                }
                std::vector<double> yi;
                getYis(x,xyLength,yi);
                double t;//由于没用到，所以都用t代替
                getDeterminateOfCoefficient(y,&yi[0],xyLength,m_ssr,m_sse,t,m_rmse,t);

                return true;
            }
            bool polyfit(const std::vector<double>& x
                         ,const std::vector<double>& y
                         ,unsigned plotN)
            {
                size_t n = x.size() > y.size() ? y.size() :x.size();
                return polyfit(&x[0],&y[0],n,plotN);
            }

            double getYi(double x) const
            {
                double ans(0);
                for (auto ite = m_factor.begin();ite != m_factor.end();++ite)
                {
                    ans += (ite->second)*pow(x,ite->first);
                }
                return ans;
            }
            void getYis(const double* x,size_t length,std::vector<double>& yis) const
            {
                yis.clear();
                yis.resize(length);
                for(size_t i=0;i<length;++i)
                {
                    yis[i] = getYi(x[i]);
                }
            }
            ///
            /// \brief 获取斜率
            /// \return 斜率值
            ///
            double getSlope() {return m_factor[1];}
            ///
            /// \brief 获取截距
            /// \return 截距值
            ///
            double getIntercept() {return m_factor[0];}

            ///
            /// \brief 回归平方和
            /// \return 回归平方和
            ///
            double getSSR() const {return m_ssr;}
            double getSSE() const {return m_sse;}
            double getSST() const {return m_ssr+m_sse;}
            double getRMSE() const {return m_rmse;}
            double getRSquare() const {return 1.0-(m_sse/(m_ssr+m_sse));}
            double getGoodness() const {return m_goodness;}
        };
    }
}
#endif // CZYMATH_FIT_H
