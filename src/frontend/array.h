#ifndef ARRAY_H
#define ARRAY_H

template <typename T>
struct Array {
    size_t len = 0; //数组的长度
    size_t cap = 0; //数组的容量
    T* a = NULL;

    Array() {};
    Array(int length) { set_len(length); };
    void release() {
        if (a) {
            a = NULL;
            len = cap = 0;
        }
    }
    size_t size() { return len; };
    void push(T it) { maygrow(1); a[len++] = it; };
    void pop() { len--; }; //只需要修改数组的结尾，并不需要删除最后的元素。
    T back() { return a[len - 1]; };
    T front() { return a[0]; };
    bool empty() { return len == 0; };
    T& operator[](size_t i) { return a[i]; }

    T* begin() { return a; }
    T* end() { return a + len; }

    int find(T it) {
        for (size_t f = 0; f < len; f++) {
            if (a[f] == it) return f;
        }
        return -1;
    }

    // 删除第一次出现的指定元素
    void remove(T it) {
        size_t p = find(it);
        if (p != -1) {
            memmove(a + p, a + p + 1, sizeof(T) * (len - p - 1));
            len--;
        }
    }

    void insert(size_t i, T it) {
        maygrow(1);
        memmove(a + i + 1, a + i, sizeof(T) * (len - i));
        a[i] = it;
        len++;
    }

    void set_len(size_t new_len) {
        if (cap < new_len) set_cap(new_len);
        if (a) {
            for (int i = len; i < new_len; i++) {
                new (&a[i]) T;
            }
            len = new_len;
        }
        else {
            assert(false);
        }
    }

    void set_cap(size_t new_cap) { grow(0, new_cap); }
    void maygrow(size_t addlen) { if (!a || len + addlen > cap) grow(addlen, 0); };
    void grow(size_t addlen, size_t min_cap);

};

// 此方法用来保证数组至少可以容纳由minimum capacity参数指定的元素数。
template <typename T>
void Array<T>::grow(size_t addlen, size_t min_cap) {
    size_t elemsize = sizeof(T);
    size_t new_length = len + addlen;
    size_t new_cap = min_cap;

    if (new_length > new_cap)
        new_cap = new_length;

    if (new_cap <= cap) 
        return ;

    if (new_cap < cap * 2) 
        new_cap = cap * 2;
    else if (new_cap < 4) 
        new_cap = 4;

    void* b;
    b = realloc(a, elemsize * new_cap);

    if (!a) {
        len = 0;
    }
    cap = new_cap;
    a = (T*)b;
}

// 创建固定大小的二维数组
template <typename T>
Array< Array<T> > make_2d(int row, int column = -1) {
    Array< Array<T> > arr(row);
    memset(arr.a, 0, sizeof(Array<T>) * row);
    if (column != -1) {
        for (int i = 0; i < row; i++) {
            arr[i].set_len(column);
        }
    }
    return arr;
}

#endif
