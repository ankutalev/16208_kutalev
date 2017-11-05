#include "CircularBuffer.hpp"
#include "loader.h"

bool CircularBuffer::GameIsOn(size_t Count,size_t Tie) {

    return (WarCounter>=1 && Count!=Tie );
}

std::list<Flow>::iterator CircularBuffer::DeleteCurrent(std::list<Flow>::iterator i) {
    int* tmp = (*i).FlowCounter;
    (*tmp)--;
    if (!(*tmp))
        WarCounter--;
    return data.erase(i);
}
void CircularBuffer::Insert(Flow& in) {
    WarCounter++;
    data.push_back(in);
}
void CircularBuffer::InsertPrev(std::list<Flow>::iterator it,Flow& in) {
    (*in.FlowCounter)++;
    data.insert(it,in);
}