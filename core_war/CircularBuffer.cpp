#include "CircularBuffer.hpp"
#include "loader.h"

bool CircularBuffer::GameIsOn(size_t Count,size_t Tie) {

    return (WarCounter>1 && Count!=Tie );
}

std::list<Flow>::iterator CircularBuffer::DeleteCurrent(std::list<Flow>::iterator i) {
    int* tmp = (*i).FlowCounter;
    (*tmp)--;
    std::cout<<"SHETCHIK POTOKA U VOINA "<<(*i).Name<<"= "<<*tmp<<std::endl;
    if (!(*tmp)) {
        WarCounter--;
    }
    return data.erase(i);
}
void CircularBuffer::Insert(Flow& in) {
    WarCounter++;
    data.push_back(in);
}
void CircularBuffer::InsertPrev(std::list<Flow>::iterator it,Flow& in) {
    (*(*it).FlowCounter)++;
    std::cout<<(*it).Name<<"  rodilsya!!!po adresu "<<in.Address<< " vsego nas : = "<<*(*it).FlowCounter<<std::endl;
    data.insert(it,in);
}