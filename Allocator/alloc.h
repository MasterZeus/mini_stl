//
// Created by djc on 18-8-4.
//

#ifndef MINI_STL_ALLOC_H
#define MINI_STL_ALLOC_H

#include <cstdlib>

namespace mini_stl
{
    class alloc {
    private:
        enum { _ALIGN = 8};
        enum { _MAX_BYTES = 128};
        enum { _NFREELISTS = _MAX_BYTES/_ALIGN};
    private:
        //free_list_basenode
        union obj
        {
            union obj *next_free_node;
            char client_data[_ALIGN];
        };
        //free_list[N] is the list of nodes that are _ALIGN*(N+1) Bytes.
        static obj * free_list[_NFREELISTS];
    private:
        //内存池记录
        static  char* start_pool;
        static  char* end_pool;
        static  size_t pool_size;
    private:
        //向上规整为_ALIGN(8)的倍数字节
        static size_t ROUND_UP(size_t bytes)
        {
            return ((bytes+_ALIGN-1) & ~(_ALIGN-1));
        }
        //根据字节数得到free_list_index
        static size_t FREELIST_INDEX(size_t bytes)
        {
            return ((bytes+_ALIGN-1)/_ALIGN - 1);
        }
        //当free_list对应槽中无可用节点,从内存池中获取节点
        static void* refill(size_t obj_size);
        //从内存池中获取空间以便填充为freelist节点
        static char* chunk_alloc(size_t obj_size,int& nobjs);

    public:
        static void* allocate(size_t n);
        static void deallocate(void* p, size_t n);
        static void* reallocate(void* p, size_t old_sz,size_t new_sz);
    };
}



#endif //MINI_STL_ALLOC_H
