//
// Created by ulyssess on 12.10.17.
//

#ifndef HASHTABLE_TEMPLATE_TEMPLATE_HASH_TABLE_H
#define HASHTABLE_TEMPLATE_TEMPLATE_HASH_TABLE_H
template <class Key,class Value>
struct Node {
    Node(const Key& k, const Value& v) : Current(v), CurrentKey(k) { };
    Node(const Key& k) : CurrentKey(k){};
    friend bool operator == (const Node& a, const Node& b ) {
        return a.CurrentKey==b.CurrentKey;
    }
    Node& operator = (Node& t) {
        if(this!=&t) {
            Current = t.Current;
            CurrentKey = t.CurrentKey;
        }
        return  *this;
    }
    Value Current;
    Key CurrentKey;
};
template <class Key, class Value,size_t (*HashFunction)(const Key &)>
class HashTable {
public:
    HashTable() : size(0), capacity(defaultCapacity), data(new std::list<Node<Key, Value>>[capacity]) {}; // default constructor
    HashTable(size_t in) : size(0), capacity(in),
                           data(new std::list<Node<Key, Value>>[capacity]) {}; // constructor with any capacity
    HashTable(const HashTable &t) { //copy constructor
        size = t.size;
        capacity = t.capacity;
        data = new std::list<Node<Key, Value>>[capacity];
        std::copy(t.data, t.data + t.capacity, data);
    }

    ~HashTable() {
        delete[] data;
    }

    void Swap(HashTable &t) {

        size_t tmp = capacity;
        capacity = t.capacity;
        t.capacity = tmp;

        tmp = size;
        size = t.size;
        t.size = tmp;

        tmp = loadFactor;
        loadFactor = t.loadFactor;
        t.loadFactor = tmp;

        std::list <Node<Key, Value>> *tmp1 = data;
        data = t.data;
        t.data = tmp1;
    }

    HashTable(HashTable &&t){ // move constructor;

        data = t.data;
        size=t.size;
        loadFactor = t.loadFactor;

        t.data = nullptr;
        t.size = 0;
        t.capacity = defaultCapacity;
        t.loadFactor = 0;
    }
    HashTable &operator=(const HashTable &t) {
        if (this != &t) {
            std::cout<<"privet mame"<<std::endl;
            delete[] data;
            size = t.size;
            capacity = t.capacity;
            loadFactor = t.loadFactor;
            data = new std::list<Node<Key,Value> >[capacity];
            std::cout<<"privet mame"<<std::endl;
            for(size_t i = 0;i< capacity;i++)
            //    data[i] = t.data[i];
                std::copy(t.data[i].begin(), t.data[i].end(), data[i].begin());
        }
        return *this;
    }

    //  HashTable& operator = (HashTable&&); // move operator;
    void Clear() { //clear fields
        delete[] data;
        size = 0;
        capacity = defaultCapacity;
        loadFactor = 0;
        data = new std::list<Node<Key, Value>>[capacity];
    }

    bool Erase(const Key & k){//  erase field with key ; true if success
        if(!Contains(k))
            return false;
        size_t i = HashFunction(k)%capacity;
        Node<Key,Value> D (k);
        data[i].remove(D);
        size--;
        return true;
    }
    bool Insert(const Key& k, const Value& v) { // add field ; true if success
        if(Contains(k))
            return false;
        Node<Key,Value> D (k,v);
        size_t i = HashFunction(k)%capacity;
        std::cout<<"size do inserta = "<<size<<std::endl;
        data[i].push_back(D); // сheck for push???
        size++;
        std::cout<<"capacity vnutri inserta = "<<capacity<<std::endl;
        loadFactor=size/capacity;
        if (loadFactor>HighLoadFactor)
            if (!Rehashing())
                return false;
        std::cout<<"size pered vihodom = "<<size<<std::endl;
        return true;
    }
    bool Contains(const Key& k) const { // checking value's availability with key
        //HashFunction y;
        Node<Key,Value> D =(k);
        //size_t i = y.HashCalculation(k) %capacity;
        size_t i = HashFunction(k)%capacity;
        return (std::find(data[i].begin(),data[i].end(),D)!=data[i].end());
    }
    Value& operator[](const Key& k) { //return key's  value; UNSAFE method;
        if (!Contains(k)) {
            Value Default;
            Insert(k,Default);
        }
        Node<Key,Value> D =(k);
        size_t i = HashFunction(k)%capacity;
        return std::find(data[i].begin(),data[i].end(),D)->Current;
    }
    Value& At(const Key& k) {// return key's value; if there is no value - throw exception
        if (Contains(k)) {
            Node<Key,Value> D =(k);
            size_t i = HashFunction(k)%capacity;
            return std::find(data[i].begin(),data[i].end(),D)->Current;
        }
        else
            throw 1;

    }
    const Value& At(const Key& k) const { // return key's value; if there is no value - throw exception
        if (Contains(k)) {
            Node<Key,Value> D =(k);
            size_t i = HashFunction(k) % capacity;
            return std::find(data[i].begin(),data[i].end(),D)->Current;
        }
        else
            throw 1;
    }
    size_t Size() const { // return current hashtable's size
        return size;
    }
    bool Empty() const { // true if empty
        return (size==0);
    }
    friend bool operator == (const HashTable& a,const HashTable& b) {
        return !(a!=b);
    }
    friend bool operator != (const HashTable& a,const HashTable& b ) {
        if (a.size!=b.size)
            return true;
        size_t counter = 0;
        for (size_t i = 0;i<a.capacity;i++) {
            size_t list_size = a.data[i].size();
            for(typename std::list<Node<Key,Value>>::iterator it = a.data[i].begin(); it!=a.data[i].end();++it) {
                for(typename std::list<Node<Key,Value>>::iterator itt = b.data[i].begin(); itt!=b.data[i].end();++itt) {
                    if (*it==*itt) {
                        counter++;
                        break;
                    }
                }
            }
            if (counter!=list_size)
                return true;
        }
        return false;
    }
private:
    size_t capacity = defaultCapacity;
    size_t size = 0;
    size_t loadFactor = 0;
    std::list < Node <Key,Value> > * data = nullptr;
    bool Rehashing() {
        std::cout<<"size vnutri rehesh"<<size<<std::endl;
        HashTable tmp((capacity*HighLoadFactor));
      //  tmp.size = size;
        std::cout<<tmp.size<<std::endl;
        for(size_t i = 0; i<capacity;i++) {
            for(typename std::list<Node<Key,Value>>::iterator it = data[i].begin(); it!=data[i].end();++it) {
                Node<Key, Value> D = data[i].back();
                tmp.Insert(D.CurrentKey, D.Current);
            }
        }
        Swap(tmp);
        std::cout<< capacity<<std::endl;
        std::cout<< tmp.capacity<<std::endl;
        return true;
    }
    static const size_t defaultCapacity = 2;
    static const size_t HighLoadFactor = 2;
};
#endif //HASHTABLE_TEMPLATE_TEMPLATE_HASH_TABLE_H
