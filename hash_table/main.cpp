#include <iostream>
#include <string>
#include <assert.h>

using namespace std;
typedef string Key;

const int HashConst = 31;

const int HighLoadFactor = 2;


size_t HashCalculation (const Key& in) {
    size_t length = in.length();
    size_t HashValue = in[length-1] % HashConst;
    for(int i=length-2;i>=0;i--)
        HashValue= HashValue*HashConst+in[i]%HashConst;
    return HashValue;
}
struct Value {
    unsigned age;
    unsigned weight;
    Value(int,int);
    Value();
};
Value::Value () {
    age = 20;
    weight = 75;
}
Value::Value (int a, int w):age(a),weight(w) {
}
struct Node {
        Value Current;
        Key CurrentKey = "Default Anonymous";
        Node* Next = nullptr;
        Node(const Key&,const Value&);
};
Node::Node(const Key& k ,const Value& t) {
    CurrentKey = k;
    Current.age = t.age;
    Current.weight = t.weight;
    Next = nullptr;
}
class EntriesList {
    public:
        EntriesList();
       ~EntriesList(); // destructor
        EntriesList& operator=(const EntriesList&);// new assignment
        EntriesList(const EntriesList&); // copy constructor;
        bool addElement(const Key&,const Value&); // add element to the end of list
        bool Erase(const Key&); // remove element from list
        void showList();
        bool Contains(const Key&) const; // checking value's availability with key
        bool IsEmpty () const;
        Node* GetFirst();
        Value& At (const Key&) const;
        bool Implace (const Key& k , const Value& v);
        void Clear();
        friend bool operator == (const EntriesList&,const EntriesList&);
    private:
        Node* head;
};
void EntriesList::Clear() {
    while(head) {
        Node* tmp = head;
        head=head->Next;
        delete tmp;
    }
    head = nullptr;
}
bool operator == (const EntriesList& t1, const EntriesList& t2) {
    Node* tmp = t1.head;
    while (tmp) {
        if(!t2.Contains(tmp->CurrentKey))
            return false;
            tmp=tmp->Next;
    }
    tmp = t2.head;
    while (tmp) {
        if(!t1.Contains(tmp->CurrentKey))
            return false;
            tmp=tmp->Next;
    }
    return true;
}
bool operator != (const EntriesList& t1, const EntriesList& t2) {
    return !(t1==t2);
}
Value& EntriesList::At(const Key& k) const {
    Node* tmp = head;
    while(tmp) {
        if(tmp->CurrentKey==k)
            return tmp->Current;
        tmp=tmp->Next;
    }
    if (!tmp)
        throw new exception;
}

bool EntriesList::IsEmpty() const {
    return (head) ? false : true;
}
Node* EntriesList :: GetFirst() {
    Node* tmp = head;
    head=head->Next;
    return tmp;
}
bool EntriesList::Contains (const Key& k) const  {
    Node* tmp = head;
    while(tmp) {
        if (tmp->CurrentKey==k)
            return true;
        tmp=tmp->Next;
    }
    return false;
}
EntriesList:: EntriesList() {
    head = nullptr;
}
EntriesList:: EntriesList(const EntriesList&t) {
    head = nullptr;
    Node* tmp = t.head;
    while (tmp){
        this->addElement(tmp->CurrentKey,tmp->Current);
        tmp=tmp->Next;
    }
}
EntriesList& EntriesList:: operator = (const EntriesList& t) {
    if (this!= &t) {
        Node* tmp = t.head;
        Clear(); //???????????????????????????? ����� �� ��������� ���������� � ������������ �������� ���� �� ���� ��� ������������ ������ �������� ����� ������� ������ ������
        while (tmp) {
            this->addElement(tmp->CurrentKey, tmp->Current);
            tmp = tmp->Next;
        }
    }
        return *this;
}
EntriesList:: ~EntriesList() {
        while(head) {
            Node* tmp= head;
            head=head->Next;
            delete tmp;
       }
    head = nullptr;
}
bool EntriesList :: addElement(const Key& k, const Value& info) {
    if (!head) {
        head = new Node(k,info);
        if (!head)
            return false;
    }
    else {
        Node* tmp = head;
        while(tmp->Next)
            tmp=tmp->Next;
        tmp->Next = new Node(k,info);
        if (!tmp->Next)
            return false;
    }
     return true;
}
void EntriesList :: showList() {
    if(!head)
        cout<<"Empty list"<<endl;
    Node* tmp = head;
    while (tmp) {
        cout<<"Name:"<< tmp->CurrentKey << endl << "Age:" << tmp->Current.age << endl << "Weight:" << tmp->Current.weight << endl;
        tmp=tmp->Next;
    }
}

bool EntriesList :: Erase (const Key& k ) {
    if (!head)
        return false;
    Node* tmp = head;
    if (tmp->CurrentKey==k) {
        head=head->Next;
        delete tmp;
        return true;
    }
    while (tmp->Next) {
        if (tmp->Next->CurrentKey==k) {
            Node* tmp1= tmp->Next;
            tmp->Next=tmp1->Next;
            delete tmp1;
            return true;
        }
        tmp=tmp->Next;
    }
    return false;
}

class HashTable {
    public:
        HashTable(); // default constructor
        ~HashTable();// destructor
        HashTable(size_t); // constuctor with any capacity
        HashTable(const HashTable&); // assignment constructor
        HashTable(HashTable&&); // move constructor;
        void Swap(HashTable&);// swap values
        HashTable& operator =(const HashTable&); // new assignment
        HashTable& operator = (HashTable&&); // move operator;
        void Clear(); // clear fields
        bool Erase(const Key&); //  erase field with key ; true if success
        bool Insert(const Key& , const Value&); // add field ; true if success
        bool Contains(const Key&) const; // checking value's availability with key
        Value& operator[](const Key&); //return key's  value; UNSAFE method;
       //  if there is no value for this key, method will add default value and return link to it
       Value& At(const Key&);// return key's value; if there is no value - throw exception
       const Value& At(const Key&) const; // return key's value; if there is no value - throw exception
       size_t Size() const; // return current hashtable's size
       bool Empty() const; // true if empty
       void Show();
       bool Implace (const Key& k , const Value& v);
       friend bool operator == (const HashTable&,const HashTable&);
       friend bool operator != (const HashTable&,const HashTable&);
    private:
        size_t size = 0;
        size_t capacity = 2;
        EntriesList* data = nullptr;
        int loadFactor = 0;
        bool ReHashing();

};
HashTable::HashTable(HashTable&& t) {
    //cout<< "move constructor";
    data = t.data;
    size = t.size;
    loadFactor = t.loadFactor;


    t.data = nullptr;
    t.size=0;
    t.capacity = 2;
    t.loadFactor = 0;

}
HashTable& HashTable:: operator = (HashTable&& t) {
    // cout<< "move operator";
    if (this!= &t) {
        delete [] data;
        data = t.data;

        size = t.size;
        capacity = t.capacity;
        loadFactor=t.loadFactor;

        t.data = nullptr;
    }
    return *this;
}
void HashTable::Clear() {
    delete [] data;
    size = 0;
    capacity = 2;
    loadFactor = 0;
    data = new EntriesList[capacity];
}
Value& HashTable::operator[](const Key& k) {
    if(this->Contains(k))
        return data[HashCalculation(k) % capacity].At(k);
    else {
        Value Default;
        this->Insert(k,Default);
        return data[HashCalculation(k) % capacity].At(k);
    }
}
bool operator == (const HashTable& t1, const HashTable& t2) {
    if (t1.size!=t2.size)
        return false;
    for (size_t i = 0 ; i< t1.capacity; i++)
        if(t1.data[i]!=t2.data[i])
            return false;
    return true;
}
bool operator != (const HashTable& t1, const HashTable& t2) {
    return !(t1==t2);
}
Value& HashTable::At(const Key& k) {
    if (this->Contains(k))
        return this->data[HashCalculation(k)%capacity].At(k);
    else throw new exception;
}
HashTable:: HashTable() {
    capacity = 2;
    loadFactor = 0;
    size = 0;
    data = new EntriesList[capacity];
}

HashTable:: HashTable(size_t c): capacity(c) {
    data = new EntriesList[capacity];
}

HashTable&  HashTable :: operator = (const HashTable& t) {
    if (this != &t) {
        delete[] data;
        size = t.size;
        capacity = t.capacity;
        loadFactor = t.loadFactor;
        data = new EntriesList[capacity];
        copy(t.data, t.data + t.capacity, data);
    }
    return *this;
}
HashTable::HashTable(const HashTable& t) {
    // cout<<"zashel v konstructor"<<endl;
    size = t.size;
    capacity = t.capacity;
    loadFactor = t.loadFactor;
    data = new EntriesList[capacity];
    for(size_t i = 0; i < capacity ; i++) {
        data[i] = t.data[i];
    }
}

HashTable:: ~HashTable() {
    delete []data;
}
void HashTable:: Swap(HashTable& t ) {

    size_t tmp = size;
    size = t.size;
    t.size = tmp;

    tmp = capacity;
    capacity=t.capacity;
    t.capacity=tmp;

    tmp = loadFactor;
    loadFactor=t.loadFactor;
    t.loadFactor=tmp;


    EntriesList* tmp1 = data;
    data = t.data;
    t.data=tmp1;

}

bool HashTable:: Insert(const Key& k, const Value& t) {
    if (Contains(k))
        return false;
    size_t index = HashCalculation(k) % capacity;
    if(!data[index].addElement(k,t))
        return false;
    size++;
    loadFactor=size/capacity;
    if (loadFactor >= HighLoadFactor)
        if (!ReHashing())
            return false;
    return true;
}
bool HashTable:: ReHashing() {
    HashTable tmp(capacity * HighLoadFactor); // tmp hashtable with more capacity
    for (size_t i = 0 ;i <capacity; i++) { // clear all lists in old and adding values tmp table
        while(!data[i].IsEmpty()) {
            Node* ntmp = data[i].GetFirst();
            if (!tmp.Insert(ntmp->CurrentKey,ntmp->Current))
                return false;
            delete ntmp;
        }

    }
    Swap(tmp);

    return true;
}
size_t HashTable::Size() const {
    return size;
}
bool HashTable ::Empty() const {
    return (!size) ? true : false;
}
bool HashTable::Contains(const Key& k) const  {
    size_t index = HashCalculation(k) % capacity;
    return data[index].Contains(k);
}
bool HashTable::Erase(const Key& k) {
    size_t index = HashCalculation(k) % capacity;
    size--;
    return data[index].Erase(k);
}
void HashTable::Show () {
    for (size_t i = 0; i<capacity;i++) {
        data[i].showList();
        std::cout<<endl;
    }
}

/*int main()
{
    Value a,b,c,d,g;
    HashTable Z;
    Z.Insert("KAMA THE BULLET",a);
    Z.Insert("MAGA THE LEZGIN",b);
    //cout<<"poka vse oke"<<endl;
    Z.Show();
    HashTable X = Z;
    HashTable* V = new HashTable;
  //  cout<<"add"<<endl;
    V->Insert("dasad",d);
    HashTable* B = new HashTable;
    *B = *V;
    delete B;
    delete V;
  //  cout<<"heh"<<endl;
    return 0;
}*/
