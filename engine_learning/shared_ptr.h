#include <iostream>

struct test
{
    int data;
    test(int x) : data(x)
    {
        std::cout << "test有参构造" << std::endl;
    };
    void hellow()
    {
        std::cout << "hellow world" << std::endl;
    }
};

template <typename T>
class sharedptr
{
public:
    explicit sharedptr(T* p = nullptr) : ptr(p), count(nullptr)
    {
        if (p != nullptr)
        {
            count = new size_t(1);
            std::cout << "sharedptr有参构造" << std::endl;
        }
        else std::cout << "sharedptr默认构造" << std::endl;
    };

    sharedptr(const sharedptr& other) : ptr(other.ptr), count(other.count)
    {
        if (count)
        {
            (*count)++;
            std::cout << "sharedptr拷贝构造  count=" << *count << std::endl;
        }
    };

    sharedptr& operator=(const sharedptr& other)
    {
        if (this == &other) return *this;
        release();
        ptr = other.ptr;
        count = other.count;
        if (count)
        {
            (*count)++;
            std::cout << "赋值，计数 = " << *count << std::endl;
        }
        else std::cout << "赋值为空" << std::endl;
        return *this;
    }

    T& operator* () const
    {
        return *ptr;
    }

    T* operator->() const
    {
        return ptr;
    }

    size_t count_t() const
    {
        return count ? *count : 0;
    }

    ~sharedptr()
    {
        release();
    }

private:
    T* ptr;
    size_t* count;
    void release()
    {
        if (count)
        {
            (*count)--;
            std::cout << "释放当前计数" << std::endl;
            if (*count == 0)
            {
                delete ptr;
                delete count;
                ptr = nullptr;
                count = nullptr;
                std::cout << "资源已释放" << std::endl;
            }
        }
    }
};
