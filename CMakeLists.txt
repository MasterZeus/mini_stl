cmake_minimum_required(VERSION 3.10)
project(mini_stl)

set(CMAKE_CXX_STANDARD 11)

add_executable(mini_stl main.cpp Container/Vector.h Allocator/alloc.cpp Allocator/alloc.h Allocator/Allocator.h TypeTrait/TypeTrait.h Constructor/Constructor.h Iterator/Iterator.h Algorithm/Algorithm.h Uninitialized.h Iterator/ReverseIterator.h Container/Deque.h Funtor/Funtor.h Container/List.h Container/Pair.h Container/RBtree.h Container/Set.h Container/Map.h Container/HashTable.h)