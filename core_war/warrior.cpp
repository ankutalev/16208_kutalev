//
// Created by ulyssess on 24.10.17.
//



#include <cstring>
#include "warrior.hpp"
#include "factory.hpp"
#include "loader.h"
#include "memory.h"

void Warrior::Born(char *in,size_t limit) {
    std::cout << in;
    std::ifstream fin;
    fin.open(in);

    if (!fin.is_open())
        throw std::runtime_error("no file in directory!");
    else {
        std::cout << "WARRIOR!!!" << std::endl;
        std::string RedCode;
        std::string tmp;

        getline(fin, RedCode);
        if (RedCode != ";redcode-94")
            throw std::runtime_error("not_redcode-94_file");


        //try {

            while (fin >> RedCode && RedCode[0] == ';') {
                getline(fin, tmp);
                if (RedCode == ";author")
                    Author = tmp;
                if (RedCode == ";name")
                    Name = tmp;
            }


            if (RedCode == "ORG") {
                    getline(fin, tmp);
                    StartPosition = std::stoi(tmp);
                    fin>>RedCode;
            }

            size_t instruct_counter = 0;
            do   {  // getting Opcode
                Instruction *a = Factory::get_instance()->create(RedCode); // try to create

                fin >> tmp; // getting AFIELD

                if (Instruction::IsAmodAllowed(tmp[0])) {  // checking for amod
                    a->AOperandMod = static_cast<Mods >(tmp[0]);
                    a->AOperand = std::stoi(tmp.substr(1, tmp.length() - 1));
                } else
                    a->AOperand = std::stoi(tmp.substr(0, tmp.length()));

                fin >> tmp; // gettinf BFIELD

                if (Instruction::IsBmodAllowed(tmp[0])) {
                    a->BOperandMod = static_cast<Mods >(tmp[0]);
                    a->BOperand = std::stoi(tmp.substr(1, tmp.length() - 1));
                } else
                    a->BOperand = std::stoi(tmp.substr(0, tmp.length()));


                instruct_counter++;
                Instructions.push_back(a->Clone());
                getline(fin, tmp); // ignore comments

            } while (fin >> RedCode);
            if (instruct_counter == 0 || instruct_counter > limit)
                throw std::runtime_error("too much or zero commands in warrior!");
//        }
       // catch (std::exception) {
         //           throw std::runtime_error("incorrect file format");
        //}
    }
}

/* to do :
 * наделать создавалок под каждый мод,например,(MOV.AB, MOV, MOV.F, MOV.I, MOV.BA -отдельняя создавалка под каждую парашу), зарегать их все
 * считывать по словам и создавать команду; если команда без модифаера, то потом считать аргументы, проверить на коректность и определить модифаер
 * закинуть в вектор инструкций */