#pragma once

template<typename T>
class Node
{
public:
    T data; //自定义数据
    Node* next=0, * prev=0; //节点指针
    int n;  //当前节点的编号
    Node(int N = 0) {
        n = N;
    }
};

template<typename T>
class List
{
private:
    int total=0;
    Node<T>* head = 0, * end = 0, * now = 0;
    inline Node<T>* creat_node(int n) {
        return new Node<T>(n);
    }
    inline Node<T>* find_node(int n) {
        if (n <= (total / 2 + 1))   //判断从哪边遍历更快
        {
            Node<T>* p = head;
            for (; p->n != n && p->next != 0; p = p->next);
            if (p->n != n)
                return 0;
            else
                return p;
        }
        else
        {
            Node<T>* p = end;
            for (; p->n != n && p->prev != 0; p = p->prev);
            if (p->n != n)
                return 0;
            else
                return p;
        }
    }
public:
    //无参构造函数，默认生成一个节点
    List() {
        now = end = head = creat_node(0);
        head->prev = 0;
        head->next = 0;
        total++;
    }
    //根据参数，生成n个节点
    List(int n) {
        now = end = head = creat_node(0);
        head->prev = 0;
        head->next = 0;
        total++;
        for (; total < n; Append_To_End());
    }
    //生成和另一个链表相同的链表
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
    //****************************插入***********************************
    Node<T>* Append_To_End() {
        end->next = creat_node(total);
        end->next->prev = end;
        end = end->next;
        end->next = 0;
        total++;
        return end;
    }
    Node<T>* Append(int n) {
        now = find_node(n);
        if (now == 0)
            return 0;
        else if (now == end)
            return Append_To_End();
        else
        {
            Node<T>* p = now;
            now = creat_node((p->n) + 1);
            now->prev = p;
            now->next = p->next;
            p->next->prev = now;
            p->next = now;
            for (p = now->next; p != 0; p = p->next)
                p->n++;
            total++;
            return now;
        }

    }
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
    Node<T>* Insert(int n) {
        now = find_node(n);
        if (now == 0)
            return 0;
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
    //****************************删除***********************************
    void Earse_End() {
        end = end->prev;
        delete end->next;
        end->next = 0;
        total--;
    }
    void Earse_Head() {
        head = head->next;
        delete head->prev;
        head->prev = 0;
        total--;
    }
    void Earse(int n) {
        now = find_node(n);
        if (now == 0)
            return;
        else if (now == end)
            Earse_End();
        else if (now == head)
            Earse_Head();
        else
        {
            Node<T>* p = now->next;
            now->prev->next = now->next;
            now->next->prev = now->prev;
            delete now;
            for (; p != 0; p = p->next)
                p->n--;
            total--;
        }
    }
    //****************************辅助***********************************
    int Size() {
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
    //****************************算符***********************************
    //检索链表节点
    T* operator[] (int n) {
        return &(find_node(n)->data);
    }
    //链表相互赋值
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
        return l;
    }
    //比较两个链表的长度
    bool operator ==(const List<T>& l) {
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
