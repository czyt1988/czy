//////////////////////////////////////////////////////////////////////////
///创建时间-2012-4-1
///创件人：尘中远
///库名：数字信号处理的数学方法库
///参考库：SP++、itpp-4.2
///引用库：fftw
///必须包含fftw3.h，libfftw3-3.lib，libfftw3-3.dll
//////////////////////////////////////////////////////////////////////////
//verson 1.1
//////////////////////////////////////////////////////////////////////////
#ifndef DSP_MATH_H
#define DSP_MATH_H

namespace czy {
namespace Math {
    class DSP
    {
    public:
        DSP(void);
        ~DSP(void);
    public:
        //辅助函数
        //判断是否是2的基次
        //算法来着sp++3.0
        static bool isPower2( int n );
    public:
        enum {WINDOW_NO = 1,WINDOW_HANNING = 2,WINDOW_HAMMING = 3,WINDOW_BLACKMAN = 4,WINDOW_BARTLETT = 5 };
        static void windowed( double *x, int n, int windowflag );
        //==========================================================================
        //傅里叶变换相关
        //////////////////////////////////////////////////////////////////////////
        //快速傅里叶变换//长度无要求
        static void FFT(double* pRealData,double* pImageData,int nNumCount);
        //逆傅里叶变换//长度无要求
        static void IFFT(double* pRealData,double* pImageData,int nNumCount);
        //实傅里叶变换，实数变换后为复数
        //pRealData实数部分，同时也是实数传进去的部分，之后将作为实部
        //real to complex
        static void FFT_RealToComplex(double* pRealData,double* pImageData,int nNumCount);
        //实傅里叶变换，实数变换后为复数的重载
        //pOrignData为原始的数据--输出实部虚部，pOrignData和pRealData可相同，这时作用和第一个DFT函数一样
        static void FFT_RealToComplex(double* pOrignData,double* pRealData,double* pImageData,int nNumCount);


        // 数组延长补0
        //int ZeroExternLength(double* pOrign, unsigned int nOrignLength, double* pResult, unsigned int nExternLength);
    public:
        ///<summary>频谱分析</summary>
        ///<para name = "pOrignData">原始数据，波形幅值</para>
        ///<para name = "pXValue">变换结果的x值</para>
        ///<para name = "pYValue">变换结果的y值,x值和y值绘图就是频谱</para>
        ///<para name = "nDataNum">数据长度</para>
        ///<para name = "nSampleRate">采样频率</para>
        ///<return>频谱分析后实际的有用长度</return>
        static int DSP_FrequencySpectrum(double *pOrignData
            , double * pXValue
            , double * pYValue
            , int nDataNum
            , int nSampleRate
            );
        ///<summary>频谱分析</summary>
        ///<para name = "pXValue">变换结果的x值</para>
        ///<para name = "pYValueAndInputData">变换结果的y值,同时也作为原始输入数据</para>
        ///<para name = "nDataNum">数据长度</para>
        ///<para name = "nSampleRate">采样频率</para>
        ///<return>频谱分析后实际的有用长度</return>
        static int DSP_FrequencySpectrum(
            double* pXValue
            , double* pYValueAndInputData
            , int nDataNum
            , int nSampleRate
            );
        ///<summary>功率谱分析</summary>
        ///<para name = "pOrignData">原始数据，波形幅值</para>
        ///<para name = "pXValue">变换结果的x值</para>
        ///<para name = "pYValue">变换结果的y值,x值和y值绘图就是频谱</para>
        ///<para name = "nDataNum">数据长度</para>
        ///<para name = "nSampleRate">采样频率</para>
        ///<return>功率谱分析后实际的有用长度</return>
        static int DSP_PowerSpectrum(
            double * pOrignData
            , double * pXValue
            , double * pYValue
            , int nDataNum
            , int nSampleRate
            );
        ///<summary>功率谱分析</summary>
        ///<para name = "pXValue">变换结果的x值</para>
        ///<para name = "pYValueAndInputData">变换结果的y值,同时也作为原始输入数据</para>
        ///<para name = "nDataNum">数据长度</para>
        ///<para name = "nSampleRate">采样频率</para>
        ///<return>功率谱分析后实际的有用长度</return>
        static int DSP_PowerSpectrum(
            double* pXValue
            , double* pYValueAndInputData
            , int nDataNum
            , int nSampleRate
            );
    };
}
}


#endif

