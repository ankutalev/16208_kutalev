#include <iostream>
#include <list>
#include <algorithm>
#include "template_shared_ptr.h"
#include "template_hash_table.hpp"
#include <gtest/gtest.h>

static const int HashConst = 31;

size_t HashCalculation (const std::string& in ) {
        size_t length = in.length();
        size_t HashValue = in[length-1] % HashConst;
        for(int i=length-2;i>=0;i--)
            HashValue= HashValue*HashConst+in[i]%HashConst;
        return HashValue;
}
class Value {
public:
    Value(int x, int y):age(x),weight(y),yx(new int[age]),abc(new int[age]) {
    }
    Value() : age(100500),weight(-5),yx(new int[age]),abc(new int [10]) { }
    ~Value() { delete[] yx ;}
    Value(const Value& t) {
        age = t.age;
        weight=t.weight;
        yx= new int [age];
        std::copy(t.yx,t.yx+age,yx);
        abc=t.abc;
    }
    Value& operator = (const Value & t) {
        if (this!=&t) {
            delete [] yx;
            age=t.age;
            weight=t.weight;
            yx= new int [age];
            std::copy(t.yx,t.yx+age,yx);
            abc=t.abc;
        }
        return *this;
    }
    int age;
    int weight;
private:

    int* yx;
    mutable shared_ptr<int> abc;
};

size_t charhash(const char& x) {
    return x;
}

class Unit {
public:
    virtual std::string move(int x,int y){
        return "UNIT M O V E";
    }
    virtual ~Unit() {}
};

typedef Unit*(*function)();

class Zergling : public Unit {
public:
    std::string move (int x, int y) override {
        std::string a = "Zergling move!";
        return a;
    }
};
class Battlecruiser :public Unit {
    std::string move (int x, int y) override  {
        return "Battlecruiser move!";
    }
};
class SiegeTank: public Unit {
    std::string move (int x, int y) override   {
        return "SiegeTank move!";
    }
};

Unit* zerg () {return new Zergling;}
Unit* bc() {return new Battlecruiser;}
Unit* tank() {return new SiegeTank;}


TEST(Insert_and_empty_testing, poni) {
    HashTable<std::string,Value,&HashCalculation> X;
    Value Y;
    ASSERT_EQ(true,X.Empty());
    ASSERT_EQ(true, X.Insert("RAINBOW DASH",Y));
    ASSERT_EQ(false,X.Empty());
    ASSERT_EQ(true,X.Insert("APPLE JACK",Y));
    ASSERT_EQ(true,X.Insert("GREAT AND POWERFUL TRIXIE",Y));
    ASSERT_FALSE(X!=X);
}
TEST(Insert_and_empty_testing, charint) {
    HashTable<char,int,&charhash> X;
    Value Y;
    ASSERT_EQ(true,X.Empty());
    ASSERT_EQ(true, X.Insert('a',5));
    ASSERT_EQ(false,X.Empty());
    ASSERT_EQ(true,X.Insert('b',7));
    ASSERT_EQ(true,X.Insert('t',100500));
}TEST(Insert_and_empty_testing, starcraft) {
    HashTable<std::string, function, &HashCalculation> X;
    ASSERT_EQ(X.Insert("zergling",&zerg),true);
    ASSERT_EQ(X.Insert("battlecruiser",&bc),true);
    ASSERT_EQ(X.Insert("siegetank",&tank),true);
    ASSERT_EQ(X.Insert("zergling",&zerg),false);
}
TEST (getting_objects,starcraft) {
    HashTable<std::string, function, &HashCalculation> X;
    ASSERT_EQ(X.Insert("zergling",&zerg),true);
    ASSERT_EQ(X.Insert("battlecruiser",&bc),true);
    ASSERT_EQ(X.Insert("siegetank",&tank),true);
    Unit* tmp = X["zergling"]();
    std::string a = "Zergling move!";
    std::string b = tmp->move(0,0);
    ASSERT_EQ(b, a);
    delete tmp;
}
TEST(Contains,poni) {
    HashTable<std::string,Value,&HashCalculation> X;
    Value Y;
    ASSERT_EQ(X.Contains("RAINBOW DASH"),false);
    X.Insert("RAINBOW DASH",Y);
    ASSERT_EQ(X.Contains("RAINBOW DASH"),true);
    ASSERT_EQ(X.Contains("TWILIGHT SPARKLE"),false);
}
TEST(Contains,charint) {
    HashTable<char,int,&charhash> X;
    ASSERT_EQ(X.Contains('a'),false);
    X.Insert('a',100500);
    ASSERT_EQ(X.Contains('a'),true);
    ASSERT_EQ(X.Contains('t'),false);
}
TEST(Clear,poni) {
    HashTable<std::string,Value,&HashCalculation> X;
    Value Y;
    X.Insert("RARITY",Y);
    X.Clear();
    ASSERT_EQ(true,X.Empty());
}
TEST(Clear,charint) {
    HashTable<char,int,&charhash> X;
    X.Insert('a',-123);
    X.Clear();
    ASSERT_EQ(true,X.Empty());
}
TEST(Erase, poni) {
    HashTable<std::string,Value,&HashCalculation> X;
    Value Y(100500,20),T;
    X.Insert("RAINBOW DASH",T);
    X.Insert("FLUTTERSHY",Y);
    ASSERT_EQ(X.Erase("FLUTTERSHY"),true);
    ASSERT_EQ(X.Erase("KAMA THE BULLET"),false);
    ASSERT_EQ(X.Contains("FLUTTERSHY"),false);
}
TEST(Erase, charint) {
    HashTable<char,int,&charhash> X;
    X.Insert('a',2);
    X.Insert(' ',3);
    ASSERT_EQ(X.Erase(' '),true);
    ASSERT_EQ(X.Erase('t'),false);
    ASSERT_EQ(X.Contains(' '),false);
}
TEST(BRACKETS,poni){
    HashTable<std::string,Value,&HashCalculation> X;
    const Value Y(3,5),D;
    X.Insert("RAINBOW DASH",Y);
    Value C = X.At("RAINBOW DASH");
    const Value g =  X.At("RAINBOW DASH");
    Value kama = X["KAMA THE BULLET"];
    ASSERT_EQ(C.age,Y.age);
    ASSERT_EQ(C.weight,Y.weight);
    ASSERT_EQ(D.age,kama.age);
    ASSERT_EQ(D.weight,kama.weight);
    const HashTable<std::string,Value,&HashCalculation> T = X;
    const Value i =T.At("RAINBOW DASH");
}
TEST(BRACKETS,charint){
    HashTable<char,int,&charhash> X;
    X.Insert('a',2);
    int C = X['a'];
    int kama = 2;
    ASSERT_EQ(kama,C);
}
TEST(size,poni) {
    HashTable<std::string,Value,&HashCalculation>  X;
    Value Y;
    ASSERT_EQ(0,X.Size());
    X.Insert("RAINBOW DASH",Y);
    ASSERT_EQ(1,X.Size());
    ASSERT_EQ(true,X.Insert("APPLE JACK",Y));
    ASSERT_EQ(2,X.Size());
    X.Insert("GREAT AND POWERFUL TRIXIE",Y);
    ASSERT_EQ(3,X.Size());
    ASSERT_EQ(X.Insert("PINKIE PIE",Y),true);
    ASSERT_EQ(4,X.Size());
    X.Erase("PINKIE PIE");
    ASSERT_EQ(3,X.Size());
    X.Erase("KAMA THE BULLET");
    ASSERT_EQ(3,X.Size());
}
TEST(size,charint) {
    HashTable<char,int,&charhash>  X;
    ASSERT_EQ(0,X.Size());
    X.Insert('R',1);
    ASSERT_EQ(1,X.Size());
    ASSERT_EQ(true,X.Insert('A',2));
    ASSERT_EQ(2,X.Size());
    X.Insert('G',3);
    ASSERT_EQ(3,X.Size());
    ASSERT_EQ(X.Insert('P',4),true);
    ASSERT_EQ(4,X.Size());
    X.Erase('P');
    ASSERT_EQ(3,X.Size());
    X.Erase('B');
    ASSERT_EQ(3,X.Size());
}
TEST(at,poni) {
    HashTable<std::string,Value,&HashCalculation> X;
    Value Y(5,4);
    X.Insert("RAINBOW DASH",Y);
    Value R = X.At("RAINBOW DASH");
    ASSERT_EQ(5,R.age);
    ASSERT_EQ(4,R.weight);
    ASSERT_ANY_THROW(R = X.At("TWILIGHT SPARKLE"));
}
TEST(at,charint) {
    HashTable<char,int,&charhash> X;
    X.Insert('R',2);
    int R = X.At('R');
    ASSERT_EQ(2,R);
    ASSERT_ANY_THROW(R = X.At('g'));
}
TEST(equal,poni) {
    HashTable<std::string,Value,&HashCalculation>  X1,Y1,X2,Y2;
    Value P;
    X1.Insert("RAINBOW DASH",P);
    Y1.Insert("RAINBOW DASH",P);
    ASSERT_EQ(true,X1==Y1);
   X2.Insert("APPLE JACK",P);
    ASSERT_EQ(false,X2==X1);
    Y2=X2;
    ASSERT_EQ(true,X2==Y2);
    HashTable<std::string,Value,&HashCalculation> Z = Y2;
    ASSERT_EQ(Y2==Z,true);
    X2.Erase("APPLE JACK");
    Y1.Insert("QWERTY",P);
    ASSERT_TRUE(X2!=Y1);
}
TEST(equal,charint) {
    HashTable<char,int,&charhash>  X1,Y1,X2,Y2;
    int P = 2;
    X1.Insert('R',P);
    Y1.Insert('R',P);
    ASSERT_EQ(true,X1==Y1);
    X2.Insert('A',P);
    ASSERT_EQ(false,X2==X1);
    Y2=X2;
    ASSERT_EQ(true,X2==Y2);
    HashTable<char,int,&charhash> Z = Y2;
    ASSERT_EQ(Y2==Z,true);
    X2.Erase('A');
    ASSERT_EQ(false,X2==Y1);
}
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc,argv);

    return RUN_ALL_TESTS();
}