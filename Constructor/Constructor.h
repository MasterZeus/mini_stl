//
// Created by djc on 18-8-9.
//

#ifndef MINI_STL_CONSTRUCTOR_H
#define MINI_STL_CONSTRUCTOR_H

#include <new>
#include "../TypeTrait/TypeTrait.h"
#include "../Iterator/Iterator.h"

namespace MINI_STL
{
    //构造函数,使用placement new构造
    template <class T1,class T2>
    inline void construct(T1 *p,const T2 &value)
    {
        new(p) T1(value);
    }

    //析构函数,调用类型的析构函数
    template <class T>
    inline void destroy(T *pointer)
    {
        pointer->~T();
    }

    template <class ForwardIterator>
    inline void destroy(ForwardIterator first,ForwardIterator last)
    {
        _destroy(first,last,&*first);
    }

    template <class ForwardIterator,class T>
    inline void _destroy(ForwardIterator first,ForwardIterator last,T*)
    {
        typedef typename _type_traits<T>::has_trivial_destructor trivial_destructor;
        _destroy_aux(first,last,trivial_destructor());
    }

    template <class ForwardIterator>
    inline void _destroy_aux(ForwardIterator first,ForwardIterator last,_false_type)
    {
        while(first<last)
        {
            destroy(&*(first++));
        }
    }

    template <class ForwardIterator>
    inline void _destroy_aux(ForwardIterator first,ForwardIterator last,_true_type)
    {
        /*do nothing*/
    }
}


#endif //MINI_STL_CONSTRUCTOR_H
