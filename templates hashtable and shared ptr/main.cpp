#include <iostream>
#include <list>
#include <algorithm>
#include "template_shared_ptr.h"
#include "template_hash_table.h"
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
        std::cout<<"ya tuta"<<std::endl;
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
            yx= new int [age];
            std::copy(t.yx,t.yx+age,yx);
            abc=t.abc;
        }
        return *this;
    }
    void Show () {
        std::cout<< age<<std::endl;
        std::cout<<weight<<std::endl;
    }
    int age;
    int weight;
private:

    int* yx;
    mutable shared_ptr<int> abc;
};
TEST(Insert_and_empty_testing, poni) {
    HashTable<std::string,Value,&HashCalculation> X;
    Value Y;
    ASSERT_EQ(true,X.Empty());
    ASSERT_EQ(true, X.Insert("RAINBOW DASH",Y));
    ASSERT_EQ(false,X.Empty());
    ASSERT_EQ(true,X.Insert("APPLE JACK",Y));
    ASSERT_EQ(true,X.Insert("GREAT AND POWERFUL TRIXIE",Y));
}
TEST(Contains,poni) {
    HashTable<std::string,Value,&HashCalculation> X;
    Value Y;
    ASSERT_EQ(X.Contains("RAINBOW DASH"),false);
    X.Insert("RAINBOW DASH",Y);
    ASSERT_EQ(X.Contains("RAINBOW DASH"),true);
    ASSERT_EQ(X.Contains("TWILIGHT SPARKLE"),false);
}
TEST(Clear,poni) {
    HashTable<std::string,Value,&HashCalculation> X;
    Value Y;
    X.Insert("RARITY",Y);
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
TEST(BRACKETS,poni){
    HashTable<std::string,Value,&HashCalculation> X;
    Value Y(3,5),D;
    X.Insert("RAINBOW DASH",Y);
    Value C = X["RAINBOW DASH"];
    Value kama = X["KAMA THE BULLET"];
    ASSERT_EQ(C.age,Y.age);
    ASSERT_EQ(C.weight,Y.weight);
    ASSERT_EQ(D.age,kama.age);
    ASSERT_EQ(D.weight,kama.weight);
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
TEST(at,poni) {
    HashTable<std::string,Value,&HashCalculation> X;
    Value Y(5,4);
    X.Insert("RAINBOW DASH",Y);
    Value R = X.At("RAINBOW DASH");
    ASSERT_EQ(5,R.age);
    ASSERT_EQ(4,R.weight);
    ASSERT_ANY_THROW(R = X.At("TWILIGHT SPARKLE"));
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
    ASSERT_EQ(false,X2==Y1);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc,argv);

    return RUN_ALL_TESTS();
}