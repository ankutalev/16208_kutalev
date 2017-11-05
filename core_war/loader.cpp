    //#include <vector>
//#include <iostream>
#include "loader.h"
#include "ctime"
//#include "jmp_command.cpp"
//#include "add_command.cpp"

//#include "dat_command.cpp"

//#include "mov_command.cpp"
#include "CircularBuffer.hpp"
#include "factory.hpp"
void MARS::LoadCommands(std::vector<Warrior> &in) {
    Core.resize(size);
    for (size_t i = 0; i < size ; i++) {
         Core[i] = Initial.Clone();
        //*Core[i] = Initial; // initiate field with initial instruction
    }
    size_t Position = rand()%size; // start position for 1st warrior
    Flow tmp;
    tmp.WarriorNumber =0;
   // Position = 0;
   // tmp.ComAddess = Position;
    for (Warrior X : in ) { // for each Warrior
        for(size_t i = 0; i<X.Instructions.size();i++) {
            delete Core[(Position + i) % size];
            Core[(Position + i) % size] = X.Instructions[i]->Clone(); // putting instructions in core
        }
        if (!tmp.WarriorNumber)
            tmp.Address = (Position)% size;
        else
            tmp.Address = Position;
        tmp.FlowCounter = &X.FlowCounter;
        Flows.Insert(tmp);
        //StartingPositions.push_back(Position); // remember start position
        Position=(Position+SeparationRange) % size; //start position for new warrior
        tmp.WarriorNumber++;
    }
   // size_t a = StartingPositions[0];
    //Instruction HH = Core[a];
    //HH.Execution(Core,a);
  //  Core[Flows[0].ComAddess]->Execution(Core,&Flows[0]);
  /*  Core[StartingPositions[0]+1]->Execution(Core,StartingPositions[0]+1);
    Core[StartingPositions[0]+2]->Execution(Core,StartingPositions[0]+2);
    Core[StartingPositions[0]+3]->Execution(Core,StartingPositions[0]+3);
    Core[StartingPositions[0]+4]->Execution(Core,StartingPositions[0]+4);
*/

   // std::cout<<"CHERT 5 RAZ POHODIL"<<std::endl;
    for (size_t i =0; i<size;i++)
        std::cout<<Core[i]->GettingCode(size)<<std::endl;
    Battle();

}
/*void MARS::Battle(std::vector<zaglushka> & potoks, size_t ties ) {
    size_t i=0,j=0,k=0;
    while (Core[potoks[i].ComAddess]->Execution(Core,size)) {
    }
}*/
/*void MARS::Battle() {
    zaglushka test = Potoki[0];
    for (int i = 0; i <TieCycles ; ++i) {
        Core[test.ComAddess]->Execution(Core,&test);
    }
    for(size_t i=0;i<size;i++)
        std::cout<<Core[i]->GettingCode(size)<<std::endl;
}*/
    void MARS::Battle() {
        std::cout<<Flows.WarCounter<<std::endl;
        auto it = Flows.data.begin();
        for (;it!=Flows.data.end();++it)
            std::cout<<(*it).Address<<" "<<(*it).WarriorNumber<<std::endl;
        //(*Core[2])=(*Core[0]);
       // Core[2]->Execution(Core,Flows,it);

        int i =0;
        std::cout<<(*it).Address<<std::endl;
        while (Flows.GameIsOn(i,TieCycles)) {
            if(it==Flows.data.end())
                it=Flows.data.begin();
            Core[(*it).Address]->Execution(Core,Flows,it);
            it++;
            i++;
            std::cout<<"POSLE "<<i<<"HODA SITUACIYA::"<<std::endl;
            for(size_t j=0;j<size;j++)
                std::cout<<Core[j]->GettingCode(size)<<std::endl;

        }
        if (i==TieCycles)
            std::cout<<"NO WINNER CHICKEN DEALER!!!!"<<std::endl;
        else {

            it = Flows.data.begin();
            std::cout<<"THE WINNER CHICKEN DEALER IS "<<(*it).WarriorNumber<<std::endl;
        }
        for(size_t i=0;i<size;i++)
            delete Core[i];
    }
int main () {
    srand(time(0));
    MARS X;
    /*Instruction Imp(Opcodes:: MOV,Modifiers:: Not,Mods:: Not, Mods:: Not, 0,1);

    std::vector<Instruction> q;
    q.push_back(Imp);
    Warrior IMP (q);
    std::vector<Warrior> warriors;
    warriors.push_back(IMP);

    X.LoadCommands(warriors); */
    //Dat_command Z;
    //  Mov_command Y;
    Instruction * Imp = Factory::get_instance()->create(Opcodes::MOV);
    Imp->AOperand = 0;
    Imp->BOperand = 1;
    Imp->BOperandMod = Mods::Dollar;
    Imp->AOperandMod = Mods::Dollar;
    Imp->OpcodeMod = Modifiers ::Not;
    std::vector<Instruction*> q;
    q.push_back(Imp);
    Warrior IMP (q);
    //Imp = new Mov_command (Opcodes:: MOV, Modifiers:: Not, Mods:: Dollar, Mods:: Dollar, 0, 1);
/*

    std::vector<Warrior> warriors;
    warriors.push_back(IMP);
    X.LoadCommands(warriors);
    std::cout<<"sffsaf";
 MEOWWWW <* ^_^ *>   delete Imp; */
   // Instruction *D1 = new Dat_command;
    std::vector<Instruction*> w;
 /*   Instruction* D1 = Factory::get_instance()->create(Opcodes::DAT);
    Instruction* D2 = Factory::get_instance()->create(Opcodes::ADD);
    D2->AOperand=5;
    D2->BOperand = -1;
    D2->AOperandMod = Mods::Lattice;
    D2->BOperandMod= Mods::Not;
   // Instruction* D2 = new Add_command(Opcodes:: ADD, Modifiers:: Not, Mods:: Lattice, Mods:: Not, 5, -1);
   // Instruction* D3 = new Mov_command(Opcodes:: MOV, Modifiers:: Not, Mods:: Lattice, Mods:: Dog, 0, -2);
    Instruction* D3 = Factory::get_instance()->create(Opcodes::MOV);
    D3->Body = Opcodes ::MOV;
    D3->OpcodeMod = Modifiers ::Not;
    D3->AOperand=-2;
    D3->BOperand = -2;
    D3->BOperandMod = Mods::Dog;
   // Instruction* D4 = new Jmp_command(Mods ::Not,-2);
    Instruction* D4 = Factory::get_instance()->create(Opcodes::JMP);
    D4->AOperand=-2;

    w.push_back(D1);
    w.push_back(D2);
    w.push_back(D3);
    w.push_back(D4);
    Warrior DWARF (w);*/
    std::vector<Warrior> warriors;
  //  warriors.push_back(DWARF);
    warriors.push_back(IMP);
    X.LoadCommands(warriors);
    std::cout<<"sffsaf";
  /*  while(q.GameIsOn()) {
        std::cout<<(*(*it).FlowCounter)<<std::endl;
        it++;
        if (it==q.data.end())
            it=q.data.begin();
        y++;
        if(y==3)
            it=q.DeleteCurrent(it);
    }*/
    //delete D1;
    //delete D2;
    //delete D3;
    //delete D4;
    delete Imp;
    return 0;
}
