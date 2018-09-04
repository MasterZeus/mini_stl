//
// Created by djc on 18-8-4.
//

#include "alloc.h"
namespace mini_stl
{
    alloc::obj * alloc::free_list[_NFREELISTS] = {0};

    char* alloc::start_pool = 0;
    char* alloc::end_pool = 0;
    size_t alloc::pool_size = 0;

    void* alloc::refill(size_t obj_size)
    {
        int nobjs = 20;
        char *chunk = chunk_alloc(obj_size,nobjs);
        //1.获得一个块
        if (nobjs==1)
        {
            return chunk;
        }
        //2.第一块给客端,其余用free-list串接
        obj *result = (obj*)chunk;
        obj *next_obj = (obj*)(chunk+obj_size);
        obj *current_obj = next_obj;
        free_list[FREELIST_INDEX(obj_size)] = current_obj;
        for (int i = 2; i <= nobjs; ++i)
        {
            if (i==nobjs)
            {
                current_obj->next_free_node = 0;
                break;
            }
            else
            {
                next_obj = (obj*)((char*)(next_obj)+obj_size);
                current_obj->next_free_node = next_obj;
                current_obj = next_obj;
            }
        }
        return result;
    }
            
            
    char* alloc::chunk_alloc(size_t obj_size,int& nobjs)
    {
        char *result;
        size_t total_bytes = obj_size*nobjs;         //请求总大小
        size_t bytes_left = end_pool-start_pool; //内存池中剩余空间大小

        //1.>=所需内存
        if (bytes_left>=total_bytes)
        {
            result = start_pool;
            start_pool += total_bytes;
            return result;
        }
            //2.>=一个块
        else if (bytes_left>=obj_size)
        {
            nobjs = bytes_left/obj_size;
            total_bytes = nobjs*obj_size;
            result = start_pool;
            start_pool += total_bytes;
            return result;
        }
            //3.内存池连一个块的大小都无法提供
        else
        {
            //将剩余的内存池空间分配给free-list
            if (bytes_left>0)
            {
                int index = FREELIST_INDEX(bytes_left);
                ((obj*)(start_pool))->next_free_node = free_list[index];
                free_list[index] = (obj*)(start_pool);
            }
            //重新为内存池申请新内存
            size_t bytes_to_get = 2*total_bytes+ROUND_UP(pool_size>>4);
            start_pool = static_cast<char*>(malloc(bytes_to_get));
            //重新申请失败
            if (start_pool== nullptr)
            {
                //从free-list中查看是否有满足条件的空间
                for(int i=obj_size;i<=_MAX_BYTES;i+=_ALIGN)
                {
                    int index = FREELIST_INDEX(i);
                    if (free_list[index]!= nullptr)
                    {
                        start_pool = (char*)(free_list[index]);
                        free_list[index] = free_list[index]->next_free_node;
                        end_pool = start_pool+i;
                        return chunk_alloc(obj_size,nobjs);
                    }
                }
                end_pool = nullptr;
                return nullptr;
            }
                //重新申请成功
            else
            {
                pool_size += bytes_to_get;
                end_pool = start_pool + bytes_to_get;
                return chunk_alloc(obj_size,nobjs);
            }
        }
    }

    void* alloc::allocate(size_t n)
    {
        //1.大于128
        if (n>_MAX_BYTES)
        {
            return malloc(n);
        }
        int index = FREELIST_INDEX(n);
        obj *result = free_list[index];
        //2.free-list中可以分配
        if (result)
        {
            free_list[index] = result->next_free_node;
            return result;
        }
        //3.free-list相应槽中没有剩余空间，从内存池中重新获取
        else
        {
            void *r = refill(ROUND_UP(n));
            return r;
        }
    }
    void alloc::deallocate(void* p, size_t n)
    {
        //1.大于128归还给堆
        if (n>_MAX_BYTES)
        {
            free(p);
            return;
        }
            //2.小于128归还给free-list
        else
        {
            int index = FREELIST_INDEX(n);
            obj *free = static_cast<obj*> (p);
            free->next_free_node = free_list[index];
            free_list[index] = free;
        }
    }
    void* alloc::reallocate(void* p, size_t old_sz,size_t new_sz)
    {
        deallocate(p,old_sz);
        p = allocate(new_sz);
        return p;
    }

}
