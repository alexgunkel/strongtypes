#include "strong_types.h"

#include <gtest/gtest.h>

TEST(StrongTypesTest, testStrings) {
strong_types::Type<std::string, struct TypeA> foo{"foo"};
    strong_types::Type<std::string, struct TypeA> bar{"bar"};

EXPECT_EQ("foo", foo.get());
EXPECT_FALSE(foo == bar);
EXPECT_EQ((strong_types::Type<std::string, struct TypeA>{"foobar"}), foo + bar);
}

TEST(StrongTypesTest, testInteger) {
    strong_types::Type<int, struct TypeA> foo{10};
    strong_types::Type<int, struct TypeA> bar{2};

EXPECT_EQ(10, foo.get());
EXPECT_TRUE(foo != bar);
EXPECT_EQ((strong_types::Type<int, struct TypeA>{12}), foo + bar);
}

TEST(StrongTypesTest, testMacro) {
STRONG_TYPE(mytype, int);
STRONG_TYPE(secondtype, int);

mytype t1{2};
mytype t2{2};
secondtype s{3};

EXPECT_EQ(2, t1.get());
EXPECT_EQ(typeid(t1), typeid(t2));
EXPECT_NE(typeid(t1), typeid(s));
}

TEST(StrongTypesTest, testSize) {
STRONG_TYPE(strongLongInt, unsigned long int);
STRONG_TYPE(strongString, std::string);

EXPECT_EQ(sizeof(strongLongInt), sizeof(unsigned long int));
EXPECT_EQ(sizeof(strongString), sizeof(std::string));
}

TEST(StrongTypesTest, testConstructors) {
    STRONG_TYPE(testType, std::string);

    const testType orig{"a"};
    const testType c1 = orig;
    const testType c2{orig};

    testType c3;
    c3 = orig;

    EXPECT_EQ(orig, c1);
    EXPECT_EQ(orig, c2);
    EXPECT_EQ(orig, c3);
}

TEST(StrongTypesTest, testConversion) {
    CONVERTIBLE_STRONG_TYPE(conversionTestExplicit, std::string)
    IMPLICIT_STRONG_TYPE(conversionTestImplicit, std::string)

    conversionTestExplicit a{"foo"};
    conversionTestImplicit b{"bar"};

    auto cmpStrings = [](const std::string& wanted, const std::string& got) {
        EXPECT_EQ(wanted, got);
    };

    EXPECT_EQ("foo", std::string(a));
    cmpStrings("bar", b);

    std::string s = "foobar";
    conversionTestImplicit c = s;
    cmpStrings(s, c);
}

TEST(StrongTypesTest, constexprConstructable) {
    STRONG_TYPE(constExprTester, int)

    constexpr constExprTester t{2};
}

class TestForwarding {
private:
    int _v;
public:
    constexpr TestForwarding(const int &a, const int &b): _v{a+b} {};

    [[nodiscard]] int getSum() const {
        return _v;
    }
};

TEST(StrongTypesTest, testObject) {
    STRONG_TYPE(ObjectType, TestForwarding);

    ObjectType a{TestForwarding{2, 3}};
    constexpr auto b = strong_types::emplace<ObjectType, TestForwarding>(3, 4);

    EXPECT_EQ(5, a.get().getSum());
    EXPECT_EQ(7, b.get().getSum());
}
