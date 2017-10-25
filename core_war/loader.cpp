//#include <vector>
//#include <iostream>
#include "loader.h"
#include "ctime"
void MARS::LoadCommands(std::vector<Warrior> &in) {
    Core.resize(size);
    for (size_t i = 0; i < size ; i++)
        Core[i] = &Initial; // initiate field with initial instruction

    size_t Position =rand()%size; // start position for 1st warrior
    zaglushka tmp;
    tmp.WNumber =0;
    tmp.ComAddess = Position;
    for (Warrior X : in ) { // for each Warrior
        for(size_t i = 0; i<X.Instructions.size();i++)
            Core[(Position+i)%size]=X.Instructions[i]; // putting instructions in core
        Potoki.push_back(tmp);
        StartingPositions.push_back(Position); // remember start position
        Position=(Position+SeparationRange) % size; //start position for new warrior
        tmp.WNumber++;
        tmp.ComAddess = Position;
    }
     for (size_t i = 0; i <StartingPositions.size() ; i++)
         std::cout<<StartingPositions[i]<<std::endl;
   // size_t a = StartingPositions[0];
    //Instruction HH = Core[a];
    //HH.Execution(Core,a);
    Core[StartingPositions[0]]->Execution(Core,StartingPositions[0]);
    Core[StartingPositions[0]+1]->Execution(Core,StartingPositions[0]+1);
    Core[StartingPositions[0]+2]->Execution(Core,StartingPositions[0]+2);
    Core[StartingPositions[0]+3]->Execution(Core,StartingPositions[0]+3);
    Core[StartingPositions[0]+4]->Execution(Core,StartingPositions[0]+4);


    std::cout<<"CHERT 5 RAZ POHODIL"<<std::endl;
    for (size_t i =0; i<size;i++)
        std::cout<<Core[i]->GettingCode(size)<<std::endl;
}
/*void MARS::Battle(std::vector<zaglushka> & potoks, size_t ties ) {
    size_t i=0,j=0,k=0;
    while (Core[potoks[i].ComAddess]->Execution(Core,size)) {
    }
}*/
/*void MARS::Battle(zaglushka test, size_t tie) {
    for (int i = 0; i <tie ; ++i) {
        Core[test.WNumber]->Execution(Core,&test);
    }
    for(size_t i;i<size;i++)
        std::cout<<Core[i]->GettingCode(size)<<std::endl;
}*/
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
    Instruction * Imp;
    Imp = new Mov_command (Opcodes:: MOV, Modifiers:: Not, Mods:: Dollar, Mods:: Dollar, 0, 1);
    std::vector<Instruction*> q;
    q.push_back(Imp);
    Warrior IMP (q);
    std::vector<Warrior> warriors;
    warriors.push_back(IMP);
    X.LoadCommands(warriors);
    std::cout<<"sffsaf";
    delete Imp;
    return 0;
}
