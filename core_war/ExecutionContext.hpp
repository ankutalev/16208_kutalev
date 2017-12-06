//
//
#ifndef CORE_WAR_EXECUTIONCONTEXT_HPP
#define CORE_WAR_EXECUTIONCONTEXT_HPP
class ExecutionContext;
#include "mars.h"

class ExecutionContext {
public:
  ExecutionContext(MARS &in, CircularBuffer &q, CircularBuffer::Iterator *it)
      : Simulator(&in), Queue(&q), it(it) {}
  void setA(int which, int what);
  void setB(int which, int what);
  int getA(int which) const;
  int getB(int which) const;
  int getCurrentAddress() const;
  void SetOffsets(Data &in);
  void SetOffset(Mods mod, int operand, int *off);
  void DeleteFromQueue();
  void AddToQueue(int);
  void ChangeCommand(int from, int which);
  void ForwardQueue();
  void ChangeCurrentFlowAddress(int Address);
  const std::string &getCurrentWarriorName() const;
  bool isInstructionsEqual(int a, int b);

private:
  MARS *Simulator = nullptr;
  CircularBuffer *Queue = nullptr;
  CircularBuffer::Iterator *it = nullptr;
};

#endif // CORE_WAR_EXECUTIONCONTEXT_HPP
