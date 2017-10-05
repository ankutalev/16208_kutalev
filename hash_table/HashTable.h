//
// Created by ulyssess on 05.10.17.
//

#ifndef UNTITLED_HASHTABLE_H
#define UNTITLED_HASHTABLE_H

#include "HashTable.cpp"
class HashTable {
public:
    HashTable(); // default constructor
    ~HashTable();// destructor
    HashTable(size_t); // constuctor with any capacity
    HashTable(const HashTable&); // assignment constructor
    HashTable(HashTable&&); // move constructor;
    void Swap(HashTable&);// swapp values
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
#endif //UNTITLED_HASHTABLE_H
