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

}
#endif //MINI_STL_ALGORITHM_H
