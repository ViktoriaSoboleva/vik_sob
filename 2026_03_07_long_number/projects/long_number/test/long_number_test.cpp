#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "long_number.hpp"

using namespace svr;

class Examples : public testing::Test{
	public:
		svr::LongNumber ex1 = svr::LongNumber("1");
		svr::LongNumber ex1_neg = svr::LongNumber("-1");
		svr::LongNumber ex1_copy = svr::LongNumber("1");
		svr::LongNumber ex1_neg_copy = svr::LongNumber("-1");
		
		
		svr::LongNumber ex2 = svr::LongNumber("2");
		svr::LongNumber ex2_neg = svr::LongNumber("-2");
		svr::LongNumber ex3 = svr::LongNumber("3");
		svr::LongNumber ex3_neg = svr::LongNumber("-3");
		svr::LongNumber ex4 = svr::LongNumber("4");
		svr::LongNumber ex4_neg = svr::LongNumber("-4");
		svr::LongNumber ex5 = svr::LongNumber("7");
		svr::LongNumber ex5_neg = svr::LongNumber("-7");
		svr::LongNumber ex6 = svr::LongNumber("10");
		svr::LongNumber ex6_neg = svr::LongNumber("-10");
		svr::LongNumber ex7 = svr::LongNumber("21");
		svr::LongNumber ex7_neg = svr::LongNumber("-21");
		svr::LongNumber big_ex = svr::LongNumber("1234567");
		svr::LongNumber big_ex_neg = svr::LongNumber("-1234567");
		svr::LongNumber big_ex_copy = svr::LongNumber("1234567");
		
		svr::LongNumber null = svr::LongNumber("0");
};

TEST_F(Examples, EQ_Test) {
    EXPECT_EQ(ex1, ex1_copy); // +1 == +1
    EXPECT_EQ(ex1_neg, ex1_neg_copy); // -1 == -1
    EXPECT_FALSE(ex1 == ex1_neg); // +1 == -1 (false)
    EXPECT_FALSE(big_ex_neg == big_ex); // -1234567 == +1234567 (false)
    EXPECT_EQ(big_ex, big_ex_copy); // big ex
}

TEST_F(Examples, NE_Test) {
    EXPECT_NE(ex1, ex1_neg); // +1 != -1
    EXPECT_NE(big_ex_neg, ex1); // -1234567 != +1
    EXPECT_FALSE(ex1 != ex1_copy); // +1 != +1 (false)
    EXPECT_FALSE(ex1_neg != ex1_neg_copy); // -1 != -1 (false)
    
    EXPECT_NE(ex2, ex3); // low ex
    EXPECT_NE(ex4, big_ex); // big ex
    EXPECT_NE(big_ex_neg, big_ex); // big negative ex
}

TEST_F(Examples, Gt_Test) {
    EXPECT_GT(ex1, ex1_neg); // +1 > -1
    EXPECT_FALSE(ex2_neg > ex1); // -2 > +1 (false)
    EXPECT_GT(ex5, ex3); // +7 > +3
    EXPECT_FALSE(ex3 > ex5); // +3 > +7 (false)
    EXPECT_FALSE(ex1 > ex1_copy); // +1 > +1 (false)
    EXPECT_GT(ex2_neg, ex3_neg); // -3 > -2
    EXPECT_FALSE(ex3_neg > ex2_neg); // -2 > -3 (false)
    EXPECT_FALSE(ex1_neg > ex1_neg_copy); // -1 > -1 (false)
    
    EXPECT_GT(big_ex, big_ex_neg); // big ex
}

TEST_F(Examples, Lt_Test) {
    EXPECT_LT(ex1_neg, ex1); // -1 < +1
    EXPECT_FALSE(ex1 < ex2_neg); // +1 < -2 (false)
    EXPECT_LT(ex3, ex5); // +3 < +7
    EXPECT_FALSE(ex5 < ex3); // +7 < +3 (false)
    EXPECT_FALSE(ex1 < ex1_copy); // +1 < +1 (false)
    EXPECT_LT(ex3_neg, ex2_neg); // -3 < -2
    EXPECT_FALSE(ex2_neg < ex3_neg); // -3 < -2 (false)
    EXPECT_FALSE(ex1_neg < ex1_neg_copy); // -1 < -1 (false)
    
    EXPECT_LT(big_ex_neg, big_ex); // big ex
}

TEST_F(Examples, Add_Test) {
    EXPECT_EQ(ex5, ex3 + ex4); // 3 + 4 = 7 
    EXPECT_EQ(ex6, ex5 + ex3); // 7 + 3 = 10

    EXPECT_EQ(ex5_neg, ex3_neg + ex4_neg); // -3 + -4 = -7
    EXPECT_EQ(ex6_neg, ex5_neg + ex3_neg); // -7 + -3 = -10
    
    EXPECT_EQ(ex4, ex5 + ex3_neg); // 7 + -3 = 4
    EXPECT_EQ(ex5_neg, ex6_neg + ex3); // -10 + 3 = -7
    
    svr::LongNumber sum = svr::LongNumber("1234569");
    EXPECT_EQ(sum, big_ex + ex2); // 1234567 + 2 = 1234569
}
TEST_F(Examples, Sub_Test) {
	EXPECT_EQ(ex5, ex6 - ex3); // 10 - 3 = 7
	EXPECT_EQ(ex1_neg, ex3 - ex4); // 3 - 4 = -1
	
    EXPECT_EQ(ex4_neg, ex5_neg - ex3_neg); // -7 - -3 = -4
    EXPECT_EQ(ex3, ex5_neg - ex6_neg); // -7 - -10 = 3
	
	EXPECT_EQ(ex6_neg, ex3_neg - ex5); // -3 - 7 = -10 
    EXPECT_EQ(ex6, ex5 - ex3_neg); // 7 - -3 = 10

    svr::LongNumber sub = svr::LongNumber("1234565");
    EXPECT_EQ(sub, big_ex - ex2); // 1234567 - 2 = 12345695
}

TEST_F(Examples, Mul_Test) {
    EXPECT_EQ(ex7, ex3 * ex5); // 3 * 7 = 21
    EXPECT_EQ(ex2, ex2 * ex1); // 2 * 1 = 2
    
    EXPECT_EQ(ex7, ex5_neg * ex3_neg); // -7 * -3 = 21
    EXPECT_EQ(ex2, ex1_neg * ex2_neg); // -1 * -2 = 2
    
    EXPECT_EQ(ex7_neg, ex5_neg * ex3); // -7 * 3 = -21
    EXPECT_EQ(ex2_neg, ex2 * ex1_neg); // 2 * -1 = -2

    svr::LongNumber mul = svr::LongNumber("2469134");
    EXPECT_EQ(mul, ex2 * big_ex); // 2 * 1234567 = 2469134
}

TEST_F(Examples, Div_Test) {
    EXPECT_EQ(ex5, ex7 / ex3); // 21 / 3 = 7
	EXPECT_EQ(null, ex1 / ex2); // 1 / 2 = 0
	EXPECT_EQ(ex2, ex2 / ex1); // 2 / 1 = 2
	
	EXPECT_EQ(ex2, ex5_neg / ex3_neg); // -7 / -3 = 2
	EXPECT_EQ(null, ex3_neg / ex4_neg); // -3 / -4 = 0
	
	EXPECT_EQ(ex5_neg, ex7_neg / ex3); // -21 / 3 = -7
	EXPECT_EQ(ex3_neg, ex5 / ex2_neg); // 7 / -2 = -3
	EXPECT_EQ(ex3_neg, ex5_neg / ex2); // -7 / 2 = -3
	EXPECT_EQ(null, ex4_neg / ex5); // -4 / 7 = 0
	EXPECT_EQ(null, ex4 / ex5_neg); // 4 / -7 = 0

    svr::LongNumber div = svr::LongNumber("617283");
    EXPECT_EQ(div, big_ex / ex2); // 1234567 / 2 = 617283
}

TEST_F(Examples, Rem_Test) {
    EXPECT_EQ(ex3, ex5 % ex4); // 7 % 4 = 3
	EXPECT_EQ(null, ex7 % ex3); // 21 % 3 = 0
	EXPECT_EQ(ex3, ex3 % ex4); // 3 % 4 = 3
	
	EXPECT_EQ(ex1_neg, ex5_neg % ex3_neg); // -7 % -3 = -1
	EXPECT_EQ(ex3_neg, ex3_neg % ex4_neg); // -3 % -4 = -4
	
	EXPECT_EQ(ex1, ex1 % ex5_neg); // 1 % -7 = 1
	EXPECT_EQ(ex1, ex5 % ex2_neg); // 7 % -2 = 1
	EXPECT_EQ(ex6, ex6 % ex7_neg); // 10 % -21 = 10
	EXPECT_EQ(ex1_neg, ex4_neg % ex3); // -4 % 3 = -1
	EXPECT_EQ(ex5_neg, ex5_neg % ex7_neg); // -7 % -21 = -7

    svr::LongNumber rem = svr::LongNumber("1");
    EXPECT_EQ(rem, big_ex % ex2); // 1234567 % 2 = 1
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}