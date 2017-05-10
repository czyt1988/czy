#ifndef CZYMATH_IMPL_H
#define CZYMATH_IMPL_H




template <typename IT> 
double czy::Math::sum(INPUT const IT _begin,INPUT const IT _end)
{
    IT it = _begin;
    double total(0.0);
    for(;it!=_end;++it){
        total += *it;
    }
    return total;
}

template <typename IT>
double czy::Math::mean(INPUT const IT _begin,INPUT const IT _end)
{
    return sum(_begin,_end)/(_end - _begin);
}

template <typename IT>
double czy::Math::var(INPUT const IT _begin,INPUT const IT _end)
{
    double m = Math::mean(_begin,_end);
    double d(0);
    IT it = _begin;
    for(;it!=_end;++it)
    {
        d += ((m - (*it)) * (m - (*it)));
    }
    size_t length = std::distance(_begin,_end);
    if(length>1)
        length -= 1;//随机序列的方差要减去1
    return d/length;
}

template <typename IT>
double czy::Math::std_var(INPUT const IT _begin,INPUT const IT _end)
{
    double v = var(_begin,_end);
    return sqrt(v);
}

template <typename IT>
double czy::Math::central_moment(INPUT const IT _begin,INPUT const IT _end,INPUT unsigned order)
{
    double m = mean(_begin,_end);
    double tmp(0),res(0);
    size_t length = _end - _begin;
    for(IT it = _begin;it!=_end;++it)
    {
        tmp = ((*it) - m);
        res += pow(tmp,int(order));
    }
    res /= length;
    return res;
}

template <typename IT>
double czy::Math::origin_moment(INPUT const IT _begin,INPUT const IT _end,INPUT unsigned order)
{
    double res(0);
    size_t length = _end - _begin;
    for(IT it = _begin;it!=_end;++it)
    {
        res += pow(*it,int(order));
    }
    res /= length;
    return res;
}

template <typename IT>
double czy::Math::skewness(INPUT const IT _begin,INPUT const IT _end)
{
    double s = std_var(_begin,_end);
    double res = central_moment(_begin,_end,3);//先求3阶中心距
    res /= (s*s*s);
    return res;
}

template <typename IT>
double czy::Math::kurtosis(INPUT const IT _begin,INPUT const IT _end)
{
    double v = var(_begin,_end);
    double res = central_moment(_begin,_end,4);//先求4阶中心距
    res /= (v*v);
    return res;
}

template <typename IT>
double czy::Math::peak_to_peak_value(INPUT const IT _begin,INPUT const IT _end)
{
    auto minmax = std::minmax_element(_begin,_end);
    return double(*minmax.second - *minmax.first);
    //return (*std::max_element(_begin,_end) - *std::min_element(_begin,_end));
}

template <typename IT>
void czy::Math::get_statistics(INPUT const IT _begin,INPUT const IT _end
                   ,OUTPUT double& d_sum
                   ,OUTPUT double& d_mean
                   ,OUTPUT double& d_var
                   ,OUTPUT double& d_std_var
                   ,OUTPUT double& d_skewness
                   ,OUTPUT double& d_kurtosis)
{
    size_t length = std::distance(_begin,_end);
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

template <typename IT>
double czy::Math::sub_mean(IN_OUTPUT IT _begin,IN_OUTPUT IT _end)
{
    double m = mean<IT>(_begin,_end);
    for(IT i=_begin;i!=_end;++i)
    {
        (*i) = ((*i) - m);
    }
    return m;
}


template <typename InputIterator,typename OutputIterator>
void czy::Math::get_out_n_sigma_rang(INPUT InputIterator _begin,INPUT InputIterator _end,double n
                          ,OUTPUT OutputIterator outIndexBegin,size_t indexStart = 0)
{
    double v = std_var(_begin,_end);//计算sigma
    double m = mean(_begin,_end);
    double min = m - n*v;
    double max = m + n*v;
    while(_begin!=_end)
    {
        if((*_begin) > max || (*_begin) < min)
        {
            (*outIndexBegin) = (indexStart);
            ++outIndexBegin;
        }
        ++_begin;
        ++indexStart;
    }
}

template <typename InputIterator,typename OutputIterator>
void czy::Math::get_n_sigma_rang(INPUT InputIterator _begin,INPUT InputIterator _end,double n
                          ,OUTPUT OutputIterator outIndexBegin
                          ,OUTPUT OutputIterator innerIndexBegin,size_t indexStart = 0)
{
    double v = std_var(_begin,_end);//计算sigma
    double m = mean(_begin,_end);
    double min = m - n*v;
    double max = m + n*v;
    while(_begin!=_end)
    {
        if((*_begin) > max || (*_begin) < min)
        {
            (*outIndexBegin) = (indexStart);
            ++outIndexBegin;
        }
        else
        {
            (*innerIndexBegin) = (indexStart);
            ++innerIndexBegin;
        }
        ++_begin;
        ++indexStart;
    }
}

template <typename IT,typename IT2>
size_t czy::Math::difference(INPUT IT in_begin,INPUT IT in_end,OUTPUT IT2 out_begin)
{
    size_t count = 0;
    IT j=in_begin;
    IT2 r = out_begin;
    IT j_end = (in_end-1);
    for(;j != j_end;++j,++r)
    {
        (*r) = (*(j+1)) - (*(j));
        ++count;
    }
    return count;
}

template <typename IT,typename IT2>
size_t czy::Math::difference(INPUT IT in_begin,INPUT IT in_end,OUTPUT IT2 out_begin,unsigned n)
{
    size_t count = 0;
    for(unsigned i=0;i<n;++i)
    {
        count = difference(in_begin,in_end,out_begin);
    }
    return count;
}

template <typename IT,typename DATA_TYPE>
size_t czy::Math::count_frequency(INPUT IT in_begin,INPUT IT in_end,OUTPUT std::map<DATA_TYPE,size_t>& res)
{

    typename std::map<DATA_TYPE,size_t>::iterator res_i = res.end ();
    size_t c=0;
    for(IT i = in_begin;i!=in_end;++i)
    {
         res_i = res.find (*i);
         if(res_i != res.end ())
             ++(res_i->second);
         else
         {
             ++c;
            res[*i] = 1;
         }
    }
    return c;
}

template <typename IT_INPUT,typename IT_OUTPUT1,typename IT_OUTPUT2>
void czy::Math::count_frequency(INPUT IT_INPUT in_begin
                       ,INPUT IT_INPUT in_end
                       ,size_t section
                       ,OUTPUT IT_OUTPUT1 sectionRange_begin
                       ,OUTPUT IT_OUTPUT2 frequencyCount_begin)
{
    IT_INPUT ite_pp = std::minmax_element(in_begin,in_end);
    const double detal = double(*ite_pp.second-*ite_pp.first)/double(section);
    *sectionRange_begin = *ite_pp.first;
    IT_OUTPUT1 sectionIte=sectionRange_begin;
    //typedef std::iterator_traits<typename IT_OUTPUT1>::value_type VT1;
    double last=0;
    for(size_t i=0;i<section;++i)
    {//计算各段
        last = *sectionIte;
        ++sectionIte;
        *sectionIte = last+detal;
    }
    IT_OUTPUT1 sectionEnd=sectionIte+1;
    for(IT_INPUT i = in_begin;i!=in_end;++i)
    {
        sectionIte = std::lower_bound(sectionRange_begin,sectionEnd,*i);
        if(sectionIte!=sectionEnd)
        {
            size_t dis = std::distance(sectionRange_begin,sectionIte);
            if(dis<section)
                ++(*(frequencyCount_begin+dis));
        }
    }
}

template <typename IT_INPUT,typename VALUE_TYPE>
void czy::Math::clip(INPUT IT_INPUT in_begin,INPUT IT_INPUT in_end,VALUE_TYPE min,VALUE_TYPE max)
{
    for(;in_begin != in_end;++in_begin)
    {
        if(*in_begin<min)
            *in_begin = min;
        else if(*in_begin>max)
            *in_begin = max;
    }
}

template <typename IT_INPUT,typename VALUE_TYPE>
void czy::Math::clip_bottom(INPUT IT_INPUT in_begin,INPUT IT_INPUT in_end,VALUE_TYPE min)
{
    for(;in_begin != in_end;++in_begin)
    {
        if(*in_begin<min)
            *in_begin = min;
    }
}

template <typename IT_INPUT,typename VALUE_TYPE>
void czy::Math::clip_up(INPUT IT_INPUT in_begin,INPUT IT_INPUT in_end,VALUE_TYPE max)
{
    for(;in_begin != in_end;++in_begin)
    {
        if(*in_begin>max)
            *in_begin = max;
    }
}


#endif // CZYMATH_H
