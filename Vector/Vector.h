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
    T* data;    //�Զ�����������
    int length,capacity;    //���Ⱥ�����
public:
    //�޲ι��캯����������һ������Ϊ1������Ϊ2������
    Vector() {
        capacity = 2;
        length = 1;
        data = new T[capacity];
    }
    //ָ�������������������������ڳ��� 
    Vector(int _length) {
        if (_length < 1)
            throw std::domain_error("Length must be bigger than 1!");
        capacity = length = _length;      
        data = new T[capacity];
    }
    //ָ�����Ⱥ�������������
    Vector(int _length, int _capcity) {
        if (_length < 1 || _capcity < 1)
            throw std::domain_error("Length and capacity must be bigger than 1!");
        if (_length > _capcity)
            throw std::out_of_range("Length must be less than capacity");
        length = _length;
        capacity = _capcity;
        data = new T[capacity];
    }
    //����һ����ָ��������ͬ������
    Vector(const Vector<T>& v) {
        length = v.length;
        capacity = v.capacity;
        data = new T[capacity];
        for (int i = 0; i < length; i++)
            data[i] = v.data[i];
    }
    //��������
    ~Vector()
    {
        delete[] data;
    }
    /****************************��С����***********************************/
    //������������
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
    //������������
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
    //��������������Ϊ������������ͬ
    void Shrink() {
        if (length == capacity)
            return;
        Resize(length);
        capacity = length;
    }
    //��������������Ϊ������������ͬ
    void Extand() {
        length = capacity;
    }
    /****************************��������***********************************/
    //������������
    int Size() const {
        return capacity;
    }
    //������������
    int Length() const {
        return length;
    }
    //��������Ԫ��
    void Reverse() {
        T* temp = data;
        data = new T[capacity];
        for (int i = 0; i < length; i++)
            data[length-1-i] = temp[i];
        delete[] temp;
    } 
    /****************************Ԫ�ؼ���***********************************/
    //��������ͷָ��
    T* FrontPtr() const {
        return data;
    }
    //������������Ԫ��ָ��,�������ڳ��ȵ��������ڵģ�Խ�罫���ؿ�ָ�롣
    T* Ptr(int n) const {
        if (n >= capacity || n < 0)
            return 0;
        return data+n;
    }
    /****************************�������***********************************/
    //����[]��ֻ�ܷ��ʳ������ڵ�Ԫ�أ�Խ���׳�����
    T& operator[] (int n) {
        if (n >= length || n < 0)
            throw std::out_of_range("Out of range!");
        return data[n];
    }
    //����=����һ������������һ�����������᷵�ر���ֵ����������
    const Vector<T>& operator= (const Vector<T>& v) {
        delete[] data;
        capacity = v.capacity;
        length = v.length;
        data = new T[capacity];
        for (int i = 0; i < length; i++)
            data[i] = v.data[i]; 
        return *this;
    }
    //����+����һ����������һ������ͷβ������ͷ����+����������
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