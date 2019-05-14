#include<iostream>
#include"Vector.h"

using namespace std;

int main() {
    //something mess for testing features.
    
    //try {
    //    Vector<int> v1(0);
    //}
    //catch(exception error){
    //    cout << error.what() << endl;
    //}

   
   Vector<int> v1(4,8),v2(8,8),v3;
   for (int i = 0; i < v1.Length(); i++)
    {
        v1[i] = i;
    }
    for (int i = 0; i < v2.Length(); i++)
    {
        v2[i] = i;
    }

    for (int i = 0; i < v1.Length(); i++)
    {
        cout << v1[i] << endl;
    }

    cout << endl;

    v1.Reverse();
    for (int i = 0; i < v1.Length(); i++)
    {
        cout << v1[i] << endl;
    }

    cout << endl;

    for (int i = 0; i < v2.Length(); i++)
    {
        cout << v2[i] << endl;
    }

    v3 = v1 + v2;

    cout << endl;
    for (int i = 0; i < v3.Length(); i++)
    {
        cout << v3[i] << endl;
    }

    cout << &v3[0] << endl;
    cout << v3.FrontPtr() << endl;
    cout << v3.Ptr(13) << endl;

    cout << endl;

    cout << v3.Size() << endl;
    v3.Extand();
    cout << v3.Size() << endl;
    for (int i = 0; i < v3.Length(); i++)
    {
        cout << v3[i] << endl;
    }
    return 0;
}