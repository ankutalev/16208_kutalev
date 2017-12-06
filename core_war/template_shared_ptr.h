//
//

#ifndef HASHTABLE_TEMPLATE_TEMPLATE_SHARED_PTR_H
#define HASHTABLE_TEMPLATE_TEMPLATE_SHARED_PTR_H
template <class T>
struct Counter {
    size_t count = 1;
    T* a_ = nullptr;
    Counter() :a_(nullptr){};
    Counter(T* a): a_(a) { }
    ~Counter() {
        count = 0;
        delete a_;
    }
};

template <class T>
class shared_ptr {
public:
    shared_ptr() {
        ctr = new Counter<T>(nullptr);
    }
    shared_ptr(T* a) {
        ctr = new Counter<T>(a);
    }
    shared_ptr(const shared_ptr &t) {
        ctr = t.ctr;
        ctr->count++;
    }
    ~shared_ptr() {
        if (ctr->count == 1)
            delete ctr;
        else
            ctr->count--;
    }
    shared_ptr& operator = (shared_ptr& t) {
        if (this!= &t) {
            if (ctr->count == 1)
                delete ctr;
            else
                ctr->count--;
            ctr = t.ctr;
            ctr->count++;
        }
        return *this;
    }
    T* release () {
        T* tmp = ctr->a_;
        ctr->count = 0 ;
        ctr->a_= nullptr;
        return tmp;
    }
    void reset(T* other) {
       if (ctr->count == 1) {
           delete ctr->a_;
           ctr->a_ = other;
       }
        else {
           ctr->count--;
           ctr = new Counter<T>(other);
       }

    }
    T* get () {
        return ctr->a_;
    }
private:
    Counter<T>* ctr = nullptr;
};
#endif //HASHTABLE_TEMPLATE_TEMPLATE_SHARED_PTR_H
