#include <agu/strong_types.h>

#include <gtest/gtest.h>
#include <string>

TEST(NumericOperations, arithmetics) {
    STRONG_TYPE(meter, int);

    constexpr meter a{5};
    constexpr meter b{4};
    constexpr char c{3};
    constexpr long d{100};

    EXPECT_EQ(meter{9}, a + b);
    EXPECT_EQ(meter{15}, a * c);
    EXPECT_EQ(meter{400}, d * b);
}

TEST(Operations, concatenation) {
    STRONG_TYPE(name, std::string);

    const name a{"foo"};
    const name b{"bar"};

    EXPECT_EQ(name{"foobar"}, a + b);
    EXPECT_EQ(name{"foofoobar"}, 2 * a + b);
}
