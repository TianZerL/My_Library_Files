// debug_new.cpp
// compile by using: cl /EHsc /W4 /D_DEBUG /MDd debug_new.cpp
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif 
#endif  // _DEBUG

#include<iostream>
#include"List.h"

using namespace std;

//MemLeakCheck
void EnableMemLeakCheck()
{
    int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    tmpFlag |= _CRTDBG_LEAK_CHECK_DF;
    _CrtSetDbgFlag(tmpFlag);
}


struct test
{
    int a;
    int b;
};


int main() {
    //something mess for testing features.
    //_CrtSetBreakAlloc(267);
    EnableMemLeakCheck();
    List<test> l1;
    l1.Append_To_End();
    l1.Append_To_End();
    for (int i = 0; i < l1.Size(); i++)
        l1[i].a = i;
    for (int i = 0; i < l1.Size(); i++)
        cout << l1[i].a << endl;
    l1.Append(0);
    l1[1].a = 100;
    for (int i = 0; i < l1.Size(); i++)
        cout << l1[i].a << endl;
    cout << endl;
    l1.Earse(1);
    for (int i = 0; i < l1.Size(); i++)
        cout << l1[i].a << endl;
    cout << endl;
    List<test> l2;
    l2.Append_To_End(); l2.Append_To_End(); l2.Append_To_End(); l2.Append_To_End();
    l2 = l1;
    for (int i = 0; i < l2.Size(); i++)
        cout << l2[i].a << endl;
    cout << endl;
    for (int i = 0; i < l1.Size(); i++)
        cout << l1[i].a << endl;
    cout << endl;
    List<test> l3(l2);
    for (int i = 0; i < l3.Size(); i++)
        cout << l3[i].a << endl;
    l3[0].a = 99;
    cout << endl;
    
    l3.Insert(2)->data.a=1000;
    for (int i = 0; i < l3.Size(); i++)
        cout << l3[i].a << endl;
    cout << endl;

    for (int i = 0; i < l2.Size(); i++)
        cout << l2[i].a << endl;

    cout << endl;
    
    for (int i = 0; i < l1.Size(); i++)
        cout << l1[i].a << endl;
    cout << endl;
 
    l1.Reverse();
    for (int i = 0; i < l1.Size(); i++)
        cout << l1[i].a << endl;
    cout << endl;

    l1.Merge(l2);

    
    //l1.Swap(1, 2);
    //cout << l1.Size() << endl;
    //l1.Cut(4, 4);
    //cout << l1.Size() << endl;
    //l1.Insert_To_Head();
    for (int i = 0; i < l1.Size(); i++)
        cout << l1[i].a << endl;
    //int* leak = new int[10];
    cout << endl;
    cout << l1[1].a << endl;
    l1.Earse_Head();
    cout << l1[0].a << endl;
    return 0;
}