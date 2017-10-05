#include <iostream>
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

    tmp= capacity;
    capacity=t.capacity;
    t.capacity=tmp;

    tmp = loadFactor;
    loadFactor=t.loadFactor;
    t.loadFactor=tmp;


    EntriesList* tmp1 = data;
    data=t.data;
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
            Node ntmp = data[i].GetFirst();
            if (!tmp.Insert(ntmp.CurrentKey,ntmp.Current))
                return false;
        }
    }
    Swap(tmp);
    return true;
}
size_t HashTable::Size() const {
    return size;
}
bool HashTable ::Empty() const {
    return (size) ? true : false;
}
bool HashTable::Contains(const Key& k) const  {
    size_t index = HashCalculation(k) % capacity;
    return data[index].Contains(k);
}
bool HashTable::Erase(const Key& k) {
    size_t index = HashCalculation(k) % capacity;
    return data[index].Erase(k);
}
void HashTable::Show () {
    for (size_t i = 0; i<capacity;i++) {
        data[i].showList();
       std::cout<<endl;
    }
}
