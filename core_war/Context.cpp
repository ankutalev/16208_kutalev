
#include "ExecutionContext.hpp"

void ExecutionContext::SetOffset(Mods x, int Operand, int* AorB)
{
    int size = Simulator->size;
    (**it).Address %= size;
    if ((**it).Address<0)
        (**it).Address += size;
    switch (x) {
    case (Mods::Lattice):*AorB = 0;
        break;
    case (Mods::Star):*AorB = getA((**it).Address+Operand);
        break;
    case (Mods::Dog):*AorB = getB((**it).Address+Operand);
        break;
    case (Mods::Open):setA(((**it).Address+Operand), getA((**it).Address+Operand)-1);
        *AorB = getA((**it).Address+Operand);
        break;
    case (Mods::Close):*AorB = getA((**it).Address+Operand);
        setA(((**it).Address+Operand), getA((**it).Address+Operand)+1);
        break;
    case (Mods::More):*AorB = getB((**it).Address+Operand);
        setB(((**it).Address+Operand), getB((**it).Address+Operand)+1);
        break;
    case (Mods::Less):setB(((**it).Address+Operand), getB((**it).Address+Operand)-1);
        *AorB = getB((**it).Address+Operand);
        break;
    case (Mods::Dollar):
    case (Mods::Not):*AorB = Operand;
        break;
    }
    *AorB = (*AorB+(**it).Address);
    *AorB %= size;
    if (*AorB<0)
        (*AorB) += size;
}

void ExecutionContext::SetOffsets(Data& in)
{
    SetOffset(in.AOperandMod, in.AOperand, &in.AOffset);
    SetOffset(in.BOperandMod, in.BOperand, &in.BOffset);
}

void ExecutionContext::setA(int which, int what)
{
    int tmp = Simulator->size;
    Simulator->Core[(which%tmp+tmp)%tmp]->GetData().AOperand = what;
}

void ExecutionContext::setB(int which, int what)
{
    int tmp = Simulator->size;
    Simulator->Core[(which%tmp+tmp)%tmp]->GetData().BOperand = what;
}

void ExecutionContext::ChangeCommand(int from, int which)
{
    int tmp = Simulator->size;
    if ((which%tmp+tmp)%tmp==(from%tmp+tmp)%tmp)
        return;
    delete Simulator->Core[(which%tmp+tmp)%tmp];
    Simulator->Core[(which%tmp+tmp)%tmp] =
            Simulator->Core[(from%tmp+tmp)%tmp]->Clone();
}

int ExecutionContext::getA(int which) const
{
    int size = Simulator->size;
    return Simulator->Core[(which%size+size)%size]->GetData().AOperand;
}

int ExecutionContext::getB(int which) const
{
    int size = Simulator->size;
    return Simulator->Core[(which%size+size)%size]->GetData().BOperand;
}

const std::string& ExecutionContext::getCurrentWarriorName() const
{
    return (**it).Name;
}

void ExecutionContext::DeleteFromQueue() { Queue->DeleteCurrent(*it); }

void ExecutionContext::ForwardQueue()
{
    (**it).Address = ((**it).Address+1)%Simulator->size;
}

void ExecutionContext::ChangeCurrentFlowAddress(int Address)
{
    int size = Simulator->size;
    (**it).Address = (Address%size+size)%size;
}

int ExecutionContext::getCurrentAddress() const { return (**it).Address; }

bool ExecutionContext::isInstructionsEqual(int a, int b)
{
    int size = Simulator->size;
    return Simulator->Core[((a%size)+size)%size]==
            Simulator->Core[((b%size)+size)%size];
}

void ExecutionContext::AddToQueue(int Address)
{
    if (*(**it).FlowCounter<Queue->GetFlowCounter()) {
        Flow tmp = (**it);
        int size = Simulator->size;
        tmp.Address = (Address%size+size)%size;
        Queue->InsertPrev(*it, tmp);
    }
    else std::cout << "TOO MUCH FLOWS FOR " << (**it).Name << std::endl;
}
