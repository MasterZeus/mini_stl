//
// Created by djc on 18-8-7.
//

#ifndef MINI_STL_TYPETRAIT_H
#define MINI_STL_TYPETRAIT_H

namespace MINI_STL
{
    //声明两个空类,作为类型参数的实值,表达真假
    //对于一个模板类,传入一个类型,即可根据类型设置内置类型.
    //内置类型随传入类型变化而变化,如同普通函数的参数和返回值的关系
    //因此可以像使用函数一样使用模板类,和函数的区别在于,传入传出的是类型
    //并且是在编译期完成.

    struct _true_type {
    };


    struct _false_type {
    };


    /*
    特性萃取以及特例化版本
    */
    template <class _Tp>
    struct _type_traits {
        typedef _false_type    has_trivial_default_constructor;
        typedef _false_type    has_trivial_copy_constructor;
        typedef _false_type    has_trivial_assignment_operator;
        typedef _false_type    has_trivial_destructor;
        typedef _false_type    is_POD_type;
    };

    template<>
    struct _type_traits<bool> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<char> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<signed char> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<unsigned char> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<wchar_t> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<short> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<unsigned short> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<int> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<unsigned int> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<long> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<unsigned long> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<long long> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<unsigned long long> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<float> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<double> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<long double> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };


    template <class T>
    struct _type_traits<T*> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<char*> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<signed char*> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<unsigned char*> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<const char*> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<const signed char*> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };

    template<>
    struct _type_traits<const unsigned char*> {
        typedef _true_type    has_trivial_default_constructor;
        typedef _true_type    has_trivial_copy_constructor;
        typedef _true_type    has_trivial_assignment_operator;
        typedef _true_type    has_trivial_destructor;
        typedef _true_type    is_POD_type;
    };


#endif //MINI_STL_TYPETRAIT_H
