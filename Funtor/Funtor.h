//
// Created by djc on 18-8-13.
//

#ifndef MINI_STL_FUNTOR_H
#define MINI_STL_FUNTOR_H

namespace MINI_STL
{
    template<class T>
    struct less
    {
        bool operator()(const T& x,const T& y)const
        {
            return x<y;
        }
    };

    template<class T>
    struct identity
    {
        const T& operator()(const T& x)const
        {
            return x;
        }
    };

    template<class Pair>
    struct selectFirst
    {
        const typename Pair::first_type& operator()(const Pair& x)const
        {
            return x.first;
        }
    };

    template<class T>
    struct equal_to
    {
        bool operator()(const T& x,const T& y)const{return x==y;}
    };
}


#endif //MINI_STL_FUNTOR_H
