#include "CircularBuffer.hpp"
#include "loader.h"

bool CircularBuffer::GameIsOn(size_t Count, size_t Tie) {

  return (WarCounter > 1 && Count != Tie);
}

/*std::list<Flow>::iterator
CircularBuffer::DeleteCurrent(std::list<Flow>::iterator i) {
    int* tmp = (*i).FlowCounter;
    (*tmp)--;
    std::cout<<"SHETCHIK POTOKA U VOINA "<<(*i).Name<<"= "<<*tmp<<std::endl;
    if (!(*tmp)) {
        WarCounter--;
    }
    return data.erase(i);
}*/
void CircularBuffer::InsertPrev(Iterator &it, Flow &in) {
  (*(*it).FlowCounter)++;
  std::cout << (*it).Name << "  was born!!!at address " << in.Address
            << " Total of it : = " << *(*it).FlowCounter << std::endl;
  data.insert(it.cur, in);
}
void CircularBuffer::DeleteCurrent(CircularBuffer::Iterator &i) {
  (*(*i).FlowCounter)--;
  std::cout << "SHETCHIK POTOKA U VOINA " << (*i).Name << "= "
            << *(*i).FlowCounter << std::endl;
  if (!(*(*i).FlowCounter)) {
    WarCounter--;
  }
  if (i.cur == i.beg) {
    std::cout << "piimav na geydzucu!" << std::endl;
    ++i.beg;
  }
  i.cur = data.erase(i.cur);
}
void CircularBuffer::Insert(Flow &in) {
  WarCounter++;
  data.push_back(in);
}
/*void CircularBuffer::InsertPrev(std::list<Flow>::iterator it,Flow& in) {
    (*(*it).FlowCounter)++;
    std::cout<<(*it).Name<<"  rodilsya!!!po adresu "<<in.Address<< " vsego nas :
= "<<*(*it).FlowCounter<<std::endl;
    data.insert(it,in);
}*/
CircularBuffer::Iterator CircularBuffer::begin() { return Iterator(data); }