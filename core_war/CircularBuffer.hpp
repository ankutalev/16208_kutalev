//
// Created by ulyssess on 26.10.17.
//

#ifndef CORE_WAR_CIRCULARBUFFER_HPP
#define CORE_WAR_CIRCULARBUFFER_HPP
#include "list"
#include <iostream>
struct Flow {
    Flow() {}
    Flow(const Flow& in):FlowCounter(in.FlowCounter),Address(in.Address),Author(in.Author),Name(in.Name) {}
    int* FlowCounter;
    int Address;
    std::string Author;
    std::string Name;

};
class CircularBuffer{
    friend class MARS;
public:
    CircularBuffer() {}
    CircularBuffer (size_t Counter) : FlowCounter(Counter) {}
    ~CircularBuffer(){}
    void Insert (Flow&);
    void InsertPrev (std::list<Flow>::iterator,Flow&);
    bool GameIsOn(size_t,size_t);
    std::list<Flow>::iterator DeleteCurrent(std::list<Flow>::iterator );
    std::list<Flow> data;
    int WarCounter=0;
    size_t FlowCounter = 1;
private:

};

/*class CBIterator : public std::iterator<std::input_iterator_tag,Flow>
{
    friend class CircularBuffer;
public:
   explicit CBIterator(const CBIterator &it ) : p(it.p){}
    bool operator != (CBIterator const& in) const {
        return p!=in.p;
    }
    CBIterator& operator++() {
        ++p;
        return *this;
    }
    typename CBIterator::reference operator *()const {
        return *p;
    }
private:
    Flow* p;
    explicit CBIterator(Flow* p): p(p){}

};*/

#endif //CORE_WAR_CIRCULARBUFFER_HPP
