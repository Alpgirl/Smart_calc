#include <gtest/gtest.h>
extern "C"
{
	#include "../back/calc.h"
}
TEST(CalcTest0, CalcCheck)
{
        int size = 0;
        token *infix = parse_str("3-2", &size);
        token *postfix = to_polish(infix, size);
        double res = calc(postfix, 0, size);
        EXPECT_FLOAT_EQ(res,1.0);
        free(infix);
        free(postfix);
}
TEST(CalcTest1, CalcCheck)
{
        int size = 0;
        token *infix = parse_str("-2^2^2*3 * sqrt(4)", &size);
        token *postfix = to_polish(infix, size);
        double res = calc(postfix, 0, size);
        EXPECT_FLOAT_EQ(res,-96.0);
        free(infix);
        free(postfix);
}
TEST(CalcTest2, CalcCheck)
{
        int size = 0;
        token *infix = parse_str("-(sin(0))", &size);
        token *postfix = to_polish(infix, size);
        double res = calc(postfix, 0, size);
        EXPECT_FLOAT_EQ(res,0.0);
        free(infix);
        free(postfix);
}
TEST(CalcTest3, CalcCheck)
{
        int size = 0;
        token *infix = parse_str("log(2*5)*2", &size);
        token *postfix = to_polish(infix, size);
        double res = calc(postfix, 0, size);
        EXPECT_EQ(res,2);
        free(infix);
        free(postfix);
}
TEST(CalcTest4, CalcCheck)
{
        int size = 0;
        token *infix = parse_str("cossin0", &size);
        token *postfix = to_polish(infix, size);
        double res = calc(postfix, 0, size);
        EXPECT_EQ(res,1);
        free(infix);
        free(postfix);
}
TEST(CalcTest5, CalcCheck)
{
        int size = 0;
        token *infix = parse_str("sqrt4^2", &size);
        token *postfix = to_polish(infix, size);
        double res = calc(postfix, 0, size);
        EXPECT_EQ(res,4);
        free(infix);
        free(postfix);
}
TEST(CalcTest6, CalcCheck)
{
        int size = 0;
        token *infix = parse_str("ln0", &size);
        token *postfix = to_polish(infix, size);
        double res = calc(postfix, 0, size);
        EXPECT_NE(res,res);
        free(infix);
        free(postfix);
}
TEST(CalcTest7, CalcCheck)
{
        int size = 0;
        token *infix = parse_str("1 / 0", &size);
        token *postfix = to_polish(infix, size);
        double res = calc(postfix, 0, size);
        EXPECT_NE(res,res);
        free(infix);
        free(postfix);
}
TEST(CalcTest8, CalcCheck)
{
        int size = 0;
        token *infix = parse_str("asin(0.9+0.9)", &size);
        token *postfix = to_polish(infix, size);
        double res = calc(postfix, 0, size);
        EXPECT_NE(res,res);
        free(infix);
        free(postfix);
}
TEST(CalcTest9, CalcCheck)
{
        int size = 0;
        token *infix = parse_str("sqrt(-1)", &size);
        token *postfix = to_polish(infix, size);
        double res = calc(postfix, 0, size);
        EXPECT_NE(res,res);
        free(infix);
        free(postfix);
}
TEST(CalcTest10, CalcCheck)
{
        int size = 0;
        token *infix = parse_str("+3 mod 2 mod 1 + 1 + acos1 + atan0 + tan(0)", &size);
        token *postfix = to_polish(infix, size);
        double res = calc(postfix, 0, size);
        EXPECT_EQ(res,1);
        free(infix);
        free(postfix);
}
TEST(CalcTest11, CalcCheck)
{
        int size = 0;
        token *infix = parse_str("0.5*x", &size);
        token *postfix = to_polish(infix, size);
        double res = calc(postfix, 2, size);
        EXPECT_EQ(res,1);
        free(infix);
        free(postfix);
}

