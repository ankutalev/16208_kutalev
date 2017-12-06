//
//

#ifndef CORE_WAR_CIRCULARBUFFER_HPP
#define CORE_WAR_CIRCULARBUFFER_HPP
#include <list>
#include <iostream>
struct Flow {
    int* FlowCounter;
    int Address;
    std::string Author;
    std::string Name;
};
class CircularBuffer{
    friend class MARS;
public:
    class Iterator {
        friend class CircularBuffer;
    public:
        explicit Iterator (std::list<Flow>& d) : beg(d.begin()), cur(d.begin()), end(d.end()) {}
        Flow& operator *() const {
            return *cur;
        }
        Iterator& operator++() {
            if(++cur==end)
                cur=beg;
            return *this;
        }
    private:
        std::list<Flow>::iterator beg;
        std::list<Flow>::iterator cur;
        std::list<Flow>::iterator end;
    };


    CircularBuffer() = default;
    explicit CircularBuffer (size_t Counter) : FlowCounter(Counter) {}
    ~CircularBuffer() = default;
    void Insert (Flow&);
  //  void InsertPrev (std::list<Flow>::iterator,Flow&);
    void InsertPrev (Iterator&,Flow&);
    bool GameIsOn(size_t,size_t);
  //  std::list<Flow>::iterator DeleteCurrent(std::list<Flow>::iterator );
    void DeleteCurrent(Iterator&);
    Iterator begin();
    size_t GetFlowCounter() { return FlowCounter;}
private:
    std::list<Flow> data;
    int WarCounter=0;
    size_t FlowCounter = 1;
};


#endif //CORE_WAR_CIRCULARBUFFER_HPP
