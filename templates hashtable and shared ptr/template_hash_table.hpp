#ifndef HASHTABLE_TEMPLATE_TEMPLATE_HASH_TABLE_H
#define HASHTABLE_TEMPLATE_TEMPLATE_HASH_TABLE_H
template <class Key, class Value> struct Node {
  Node(const Key &k, const Value &v) : Current(v), CurrentKey(k){};
  explicit Node(const Key &k) : CurrentKey(k){};
  friend bool operator==(const Node &a, const Node &b) {
    return a.CurrentKey == b.CurrentKey;
  }
  Value Current;
  Key CurrentKey;
};
template <class Key, class Value, size_t (*HashFunction)(const Key &)>
class HashTable {
public:
  HashTable() : HashTable(defaultCapacity) {};
  explicit HashTable(size_t in)
      : size(0), capacity(in),
        data(new std::list<Node<Key, Value>>[capacity]){}; // constructor with
                                                           // any capacity
  HashTable(const HashTable &t) : size(t.size), capacity(t.capacity), data(new std::list<Node<Key, Value>>[capacity]) {                          // copy constructor
    std::copy(t.data, t.data + t.capacity, data);
  }
  ~HashTable() { delete[] data; }
  void Swap(HashTable &t) {
    std::swap(capacity, t.capacity);
    std::swap(size, t.size);
    std::swap(loadFactor, t.loadFactor);
    std::list<Node<Key, Value>> *tmp1 = data;
    data = t.data;
    t.data = tmp1;
  }
  HashTable &operator=(const HashTable &t) {
    if (this != &t) {
      delete[] data;
      size = t.size;
      capacity = t.capacity;
      loadFactor = t.loadFactor;
      data = new std::list<Node<Key, Value>>[capacity];
      std::copy(t.data, t.data + capacity, data);
    }
    return *this;
  }
  void Clear() { // clear fields
    delete[] data;
    size = 0;
    capacity = defaultCapacity;
    loadFactor = 0;
    data = new std::list<Node<Key, Value>>[capacity];
  }
  bool Erase(const Key &k) { //  erase field with key ; true if success
    if (!Contains(k))
      return false;
    size_t i = HashFunction(k) % capacity;
    Node<Key, Value> D(k);
    data[i].remove(D);
    size--;
    return true;
  }
  bool Insert(const Key &k, const Value &v) { // add field ; true if success
    if (Contains(k))
      return false;
    Node<Key, Value> D(k, v);
    size_t i = HashFunction(k) % capacity;
    data[i].push_back(D); // сheck for push???
    size++;
    loadFactor = static_cast<double>(size) / capacity;
    if (loadFactor > HighLoadFactor)
      if (!Rehashing())
        return false;
    return true;
  }
  bool Contains(const Key &k) const { // checking value's availability with key
    Node<Key, Value> D (k);
    size_t i = HashFunction(k) % capacity;
    return (std::find(data[i].begin(), data[i].end(), D) != data[i].end());
  }
  Value &operator[](const Key &k) {
    if (!Contains(k)) {
      Value Default;
      Insert(k, Default);
    }
    Node<Key, Value> D  (k);
    size_t i = HashFunction(k) % capacity;
    return std::find(data[i].begin(), data[i].end(), D)->Current;
  }
  Value &At(const Key &k) {
    if (Contains(k)) {
      Node<Key, Value> D (k);
      size_t i = HashFunction(k) % capacity;
      return std::find(data[i].begin(), data[i].end(), D)->Current;
    } else
      throw std::runtime_error("no key");
  }
  const Value &At(const Key &k)
      const { // return key's value; if there is no value - throw exception
    if (Contains(k)) {
      Node<Key, Value> D (k);
      size_t i = HashFunction(k) % capacity;
      return std::find(data[i].begin(), data[i].end(), D)->Current;
    } else
      throw std::runtime_error(k);
  }
  size_t Size() const { return size; }
  bool Empty() const { return (size == 0); }
  friend bool operator==(const HashTable &a, const HashTable &b) {
    if (a.capacity != b.capacity)
      return false;
    for (size_t i = 0; i < a.capacity; i++) {
      for (auto it = a.data[i].begin(); it != a.data[i].end(); ++it)
        if (!b.Contains((*it).CurrentKey))
          return false;
    }
    for (size_t i = 0; i < a.capacity; i++) {
      for (auto it = b.data[i].begin(); it != b.data[i].end(); ++it)
        if (!a.Contains((*it).CurrentKey))
          return false;
    }
    return true;
  }
  friend bool operator!=(const HashTable &a, const HashTable &b) {
    return !(a == b);
  }

private:
  size_t capacity = defaultCapacity;
  size_t size = 0;
  double loadFactor = 0;
  std::list<Node<Key, Value>> *data = nullptr;
  bool Rehashing() {
    HashTable tmp((capacity * HighLoadFactor));
    for (size_t i = 0; i < capacity; i++) {
      for (auto it = data[i].begin(); it != data[i].end(); ++it) {
        Node<Key, Value> D = (*it);
        tmp.Insert(D.CurrentKey, D.Current);
      }
    }
    Swap(tmp);
    return true;
  }
  static const size_t defaultCapacity = 1;
  static const size_t HighLoadFactor = 2;
};
#endif // HASHTABLE_TEMPLATE_TEMPLATE_HASH_TABLE_H
