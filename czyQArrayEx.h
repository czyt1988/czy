/*Qt 数组扩展
 *日期：2014-02-05
 *作者：尘中远
 *email：czy.t@163.com
 *blog:http://blog.csdn.net/czyt1988
 */

#ifndef CZY_QARRAYEX_H
#define CZY_QARRAYEX_H
#include <QVector>
#include <QStringList>
#include <QVariant>
#include <QPointF>
#include <QDebug>
#include <math.h>
namespace czy
{
	class QArrayEx
	{
	public:
		QArrayEx(){

		}
		///
		/// \brief 把qZr数组转换为QStringList,前提是类型可转换
		/// \param v qvector数组
		/// \return 转换后的数组
		///
		template<typename T>
		static QStringList Vector2StringList(const QVector<T>& v)
		{
			QStringList strL;
			strL.reserve(v.size());
			auto ite = v.begin();
			for(;ite != v.end();++ite)
			{
				strL.append(QStringLiteral("%1").arg(*ite));
			}
			return strL;
		}
		///
		/// \brief 把qvector<任意类型>数组转换为QVector<QVariant>,前提是类型可转换
		/// \param input_v qvector<任意类型>数组
		/// \return 转换后的QVector<QVariant>数组
		///
		///如果类型是自定义类型，需要用宏Q_DECLARE_METATYPE告知QMetaType
		///struct MyStructZ
		///{
		///   int i;
		///   ...
		///};
		///
		///Q_DECLARE_METATYPE(MyStruct)
		///
		template<typename T>
		static QVector<QVariant> VectorType2VectorVariant(const QVector<T>& input_v)
		{
			QVector<QVariant> datas;
			datas.reserve(input_v.size());
			for(auto ite = input_v.begin();ite != input_v.end();++ite)
			{
				datas.append(QVariant::fromValue(*ite));
			}
			return datas;
		}
		///
		/// \brief 把QVector<QVariant>转换为qvector<任意类型>数组,前提是类型可转换
		/// \param input_v qvector<任意类型>数组
		/// \return 转换后的QVector<QVariant>数组
		///
		template<typename T>
		static QVector<T> VectorVariant2VectorType(const QVector<QVariant>& input_v)
		{
			QVector<T> datas;
			datas.reserve(input_v.size());
			for(QVector<QVariant>::const_iterator ite = input_v.begin();ite != input_v.end();++ite)
			{
				datas.append(ite->value<T>());
			}
			return datas;
		}
		///
		/// \brief 把QVector<QPointF>的X序列提取
		/// \param in_Points qvector<QPointF>数组
		/// \return 获取QVector<Double>数组
		///
		static QVector<double> getVectPointFX(const QVector<QPointF>& in_Points)
		{
			QVector<double> datas;
			datas.reserve(in_Points.size());
			for(auto ite = in_Points.begin();ite != in_Points.end();++ite)
			{
				datas.append(ite->x());
			}
			return datas;
		}
		static QVector<double> getVectPointFY(const QVector<QPointF>& in_Points)
		{
			QVector<double> datas;
			datas.reserve(in_Points.size());
			for(auto ite = in_Points.begin();ite != in_Points.end();++ite)
			{
				datas.append(ite->y());
			}
			return datas;
		}
		///
		/// \brief 把两个QVector<double>的序列转换为QVector<QPointF>
		/// \param x x序列
		/// \param y y序列
		/// \return 转换的QVector<QPointF>数组
		///
		static QVector<QPointF> toVectPointF(const QVector<double>& x,const QVector<double>& y)
		{
			size_t count = x.size() > y.size() ? y.size() : x.size();
			QVector<QPointF> datas;
			datas.reserve(count);
			for(auto i=0;i<count;++i)
			{
				datas.append(QPointF(x[i],y[i]));
			}
			return datas;
		}
		/// 未验证
		template<typename A,typename B>
		static QVector<B> static_cast_VectorA2VectorB(const QVector<A> input_A_beCasted)
		{
            QVector<B> dataB;
			dataB.reserve(input_A_beCasted.size());
			auto ite_end = input_A_beCasted.end();
			for (auto ite = input_A_beCasted.begin();ite != ite_end;++ite)
			{
                dataB.append(static_cast<B>(*ite));
			}
			return dataB;
		}

		template<typename A,typename B>
		static void static_cast_VectorA2VectorB(const QVector<A>& input_A_beCasted,QVector<B>& output_B)
		{
			output_B.resize(input_A_beCasted.size());
			auto count = input_A_beCasted.size();
			for (auto i=0;i<count;++i)
			{
                output_B[i] = static_cast<B>(input_A_beCasted[i]);
			}
		}
		/// 
		/// \brief 一个向量除以常数
		/// 
		/// vector<left>/beDivise
		/// \param left 除数
		/// \param right 被除数
		/// \return 返回结果
		///
		template<typename T>
		static QVector<T> division(const QVector<T>& divisor,const T& beDivise)
		{
            QVector<T> res;
			res.reserve(divisor.size());
			for (auto ite = divisor.begin();ite != divisor.end();++ite)
			{
				res.append( (*ite) /beDivise);
			}
			return res;
		}
		/// 
		/// \brief 一个向量除以另外一个向量
		/// 
		/// vector<left>/vector<right>
		/// \param left 除数
		/// \param right 被除数
		/// \return 返回结果
		///
		template<typename T>
		static QVector<T> division(const QVector<T>& left,const QVector<T>& right)
		{
            QVector<T> res;
			size_t minSize = left.size() > right.size() ? right.size() : left.size();
			res.reserve(minSize);
			for (size_t i=0;i<minSize;++i)
			{
				res.append(left[i] / right[i]);
			}
			return res;
		}
		/// 
		/// \brief 一个向量加常数
		/// 
		/// vactor<adder>+data
		/// \param adder 向量
		/// \param data 常数
		/// \return 返回结果
		///
		template<typename T>
		static QVector<T> add(const QVector<T>& adder,const T& data)
		{
            QVector<T> res;
			res.reserve(adder.size());
			for (auto ite = adder.begin();ite != adder.end();++ite)
			{
				res.append( (*ite) + data);
			}
			return res;
		}
		/// 
		/// \brief 一个向量乘以常数
		/// 
		/// vactor<a>*b
		/// \param a 向量
		/// \param b 常数
		/// \return 返回结果
		///
		template<typename T>
		static QVector<T> multiply(const QVector<T>& a,const T& b)
		{
            QVector<T> res;
			res.reserve(a.size());
			for (auto ite = a.begin();ite != a.end();++ite)
			{
				res.append( (*ite) * b);
			}
			return res;
		}
		/// 
		/// \brief 一个向量乘以另一个向量
		/// 
		/// vactor<a>*b
		/// \param a 向量
		/// \param b 常数
		/// \return 返回结果
		///
		template<typename T>
		static QVector<T> multiply(const QVector<T>& a,const QVector<T>& b)
		{
            QVector<T> res;
			size_t minSize = a.size() > b.size() ? b.size() : a.size();
			res.reserve(minSize);
			for (size_t i=0;i<minSize;++i)
			{
				res.append(a[i] * b[i]);
			}
			return res;
		}
		/// 
		/// \brief 对向量里的每个数值求取log
		/// 
		/// log(vactor<a>)
		/// \param a 向量
		/// \return 返回结果
		///
		template<typename T>
		static QVector<T> log(const QVector<T>& a)
		{
            QVector<T> res;
			res.reserve(a.size());
			for (auto ite = a.begin();ite != a.end();++ite)
			{
				res.append( log(*ite) );
			}
			return res;
		}
        ///
        /// \brief 把x,y序列组合成point数组
        /// \param x 向量
        /// \param y 向量
        ///
        template<typename T>
        static QVector<QPointF> makePointArray(const QVector<T>&x,const QVector<T>&y)
        {
            QVector<QPointF> f;
            size_t min = qMin(x.size(),y.size());
            f.reserve(min);
            for(size_t i=0;i<min;++i)
            {
                f.push_back(QPointF(x[i],y[i]));
            }
            return f;
        }
	};
}


#endif // QMYARRAYEX_H
