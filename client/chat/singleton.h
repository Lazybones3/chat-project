#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>
#include <mutex>
#include <iostream>

template <typename T>
class Singleton {
protected:
    Singleton() = default;
    Singleton(const Singleton<T>&) = delete;
    Singleton& operator=(const Singleton<T>&) = delete;

    static std::shared_ptr<T> _instance;
public:
    static std::shared_ptr<T> GetInstance() {
        static std::once_flag s_flag;
        std::call_once(s_flag, [&](){
            // 使用new操作符创建对象，并将其传递给shared_ptr的构造函数
            _instance = std::shared_ptr<T>(new T);
        });
        return _instance;
    }

    void PrintAddress() {
        std::cout << _instance.get() << std::endl;
    }
    ~Singleton() {
        std::cout << "this is singleton destruct" << std::endl;
    }
};

// 定义并初始化静态成员变量_instance，初始值为nullptr
template <typename T>
std::shared_ptr<T> Singleton<T>::_instance = nullptr;

#endif // SINGLETON_H
