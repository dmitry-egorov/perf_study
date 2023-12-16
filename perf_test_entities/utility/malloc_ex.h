#pragma once

template<typename T>
T* tmalloc(size_t count) {
    return (T*)malloc(count * sizeof(T));
}

template<typename T>
T* aligned_malloc(size_t count, size_t alignment) {
    return (T*)_aligned_malloc(count * sizeof(T), alignment);
}