#include "main.cpp"
#include <gtest/gtest.h>
TEST(Insert_and_empty_testing, poni) {
    HashTable X;
    Value Y;
    ASSERT_EQ(true,X.Empty());
    ASSERT_EQ(true, X.Insert("RAINBOW DASH",Y));
    ASSERT_EQ(false,X.Empty());
    ASSERT_EQ(true,X.Insert("APPLE JACK",Y));
    ASSERT_EQ(true,X.Insert("GREAT AND POWERFUL TRIXIE",Y));
}
TEST(Contains,poni) {
    HashTable X;
    Value Y;
    ASSERT_EQ(X.Contains("RAINBOW DASH"),false);
    X.Insert("RAINBOW DASH",Y);
    ASSERT_EQ(X.Contains("RAINBOW DASH"),true);
    ASSERT_EQ(X.Contains("TWILIGHT SPARKLE"),false);
}
TEST(Clear,poni) {
    HashTable X;
    Value Y;
    X.Insert("RARITY",Y);
    X.Clear();
    ASSERT_EQ(true,X.Empty());
}
TEST(Erase, poni) {
    HashTable X;
    Value Y(100500,20),T;
    X.Insert("RAINBOW DASH",T);
    X.Insert("FLUTTERSHY",Y);
    ASSERT_EQ(X.Erase("FLUTTERSHY"),true);
    ASSERT_EQ(X.Erase("KAMA THE BULLET"),false);
    ASSERT_EQ(X.Contains("FLUTTERSHY"),false);
}
TEST(BRACKETS,poni){
    HashTable X;
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
    HashTable X;
    Value Y;

    X.Insert("RAINBOW DASH",Y);
    X.Insert("APPLE JACK",Y);
    X.Insert("GREAT AND POWERFUL TRIXIE",Y);
    X.Insert("PINKIE PIE",Y);
    ASSERT_EQ(4,X.Size());
    X.Erase("PINKIE PIE");
    ASSERT_EQ(3,X.Size());
}
TEST(at,poni) {
    HashTable X;
    Value Y(5,4);
    X.Insert("RAINBOW DASH",Y);
    Value R = X.At("RAINBOW DASH");
    ASSERT_EQ(5,R.age);
    ASSERT_EQ(4,R.weight);
    ASSERT_ANY_THROW(R = X.At("TWILIGHT SPARKLE"));
}
TEST(equal,poni) {
    HashTable X1,Y1,X2,Y2;
    Value P;
    X1.Insert("RAINBOW DASH",P);
    Y1.Insert("RAINBOW DASH",P);
    ASSERT_EQ(true,X1==Y1);
    X2.Insert("APPLE JACK",P);
    ASSERT_EQ(false,X2==X1);
    Y2=X2;
    ASSERT_EQ(true,X2==Y2);
    HashTable Z = Y2;
    ASSERT_EQ(Y2==Z,true);
    X2.Erase("APPLE JACK");
    ASSERT_EQ(false,X2==Y1);
}
int main(int argc, char** argv)
{
    testing:: InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}


