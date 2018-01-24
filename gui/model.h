#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include"/home/ulyssess/CLionProjects/obertka_repo/16208_kutalev/core_war/loader.hpp"
class model : public QObject
{
    Q_OBJECT
public:
    explicit model(QObject *parent = 0);

signals:

public slots:
    void coreClear();
    void setSize(int size);
    void setRange(int range);
    void setWNumbers(int number);
    void load(int wnum, std::__cxx11::string *files,int size);
    void startGame();
    std::string getInstructionName(int pos);
private:
    MARS simulator;
    std::vector<Warrior> Warriors;
};

#endif // MODEL_H
