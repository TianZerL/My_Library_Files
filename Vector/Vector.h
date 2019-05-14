/*
 * Copyleft (c) 2019 by TianZer.
 * Some rights reserved.
*/
#pragma once
#include <stdexcept>



template<typename T>
class Vector
{
private:
    T* data;    //自定义数据类型
    int length,capacity;    //长度和容量
public:
    //无参构造函数，会生成一个长度为1，容量为2的容器
    Vector() {
        capacity = 2;
        length = 1;
        data = new T[capacity];
    }
    //指定长度生成容器，其容量等于长度 
    Vector(int _length) {
        if (_length < 1)
            throw std::domain_error("Length must be bigger than 1!");
        capacity = length = _length;      
        data = new T[capacity];
    }
    //指定长度和容量生成容器
    Vector(int _length, int _capcity) {
        if (_length < 1 || _capcity < 1)
            throw std::domain_error("Length and capacity must be bigger than 1!");
        if (_length > _capcity)
            throw std::out_of_range("Length must be less than capacity");
        length = _length;
        capacity = _capcity;
        data = new T[capacity];
    }
    //生成一个和指定容器相同的容器
    Vector(const Vector<T>& v) {
        length = v.length;
        capacity = v.capacity;
        data = new T[capacity];
        for (int i = 0; i < length; i++)
            data[i] = v.data[i];
    }
    //析构清理
    ~Vector()
    {
        delete[] data;
    }
    /****************************大小控制***********************************/
    //重设容器容量
    void Resize(int _capacity) {
        if (_capacity < 1)
            throw std::domain_error("Capacity must be bigger than 1!");
        if (_capacity == capacity)
            return;
        else if (_capacity > capacity)
        {
            T* temp = data;
            capacity = _capacity;
            data = new T[capacity];
            for (int i = 0; i < length; i++)
                data[i] = temp[i];
            delete[] temp;
        }
        else if (_capacity < capacity)
        {
            if (_capacity >= length)
            {
                T* temp = data;
                capacity = _capacity;
                data = new T[capacity];
                for (int i = 0; i < length; i++)
                    data[i] = temp[i];
                delete[] temp;
            }
            else
            {
                T* temp = data;
                capacity = _capacity;
                data = new T[capacity];
                for (int i = 0; i < capacity; i++)
                    data[i] = temp[i];
                delete[] temp;
            }
        }
    }
    //重设容器长度
    void Relength(int _length) {
        if (_length < 1)
            throw std::domain_error("Length must be bigger than 1!");
        if (_length > capacity)
        {
            if (_length <= 2 * capacity)
                Resize(2 * capacity);
            else
                Resize(_length);
        }
        else if (_length == length)
            return;
        length = _length;
    }
    //将容器容量设置为和容器长度相同
    void Shrink() {
        if (length == capacity)
            return;
        Resize(length);
        capacity = length;
    }
    //将容器长度设置为和容器容量相同
    void Extand() {
        length = capacity;
    }
    /****************************辅助函数***********************************/
    //返回容器容量
    int Size() const {
        return capacity;
    }
    //返回容器长度
    int Length() const {
        return length;
    }
    //反序容器元素
    void Reverse() {
        T* temp = data;
        data = new T[capacity];
        for (int i = 0; i < length; i++)
            data[length-1-i] = temp[i];
        delete[] temp;
    } 
    /****************************元素检索***********************************/
    //返回容器头指针
    T* FrontPtr() const {
        return data;
    }
    //返回容器任意元素指针,包括大于长度但在容量内的，越界将返回空指针。
    T* Ptr(int n) const {
        if (n >= capacity || n < 0)
            return 0;
        return data+n;
    }
    /****************************算符重载***********************************/
    //重载[]，只能访问长度以内的元素，越界抛出错误
    T& operator[] (int n) {
        if (n >= length || n < 0)
            throw std::out_of_range("Out of range!");
        return data[n];
    }
    //重载=，将一个容器赋给另一个容器，并会返回被赋值容器的引用
    const Vector<T>& operator= (const Vector<T>& v) {
        delete[] data;
        capacity = v.capacity;
        length = v.length;
        data = new T[capacity];
        for (int i = 0; i < length; i++)
            data[i] = v.data[i]; 
        return *this;
    }
    //重载+，将一个容器与另一个任意头尾相连，头部在+运算符的左边
    Vector<T> operator+ (const Vector<T>& v) {
        Vector<T> temp(length + v.length, capacity + v.capacity);
        int i = 0, j;
        for (j = 0; j < length; j++, i++)
            temp.data[i] = data[j];
        for (j = 0; j < v.length; j++, i++)
            temp.data[i] = v.data[j];
        return temp;
    }
};