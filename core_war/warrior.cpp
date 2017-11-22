//
// Created by ulyssess on 24.10.17.
//

#include "warrior.hpp"
#include "factory.hpp"
#include "loader.h"
#include "memory.h"
#include <cstring>

void Warrior::Born(char *in, size_t limit) {
  std::ifstream fin;
  fin.open(in);
  if (!fin.is_open())
    throw std::runtime_error("no file in directory!");
  else {
    size_t LineCounter = 0;
    std::string RedCode;
    std::string tmp;
    getline(fin, RedCode);
    LineCounter++;
    if (RedCode != ";redcode-94")
      throw std::runtime_error("not_redcode-94_file");

    while (fin >> RedCode && RedCode[0] == ';') {
      getline(fin, tmp);
      LineCounter++;
      if (RedCode == ";author")
        Author = tmp;
      if (RedCode == ";name")
        Name = tmp;
    }

    if (RedCode == "ORG") {
      getline(fin, tmp);
      LineCounter++;
      StartPosition = std::stoi(tmp);
      fin >> RedCode;
    }
    size_t instruct_counter = 0;
    try {
      do { // getting Opcode
        std::shared_ptr<Instruction> a;
        a.reset(Factory::get_instance()->create(RedCode));

        fin >> tmp; // getting AFIELD

        if (Instruction::IsModAllowed(tmp[0])) { // checking for amod
          a.get()->AOperandMod = static_cast<Mods>(tmp[0]);
          a.get()->AOperand = std::stoi(tmp.substr(1, tmp.length() - 1));
        } else
          a.get()->AOperand = std::stoi(tmp.substr(0, tmp.length()));

        fin >> tmp; // gettinf BFIELD

        if (Instruction::IsModAllowed(tmp[0])) {
          a.get()->BOperandMod = static_cast<Mods>(tmp[0]);
          a.get()->BOperand = std::stoi(tmp.substr(1, tmp.length() - 1));
        } else
          a.get()->BOperand = std::stoi(tmp.substr(0, tmp.length()));

        instruct_counter++;
        Instructions.push_back(a);
        getline(fin, tmp); // ignore comments
        LineCounter++;
      } while (fin >> RedCode);
    }

    catch (std::exception &x) {
      std::string c = "Invalid command at ";
      c += std::to_string(LineCounter + 1);
      c += " line in file ";
      c += in;
      throw std::runtime_error(c);
    }

    if (instruct_counter == 0 || instruct_counter > limit)
      throw std::runtime_error("too much or zero commands in warrior!");
    //        }
    // catch (std::exception) {
    //           throw std::runtime_error("incorrect file format");
    //}
  }
}

