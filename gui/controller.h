#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <map>
#include "model.h"
class MainWindow;
class MARS;
class controller
{
public:
    void repeat();
    void setModel(model* a);
    void setView(MainWindow &window,int argc, char** argv);
    void getChangedCell(const std::string& Name, int Address,bool isDanger);
    void checkStartOptions(int argc, std::string* files,int size,int separation);
    bool startDrawing();
    void warEnd(const std::string& win);
    void warriorRegister(const std::__cxx11::string &name,int Pos);
    static controller* get_instance();
    void signalToStart(int wnum, std::string* files,int size);
    std::string getWName(int pos);
    std::string getCommandName(int pos);
    void needInfo(const std::vector<std::string>& info,int x,int y);
    void update();
private:
     controller() = default;
     MainWindow* view;
     bool start = true;
     int argcc;
     char** argvv;
     std::map <std::string, int> Warriors;
     model* simulator;
     int wnum;
     std::string* mfiles;
     int msize;
};

#endif // CONTROLLER_H
