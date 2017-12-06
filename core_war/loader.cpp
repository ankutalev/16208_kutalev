//
//

#include "loader.hpp"
void Loader::loadCommands(std::vector<Warrior>& in, MARS& Simulator)
{
    for (size_t i = 0; i<Simulator.size; i++) {
        Simulator.Core.push_back(Simulator.Initial->Clone());
    }
    Flow tmp;
    for (Warrior& X : in) { // for each Warrior
        for (size_t i = 0; i<X.Instructions.size(); i++) {
            delete Simulator.Core[(Simulator.Position+i)%Simulator.size];
            Simulator.Core[(Simulator.Position+i)%Simulator.size] =
                    X.Instructions[i].get()->Clone(); // putting instructions in core
        }
        tmp.Name = X.Name;
        tmp.Author = X.Author;
        tmp.Address = (Simulator.Position+X.StartPosition)%Simulator.size;
        tmp.FlowCounter = &X.FlowCounter;
        Simulator.Flows.Insert(tmp);
        Simulator.Position = (Simulator.Position+Simulator.SeparationRange)%Simulator.size;
    }
}
