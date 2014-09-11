

#include "czyMath_DSP.h"
#include "fftw3.h"
#include <math.h>
#include <memory>
#include <memory.h>
#ifndef TWOPI
#define TWOPI 6.2831853
#endif
#ifndef PI
#define PI 3.14159265
#endif


czy::Math::DSP::DSP(void)
{
}


czy::Math::DSP::~DSP(void)
{
}

//=============================================================================
//判断是否是2的基次
//算法来着sp++3.0
bool czy::Math::DSP::isPower2( int n )
{
	int bits = 0;
	while( n )
	{
		bits += n & 1;
		n >>= 1;
	}
	return ( bits == 1 );
}

//=============================================================================
//WINDOWFLAG=1     no window or rectangle window
//WINDOWFLAG=2     hanning window                  
//WINDOWFLAG=3     hamming window                  
//WINDOWFLAG=4     blackman window   
//WINDOWFLAG=5     bartlett window
void czy::Math::DSP::windowed( double *x, int n, int windowflag )
{   
	double  multiplier;
	int i;

	switch(windowflag)
	{   
	case WINDOW_NO:
		break;
	case WINDOW_HANNING://hanning window
		for(i=0;i<n;i++)
		{  
			multiplier=(double)(0.5-0.5*cos(TWOPI*i/(n-1)));
			x[i]*=multiplier;
		}
		break;
	case WINDOW_HAMMING://hamming window
		for(i=0;i<n;i++)
		{  
			multiplier=(double)(0.54-0.46*cos(TWOPI*i/(n-1)));
			x[i]*=multiplier;
		}
		break;
	case WINDOW_BLACKMAN://blackman window
		for(i=0;i<n;i++)
		{  
			multiplier=(double)(0.42-0.5*cos(TWOPI*i/(n-1))+0.08*cos(4*PI*i/(n-1)));
			x[i]*=multiplier;
		}
		break;
	case WINDOW_BARTLETT://bartlett window
		for(i=0;i<(n+1)/2;i++)
		{  
			multiplier = (double)(2*(double)i)/((double)n-1);
			x[i]*=multiplier;
			x[n-1-i]*=multiplier;
		}
		break;
	}
}

//=============================================================================
//快速傅里叶变换，属于ComplexToComplex,只要pImageData 全部等于0既是DFT
void czy::Math::DSP::FFT(double* pRealData,double* pImageData,int nNumCount)
{
	int i(0);
	fftw_complex *pOutPut;     
	fftw_complex *pInPut;
	pOutPut = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * nNumCount);
	pInPut = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * nNumCount);
	//转移数据
	for (i=0;i<nNumCount;i++)
	{
		pInPut[i][0] = pRealData[i];
		pInPut[i][1] = pImageData[i];
	}
	//创建方案
	fftw_plan fftplan = fftw_plan_dft_1d(nNumCount,pInPut,pOutPut,FFTW_FORWARD,FFTW_ESTIMATE);
	//执行
	fftw_execute( fftplan );
	//数据转移回去
	for (i=0;i<nNumCount;i++)
	{
		pRealData[i] = pInPut[i][0];
		pImageData[i] = pInPut[i][1];
	}
	fftw_destroy_plan( fftplan );
	fftw_free(pOutPut );//fftw_destroy_plan之后不调用fftw_free也没检测到内存泄露，可能fftw里面用的是智能指针,或者destroy时就释放了
	fftw_free(pInPut );
}

//=============================================================================
//逆傅里叶变换
void czy::Math::DSP::IFFT(double* pRealData,double* pImageData,int nNumCount)
{
	int i(0);
	fftw_complex *pOutPut;     
	fftw_complex *pInPut;
	pOutPut = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * nNumCount);
	pInPut = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * nNumCount);
	//转移数据
	for (i=0;i<nNumCount;i++)
	{
		pInPut[i][0] = pRealData[i];
		pInPut[i][1] = pImageData[i];
	}
	//创建方案
	fftw_plan fftplan = fftw_plan_dft_1d(nNumCount,pInPut,pOutPut,FFTW_BACKWARD,FFTW_ESTIMATE);
	//执行
	fftw_execute( fftplan );
	//数据转移回去--
	//由于fftw的逆傅里叶变换都是大了nNumCount倍，所以是要除回去
	for (i=0;i<nNumCount;i++)
	{
		pRealData[i] = pInPut[i][0]/nNumCount;
		pImageData[i] = pInPut[i][1]/nNumCount;
	}
	fftw_destroy_plan( fftplan );
	fftw_free(pOutPut );//fftw_destroy_plan之后不调用fftw_free也没检测到内存泄露，可能fftw里面用的是智能指针,或者destroy时就释放了
	fftw_free(pInPut );
}

//=============================================================================
//实傅里叶变换，实数变换后为复数
//pRealData实数部分，同时也是实数传进去的部分，之后将作为实部
void czy::Math::DSP::FFT_RealToComplex(double* pRealData,double* pImageData,int nNumCount)
{
	int i(0);
	//傅里叶变化方案
	fftw_complex *pOutPut;
	fftw_plan fftplan;
	//为复数分配内存
	pOutPut = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * nNumCount);
	//实数到复数的傅里叶变化
	fftplan = fftw_plan_dft_r2c_1d(nNumCount,pRealData,pOutPut,FFTW_ESTIMATE);
	//执行
	fftw_execute( fftplan );
	//转移数据
	for (i=0;i<nNumCount;i++)
	{
		pRealData[i] = pOutPut[i][0];
		pImageData[i] = pOutPut[i][1];
	}
	//释放内存
	fftw_destroy_plan( fftplan );
}

//=============================================================================
//实傅里叶变换，实数变换后为复数的重载
//pOrignData为原始的数据--输出实部虚部，pOrignData和pRealData可相同，这时作用和第一个DFT函数一样
void czy::Math::DSP::FFT_RealToComplex(double* pOrignData,double* pRealData,double* pImageData,int nNumCount)
{
	int i(0);
	//傅里叶变化方案
	fftw_complex *pOutPut;
	fftw_plan fftplan;
	//为复数分配内存
	pOutPut = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * nNumCount);
	//实数到复数的傅里叶变化
	fftplan = fftw_plan_dft_r2c_1d(nNumCount,pOrignData,pOutPut,FFTW_ESTIMATE);
	//执行
	fftw_execute( fftplan );
	//转移数据
    for (i=0;i<nNumCount;++i)
	{
		pRealData[i] = pOutPut[i][0];
		pImageData[i] = pOutPut[i][1];
	}
	//释放内存
	fftw_destroy_plan( fftplan );
}

//////////////////////////////////////////////////////////////////////////

///
/// \brief 频谱分析
/// \param pOrignData 原始数据，波形幅值,不会改动
/// \param pXValue 变换结果的x值,会改变其内容
/// \param pYValue 变换结果的y值,x值和y值绘图就是频谱
/// \param nDataNum 数据长度
/// \param nSampleRate 采样频率
/// \return 频谱分析后实际的有用长度
///
int czy::Math::DSP::DSP_FrequencySpectrum(
    double * pOrignData
	, double * pXValue 
	, double * pYValue 
	, int nDataNum
	, int nSampleRate
	)
{
    int nRealData = (unsigned int)floor((double)(nDataNum/2));
	memset(pXValue,0,nDataNum*sizeof(double));//借用pXValue做原始数据虚部
	FFT_RealToComplex(pOrignData,pYValue,pXValue,nDataNum );
    for (int i=0;i<nRealData;++i)
	{
		pYValue[i]=sqrt((pYValue[i]*pYValue[i])+(pXValue[i]*pXValue[i]))*2/nDataNum;//pYValue为幅值
        pXValue[i]=((double(i)*double(nSampleRate)))/((double)nDataNum);
	}
	return nRealData;
}

///<summary>频谱分析</summary>
///<para name = "pXValue">变换结果的x值</para>
///<para name = "pYValueAndInputData">变换结果的y值,同时也作为原始输入数据</para>
///<para name = "nDataNum">数据长度</para>
///<para name = "nSampleRate">采样频率</para>
///<return>频谱分析后实际的有用长度</return>
int czy::Math::DSP::DSP_FrequencySpectrum(
	double* pXValue 
	, double* pYValueAndInputData
	, int nDataNum
	, int nSampleRate
	)
{
    int nRealData = (unsigned int)floor((double)(nDataNum/2));
	memset(pXValue,0,nDataNum*sizeof(double));//借用pXValue做原始数据虚部
	FFT_RealToComplex(pYValueAndInputData,pXValue,nDataNum);
	for (int i=0;i<nDataNum && i<nRealData;i++)
	{
		pYValueAndInputData[i]=sqrt((pYValueAndInputData[i]*pYValueAndInputData[i])+(pXValue[i]*pXValue[i]))*2.0/(double)nDataNum;//pYValue为幅值
        pXValue[i]=((double(i)*double(nSampleRate)))/((double)nDataNum);
	}

	return nRealData;
}

///<summary>功率谱分析</summary>
///<para name = "pOrignData">原始数据，波形幅值</para>
///<para name = "pXValue">变换结果的x值</para>
///<para name = "pYValue">变换结果的y值,x值和y值绘图就是频谱</para>
///<para name = "nDataNum">数据长度</para>
///<para name = "nSampleRate">采样频率</para>
///<return>功率谱分析后实际的有用长度</return>
int czy::Math::DSP::DSP_PowerSpectrum(double *pOrignData
    , double * pXValue
    , double * pYValue
    , int nDataNum
    , int nSampleRate
    )
{
    int nRealData = (unsigned int)floor((double)(nDataNum/2));
	memset(pXValue,0,nDataNum*sizeof(double));//借用pXValue做原始数据虚部
	FFT_RealToComplex(pOrignData,pYValue,pXValue,nDataNum );
    for (int i=0;i<nRealData;i++)
	{
        pYValue[i]=((pYValue[i]*pYValue[i]+pXValue[i]*pXValue[i])*4) / (nDataNum*nDataNum);
        pYValue[i]=10*log10(pYValue[i]);//pYValue为幅值
        pXValue[i]=((double(i)*double(nSampleRate)))/((double)nDataNum);
	}
	return nRealData;
}

///<summary>功率谱分析</summary>
///<para name = "pXValue">变换结果的x值</para>
///<para name = "pYValueAndInputData">变换结果的y值,同时也作为原始输入数据</para>
///<para name = "nDataNum">数据长度</para>
///<para name = "nSampleRate">采样频率</para>
///<return>功率谱分析后实际的有用长度</return>
int czy::Math::DSP::DSP_PowerSpectrum(
	double* pXValue 
	, double* pYValueAndInputData
	, int nDataNum
	, int nSampleRate
	)
{
    int nRealData = (unsigned int)floor((double)(nDataNum/2));
	memset(pXValue,0,nDataNum*sizeof(double));//借用pXValue做原始数据虚部
	FFT_RealToComplex(pYValueAndInputData,pXValue,nDataNum);
    for (int i=0;i<nRealData;i++)
	{
        pYValueAndInputData[i]=((pYValueAndInputData[i]*pYValueAndInputData[i]+pXValue[i]*pXValue[i])*4);
        pYValueAndInputData[i]/=(nDataNum*nDataNum);
        pYValueAndInputData[i]=10*log10(pYValueAndInputData[i]);//pYValue为幅值
        pXValue[i]=((double(i)*double(nSampleRate)))/((double)nDataNum);
	}
	return nRealData;
}
