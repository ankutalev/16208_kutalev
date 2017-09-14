#include <iostream>
#include <stdlib.h>
#include<stdio.h>
#include<assert.h>
using namespace std;
class Array {
    private:
        int* data;
        int size;
        int capacity;
       const static int default_capacity = 10;
    public:
        Array(int); // constructor
        ~Array();                    // destructor
        Array(const Array&);  // copy constructor;
        Array(); // default constructor
        Array& operator = (const Array&); //copy  assignment
        void AddElement(int);
       // void ShowArray();
        friend ostream& operator<<(ostream& os, const Array& t); // cout << Array
        Array operator +(const Array&); // array z = array x [A1,A2.....Asize] + array y [B1...Bsize] = [A1...Asize,B1.. Bsize]
        int &operator [](int i);
};
Array::Array(){
    data=(int*)calloc(default_capacity,sizeof(int));
    capacity=default_capacity;
    size=0;
}
Array::Array (int initial_capacity) {
    assert(initial_capacity > 0);
    data = (int*)calloc(initial_capacity,sizeof(int));
    assert(data);
    size=0;
    capacity = initial_capacity;
}
Array::Array(const Array& t) {
    data = (int*)calloc(t.capacity,sizeof(int));
    assert(data);
    size = t.size;
    capacity = t.capacity;
    for (int i = 0; i < size;i++)
        data[i]=t.data[i];
}
Array& Array:: operator =(const Array& t) {
    if (this!= &t) {
        if (data)
            delete data;
        data = (int*)calloc(t.capacity,sizeof(int));
        assert(data);
        capacity = t.capacity;
        size = t.size;
        for (int i =0;i<t.size;i++)
            data[i]=t.data[i];
    }
}
ostream& operator<<(ostream& os, const Array& t) {
    for (int i = 0; i<t.size; i++)
        os<<t.data[i]<<" ";
    return os;
}
Array::~Array() {
    if(data)
        delete data;
}
void Array:: AddElement(int elem) {
    assert(data);
    if (size < capacity) {
        data[size] = elem;
        size++;
    }
    else {
        capacity=2*capacity;
        data = (int*)realloc(data,sizeof(int)*capacity);
        assert(data);
        data[size]=elem;
        size++;
    }
}
/*void Array:: ShowArray() {
    for(int i =0;i< size;i++)
        cout<<data[i]<<" ";
} */
int& Array::operator[](int i) {
    assert(i<size);
    return data[i];
}
Array Array:: operator + (const Array& t1) {
    Array Z;
    Z.capacity=capacity+t1.capacity;
    Z.size = t1.size + size;
    Z.data = (int*)calloc(Z.capacity,sizeof(int));
    assert(Z.data);
    int i,j;
    for(i =0;i<size;i++)
        Z.data[i] = data[i];
    for(j=0;j < t1.size;j++)
        Z.data[i+j] = t1.data[j];
    return Z;
}
int main()
{
    Array X;
    X.AddElement(5);
    X.AddElement(10500);
    X.AddElement(3);
    X.AddElement(3123);
//    X.ShowArray();
    Array Y;
    for(int i =0; i<5;i++)
        Y.AddElement(i);
    cout << X << endl << Y << endl;
    Array Z = X + Y;
    cout<< Z;
    Z[0]=322;
    cout<<endl<<Z;
    return 0;
}
