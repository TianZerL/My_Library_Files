/*
 * Copyleft (c) 2019 by TianZer.
 * Some rights reserved.
*/
#pragma once
#include<stdexcept>



//�ڵ��࣬�ɰ���һ���������������
template<typename T>
class Node
{
public:
    T data; //�Զ�������
    Node* next=0, * prev=0; //�ڵ�ָ��
    int n;  //��ǰ�ڵ�ı�ţ����ڸ��ڵ���λ
    Node(int N = 0) {
        n = N;
    }
};

//��������࣬ʹ��List<typename> listname ��������һ������
template<typename T>
class List
{
private:
    //�ڵ�����
    int total=0;
    //ͷ��㣬β�ڵ㣬���ڲ�ʹ�õ����нڵ�
    Node<T>* head = 0, * end = 0, * now = 0;
    //�ڲ����������ڴ����ڵ�
    inline Node<T>* creat_node(int n) {
        return new Node<T>(n);
    }
    //�ڲ����������ڲ���ָ��λ�õĽڵ�
    inline Node<T>* find_node(int n) {
        if (n <= (total / 2 + 1))   //�жϴ��ı߱�������
        {
            Node<T>* p = head;
            for (; p->n != n && p->next != 0; p = p->next);     //��������
            if (p->n != n)  //����ʧ���򷵻�NULL
                return 0;
            else
                return p;   //���ҳɹ��򷵻ؽڵ�ָ��
        }
        else
        {
            Node<T>* p = end;
            for (; p->n != n && p->prev != 0; p = p->prev);     //��������
            if (p->n != n)
                return 0;
            else
                return p;
        }
    }
public:
    //�޲ι��캯����Ĭ�ϻ�����һ���ڵ�
    List() {
        now = end = head = creat_node(0);
        head->prev = 0;
        head->next = 0;
        total++;
    }
    //���ݲ���������n���ڵ�
    List(int n) {
        if (n < 1)
            throw std::domain_error("The number of node must be greater than 1!");
        now = end = head = creat_node(0);
        head->prev = 0;
        head->next = 0;
        total++;
        for (; total < n; Append_To_End());
    }
    //���ƹ��캯�������ɺ���һ��������ͬ������
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
    //���������ڴ�
    ~List() {
        Node<T>* p = head, *q = head;
        while (p != 0)
        {
            p = p->next;
            delete q;
            q = p;
        }
    }
    /****************************����ڵ�***********************************/
    //������ĩβ���һ���ڵ㣬���������ַ
    Node<T>* Append_To_End() {
        end->next = creat_node(total);
        end->next->prev = end;
        end = end->next;
        end->next = 0;
        total++;
        return end;
    }
    //��ָ��λ�ú������һ���½ڵ㣬���������ַ
    Node<T>* Append(int n) {
        now = find_node(n);
        if (now == 0)   //�ж��Ƿ����ʧ�ܣ�����ʧ�����׳�����
            throw std::out_of_range("Cannot find this node!");
        else if (now == end)    //�ж����λ���Ƿ�λ������β��
            return Append_To_End();
        else
        {
            Node<T>* p = now;
            now = creat_node((p->n) + 1);
            now->prev = p;
            now->next = p->next;
            p->next->prev = now;
            p->next = now;
            for (p = now->next; p != 0; p = p->next)    //�����λ�ú��������+1
                p->n++;
            total++;        //�ܽ����+1
            return now;     //�����¼ӽڵ�ָ��
        }

    }
    //������ͷ����һ���½ڵ㣬���������ַ
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
    //��ָ��λ��֮ǰ����һ���½ڵ㣬���������ַ
    Node<T>* Insert(int n) {
        now = find_node(n);
        if (now == 0)       //����ʧ�����׳�����
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
    /****************************ɾ���ڵ�***********************************/
    //ɾ��β�ڵ�
    void Earse_End() {
        end = end->prev;
        delete end->next;
        end->next = 0;
        total--;
    }
    //ɾ��ͷ���
    void Earse_Head() {
        head = head->next;
        delete head->prev;
        head->prev = 0;
        total--;
    }
    //ɾ��ָ���ڵ�
    void Earse(int n) {
        now = find_node(n);
        if (now == 0)       //����ʧ�����׳�����
            throw std::out_of_range("Cannot find this node!");
        else if (now == end)       //�ж��Ƿ�Ϊβ�ڵ�
            Earse_End();
        else if (now == head)       //�ж��Ƿ�Ϊͷ�ڵ�
            Earse_Head();
        else
        {
            Node<T>* p = now->next;
            now->prev->next = now->next;
            now->next->prev = now->prev;
            delete now;
            for (; p != 0; p = p->next)     //��ɾ��λ�ú�Ľڵ���-1
                p->n--;
            total--;
        }
    }
    /****************************��������***********************************/
    //���ص�ǰ����ڵ���
    int Size() const {
        return total;
    }
    //��������
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
    /****************************�������***********************************/
    //��[]��������ڵ�
    T& operator[] (int n) {
        if (n >= total || n < 0)      //����ʧ�����׳�����
            throw std::out_of_range("Out of range!");
        return find_node(n)->data;
    }
    //���������໥��ֵ
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
    //�Ƚ���������ĳ���
    bool operator ==(const List<T>& l) const {
        if (l.total != total)
            return false;
        else
            return true;
    }
    //���ؽ����������������������
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
