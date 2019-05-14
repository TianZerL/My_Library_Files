/*
 * Copyleft (c) 2019 by TianZer.
 * Some rights reserved.
*/
#pragma once
#include<stdexcept>



//节点类，可包含一个任意的数据类型
template<typename T>
class Node
{
public:
    T data; //自定义数据
    Node* next=0, * prev=0; //节点指针
    int n;  //当前节点的编号，用于给节点排位
    Node(int N = 0) {
        n = N;
    }
};

//链表管理类，使用List<typename> listname 即可声明一个链表
template<typename T>
class List
{
private:
    //节点总数
    int total=0;
    //头结点，尾节点，供内部使用的现有节点
    Node<T>* head = 0, * end = 0, * now = 0;
    //内部函数，用于创建节点
    inline Node<T>* creat_node(int n) {
        return new Node<T>(n);
    }
    //内部函数，用于查找指定位置的节点
    inline Node<T>* find_node(int n) {
        if (n <= (total / 2 + 1))   //判断从哪边遍历更快
        {
            Node<T>* p = head;
            for (; p->n != n && p->next != 0; p = p->next);     //遍历链表
            if (p->n != n)  //查找失败则返回NULL
                return 0;
            else
                return p;   //查找成功则返回节点指针
        }
        else
        {
            Node<T>* p = end;
            for (; p->n != n && p->prev != 0; p = p->prev);     //遍历链表
            if (p->n != n)
                return 0;
            else
                return p;
        }
    }
public:
    //无参构造函数，默认会生成一个节点
    List() {
        now = end = head = creat_node(0);
        head->prev = 0;
        head->next = 0;
        total++;
    }
    //根据参数，生成n个节点
    List(int n) {
        if (n < 1)
            throw std::domain_error("The number of node must be greater than 1!");
        now = end = head = creat_node(0);
        head->prev = 0;
        head->next = 0;
        total++;
        for (; total < n; Append_To_End());
    }
    //复制构造函数，生成和另一个链表相同的链表
    List(const List<T>& l) {
        now = end = head = creat_node(0);
        head->prev = 0;
        head->next = 0;
        total++;
        if (l.total == 1)
            return;
        for (; total < l.total; Append_To_End());
        Node<T>* p = head, * q = l.head;
        for (; p != 0 && q != 0; p = p->next, q = q->next)
            p->data = q->data;
    }
    //析构清理内存
    ~List() {
        Node<T>* p = head, *q = head;
        while (p != 0)
        {
            p = p->next;
            delete q;
            q = p;
        }
    }
    /****************************插入节点***********************************/
    //在链表末尾添加一个节点，并返回其地址
    Node<T>* Append_To_End() {
        end->next = creat_node(total);
        end->next->prev = end;
        end = end->next;
        end->next = 0;
        total++;
        return end;
    }
    //在指定位置后面插入一个新节点，并返回其地址
    Node<T>* Append(int n) {
        now = find_node(n);
        if (now == 0)   //判断是否查找失败，查找失败则抛出错误
            throw std::out_of_range("Cannot find this node!");
        else if (now == end)    //判断添加位置是否位于链表尾部
            return Append_To_End();
        else
        {
            Node<T>* p = now;
            now = creat_node((p->n) + 1);
            now->prev = p;
            now->next = p->next;
            p->next->prev = now;
            p->next = now;
            for (p = now->next; p != 0; p = p->next)    //将添加位置后的链表编号+1
                p->n++;
            total++;        //总结点数+1
            return now;     //返回新加节点指针
        }

    }
    //在链表头插入一个新节点，并返回其地址
    Node<T>* Insert_To_Head() {
        Node<T>* p = head;
        head = creat_node(0);
        head->prev = 0;
        head->next = p;
        p->prev = head;
        for (; p != 0; p = p->next)
            p->n++;
        total++;
        return head;
    }
    //在指定位置之前插入一个新节点，并返回其地址
    Node<T>* Insert(int n) {
        now = find_node(n);
        if (now == 0)       //查找失败则抛出错误
            throw std::out_of_range("Cannot find this node!");
        else if (now == head)
            return Insert_To_Head();
        else
        {
            Node<T>* p = now;
            now = creat_node(p->n);
            now->next = p;
            now->prev = p->prev;
            p->prev->next = now;
            p->prev = now;
            for (; p != 0; p = p->next)
                p->n++;
            total++;
            return now;
        }
    }
    /****************************删除节点***********************************/
    //删除尾节点
    void Earse_End() {
        end = end->prev;
        delete end->next;
        end->next = 0;
        total--;
    }
    //删除头结点
    void Earse_Head() {
        head = head->next;
        delete head->prev;
        head->prev = 0;
        total--;
    }
    //删除指定节点
    void Earse(int n) {
        now = find_node(n);
        if (now == 0)       //查找失败则抛出错误
            throw std::out_of_range("Cannot find this node!");
        else if (now == end)       //判断是否为尾节点
            Earse_End();
        else if (now == head)       //判断是否为头节点
            Earse_Head();
        else
        {
            Node<T>* p = now->next;
            now->prev->next = now->next;
            now->next->prev = now->prev;
            delete now;
            for (; p != 0; p = p->next)     //将删除位置后的节点编号-1
                p->n--;
            total--;
        }
    }
    /****************************辅助功能***********************************/
    //返回当前链表节点数
    int Size() const {
        return total;
    }
    //反序链表
    void Reverse() {
        Node<T>* p = head, * temp = p->next, * t = 0;
        while (p != 0)
        {
            t = p->next;
            p->next = p->prev;
            p->prev = t;
            p = temp;

            if (temp == 0)
                break;
            temp = temp->next;
        }
        t = head;
        head = end;
        end = t;
        for (p = head; p != 0; p = p->next)
            p->n = total - p->n - 1;
    }
    /****************************算符重载***********************************/
    //用[]检索链表节点
    T& operator[] (int n) {
        if (n >= total || n < 0)      //查找失败则抛出错误
            throw std::out_of_range("Out of range!");
        return find_node(n)->data;
    }
    //两个链表相互赋值
    const List<T>& operator=(const List<T>& l) {
        Node<T>* p = head, * q = l.head;
        if (l.total == total)
            for (; p != 0 && q != 0; p = p->next, q = q->next)
                p->data = q->data;
        if (l.total > total)
        {
            for (; total < l.total; Append_To_End());
            for (; p != 0 && q != 0; p = p->next, q = q->next)
                p->data = q->data;
        }
        if (l.total < total)
        {
            for (; total > l.total; Earse_End());
            for (; p != 0 && q != 0; p = p->next, q = q->next)
                p->data = q->data;
        }
        return *this;
    }
    //比较两个链表的长度
    bool operator ==(const List<T>& l) const {
        if (l.total != total)
            return false;
        else
            return true;
    }
    //返回将两个链表相连后的新链表
    List<T> operator+(const List<T>& l) {
        List<T> temp;
        Node<T>* p = head, * q = l.head, * t = temp.head;
        for (; temp.total < total + l.total;temp.Append_To_End());
        for (; p != 0; p = p->next, t = t->next)
            t->data = p->data;
        for (; q != 0; q = q->next, t = t->next)
            t->data = q->data;
        return temp;
    }
};
