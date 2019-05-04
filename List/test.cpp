#include<iostream>
#include"List.h"

using namespace std;

struct test
{
    int a;
    int b;
};

int main() {
   //something mess for testing features.
    List<test> l1;
    l1.Append_To_End();
    l1.Append_To_End();
    for (int i = 0; i < l1.Size(); i++)
        l1[i]->a = i;
    for (int i = 0; i < l1.Size(); i++)
        cout << l1[i]->a << endl;
    l1.Append(0);
    l1[1]->a = 100;
    for (int i = 0; i < l1.Size(); i++)
        cout << l1[i]->a << endl;
    cout << endl;
    l1.Earse(1);
    for (int i = 0; i < l1.Size(); i++)
        cout << l1[i]->a << endl;
    cout << endl;
    List<test> l2;
    l2.Append_To_End(); l2.Append_To_End(); l2.Append_To_End(); l2.Append_To_End();
    l2 = l1;
    for (int i = 0; i < l2.Size(); i++)
        cout << l2[i]->a << endl;
    cout << endl;
    for (int i = 0; i < l1.Size(); i++)
        cout << l1[i]->a << endl;
    cout << endl;
    List<test> l3(l2);
    for (int i = 0; i < l3.Size(); i++)
        cout << l3[i]->a << endl;
    l3[0]->a = 99;
    cout << endl;
    
    l3.Insert(2)->data.a=1000;
    for (int i = 0; i < l3.Size(); i++)
        cout << l3[i]->a << endl;
    cout << endl;

    for (int i = 0; i < l2.Size(); i++)
        cout << l2[i]->a << endl;

    cout << endl;
    
    for (int i = 0; i < l1.Size(); i++)
        cout << l1[i]->a << endl;
    cout << endl;
 
    l1.Reverse();
    for (int i = 0; i < l1.Size(); i++)
        cout << l1[i]->a << endl;
    cout << endl;


        return 0;
}