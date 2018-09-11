//
// Created by djc on 18-8-9.
//

#ifndef MINI_STL_ALGORITHM_H
#define MINI_STL_ALGORITHM_H

#include <cstring>
#include "../Iterator/Iterator.h"
#include "../TypeTrait/TypeTrait.h"

namespace MINI_STL {
    template<class T>
    inline const T &max(const T &a, const T &b) {
        return a > b ? a : b;
    }

    template<class T>
    inline const T &min(const T &a, const T &b) {
        return a > b ? b : a;
    }

    template<class T>
    inline void swap(T &a, T &b) {
        T temp = a;
        a = b;
        b = temp;
    }
    /************************************************************************/
    /* fill[first,last)->x
       fill_n[first,last)->x
    */
    /************************************************************************/
    template<class ForwardIterator, class T>
    void fill(ForwardIterator first, ForwardIterator last, const T &value) {
        for (; first != last; ++first)
            *first = value;
    }

    template<class OutputIterator, class Size, class T>
    OutputIterator fill_n(OutputIterator first, Size n, const T &value) {
        for (; n > 0; --n, ++first)
            *first = value;
        return first;
    }
    /************************************************************************/
    /* copy[first,last)to[dest...)
    */
    /************************************************************************/
    //copy的完全泛化版本，以及两个特殊版本
    template<class InputIterator, class OutputIterator>
    inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator dest) {
        return _copy_dispatch<InputIterator, OutputIterator>()(first, last, dest);
    }

    inline char *copy(const char *first, const char *last, char *dest) {

        memmove(dest, first, last - first);

        return dest + (last - first);
    }

    inline wchar_t *copy(const wchar_t *first, const wchar_t *last, wchar_t *dest) {
        memmove(dest, first, sizeof(wchar_t) * (last - first));
        return dest + (last - first);
    }

    //_copy_dispatch的一个完全泛化和两个偏特例化版本
    template<class InputIterator, class OutputIterator>
    struct _copy_dispatch {
        OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator dest) {
            return _copy(first, last, dest, iterator_category(first));
        }
    };

    template<class T>
    struct _copy_dispatch<T *, T *> {
        T *operator()(T *first, T *last, T *dest) {
            typedef typename _type_traits<T>::has_trivial_assignment_operator t;
            return _copy_t(first, last, dest, t());
        }
    };

    template<class T>
    struct _copy_dispatch<const T *, T *> {
        T *operator()(const T *first, const T *last, T *dest) {
            typedef typename _type_traits<T>::has_trivial_assignment_operator t;
            return _copy_t(first, last, dest, t());
        }
    };

    //_copy的InputIterator和RandomAccessIterator版本
    template<class InputIterator, class OutputIterator>
    inline OutputIterator _copy(InputIterator first, InputIterator last, OutputIterator dest, input_iterator_tag) {
        for (; first != last; ++first, ++dest)  //通过比较迭代器实现，较慢
            *dest = *first;
        return dest;
    }

    template<class RandomAccessIterator, class OutputIterator>
    inline OutputIterator
    _copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator dest, random_access_iterator_tag) {
        return _copy_d(first, last, dest, difference_type(first));
    }

    //RandomAccessIterator进行复制，通过比较Distance所以速度比较快
    template<class RandomAccessIterator, class OutputIterator, class Distance>
    inline OutputIterator
    _copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator dest, Distance *) {
        for (Distance n = last - first; n > 0; --n, ++dest, ++first)
            *dest = *first;
        return dest;
    }

    //T*和const T*特化版本所用到的_copy_t
    template<class T>
    inline T *_copy_t(const T *first, const T *last, T *dest, _true_type) {
        memmove(dest, first, sizeof(T) * (last - first));
        return dest + (last - first);
    }

    template<class T>
    inline T *_copy_t(const T *first, const T *last, T *dest, _false_type) {
        return _copy_d(first, last, dest, (ptrdiff_t *) 0);
    }


    /************************************************************************/
    /* copy_backward[first,last)to[...dest)
    */
    /************************************************************************/
    template<class BidirectionalIterator, class Distance>
    inline BidirectionalIterator _copy_backward(BidirectionalIterator first,
                                                BidirectionalIterator last,
                                                BidirectionalIterator dest,
                                                bidirectional_iterator_tag,
                                                Distance *) {
        while (first != last)
            *(--dest) = *(--last);
        return dest;
    }

    template<class RandomAccessIterator, class BidirectionalIterator, class Distance>
    inline BidirectionalIterator _copy_backward(RandomAccessIterator first,
                                                RandomAccessIterator last,
                                                BidirectionalIterator dest,
                                                random_access_iterator_tag,
                                                Distance *) {
        for (Distance n = last - first; n > 0; --n)
            *(--dest) = *(--last);
        return dest;
    }

    template<class BidirectionalIterator1, class BidirectionalIterator2>
    inline BidirectionalIterator2
    copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 dest) {
        return _copy_backward(first, last, dest, iterator_category(first), difference_type(first));
    }


    /************************************************************************/
    /* equal:[first1,last1)to[first2...)序列二中多的元素不予考虑
    */
    /************************************************************************/
    template <class InputIterator1,class InputIterator2>
    inline bool equal(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2)
    {
        while (first1!=last1)
        {
            if (*first1!=*first2)
            {
                return false;
            }
            ++first1;
            ++first2;
        }
        return true;
    }

    template <class InputIterator1,class InputIterator2,class BinaryPredicate>
    inline bool equal(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2,BinaryPredicate binary_pred)
    {
        while (first1!=last1)
        {
            if (!binary_pred(*first1,*first2))
            {
                return false;
            }
            ++first1;
            ++first2;
        }
        return true;
    }

    /************************************************************************/
    /* lexicographical_compare:[first1,last1)to[first2,last2)
    */
    /************************************************************************/
    template <class InputIterator1,class InputIterator2>
    bool lexicographical_compare(InputIterator1 first1,InputIterator1 last1,
                                 InputIterator2 first2,InputIterator2 last2)
    {
        while(first1!=last1&&first2!=last2)
        {
            if (*first1<*first2)
            {
                return true;
            }
            if (*first1>*first2)
            {
                return false;
            }
        }
        return first1==last1&&first2!=last2;
    }

    template <class InputIterator1,class InputIterator2,class Compare>
    bool lexicographical_compare(InputIterator1 first1,InputIterator1 last1,
                                 InputIterator2 first2,InputIterator2 last2,
                                 Compare comp)
    {
        while(first1!=last1&&first2!=last2)
        {
            if (comp(*first1,*first2))
            {
                return true;
            }
            if (comp(*first2,*first1))
            {
                return false;
            }
        }
        return first1==last1&&first2!=last2;
    }

    template <class InputIterator,class T>
    T accumulate(InputIterator first,InputIterator last,T init)
    {
        while(first!=last)
        {
            init = init + *first;
            ++first;
        }
        return init;
    }

    template <class InputIterator,class T,class BinaryOperation>
    T accumulate(InputIterator first,InputIterator last,T init,BinaryOperation op)
    {
        while(first!=last)
        {
            init = op(init ,*first);
            ++first;
        }
        return init;
    }

    template <class InputIterator,class T>
    InputIterator find(InputIterator first,InputIterator last,const T& value)
    {
        while (first!=last && *first!=value)
        {
            ++first;
        }
        return first;
    }

    template <class ForwardIterator,class T>
    inline ForwardIterator lower_bound(ForwardIterator first,ForwardIterator last,const T& value)
    {
        return _lower_bound(first,last,value,difference_type(first),iterator_category(first));
    }

    template <class ForwardIterator,class T,class Distance>
    inline ForwardIterator _lower_bound(ForwardIterator first,ForwardIterator last,const T& value,Distance*,forward_iterator_tag)
    {
        Distance len = distance(first,last);
        Distance half;
        ForwardIterator mid;
        while(len>0)
        {
            half = len>>1;
            mid = first;
            advance(mid,half);
            if(*mid<value)
            {
                first = mid;
                ++first;
                len = len-half-1;
            }
            else
                len = half;
        }
        return first;
    }

    template <class ForwardIterator,class T,class Distance>
    inline ForwardIterator _lower_bound(ForwardIterator first,ForwardIterator last,const T& value,Distance*,random_access_iterator_tag)
    {
        Distance len = distance(first,last);
        Distance half;
        ForwardIterator mid;
        while (len>0)
        {
            half = len>>1;
            mid = first+half;
            if (*mid<value)
            {
                first = mid+1;
                len = len-half-1;
            }
            else
                len = half;
        }
        return first;
    }


}
#endif //MINI_STL_ALGORITHM_H
