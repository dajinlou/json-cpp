#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "leptjson.h"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format)                                                           \
    do                                                                                                             \
    {                                                                                                              \
        test_count++;                                                                                              \
        if (equality)                                                                                              \
            test_pass++;                                                                                           \
        else                                                                                                       \
        {                                                                                                          \
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual); \
            main_ret = 1;                                                                                          \
        }                                                                                                          \
    } while (0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")
#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%.17g")

static void test_parse_null()
{
    leptjson::lept_value v;
    v.type = leptjson::LEPT_FALSE;
    EXPECT_EQ_INT(leptjson::LEPT_PARSE_OK, leptjson::lept_parse(&v, "null"));
    EXPECT_EQ_INT(leptjson::LEPT_NULL, leptjson::lept_get_type(&v));
}

void test_parse_true()
{
    leptjson::lept_value v;
    v.type = leptjson::LEPT_FALSE;
    // EXPECT_EQ_INT(leptjson::LEPT_TRUE, leptjson::lept_get_type(&v));
    EXPECT_EQ_INT(leptjson::LEPT_PARSE_OK, leptjson::lept_parse(&v, "true"));
    EXPECT_EQ_INT(leptjson::LEPT_TRUE, leptjson::lept_get_type(&v));
}

void test_parse_false()
{
    leptjson::lept_value v;
    v.type = leptjson::LEPT_TRUE;
    EXPECT_EQ_INT(leptjson::LEPT_PARSE_OK, leptjson::lept_parse(&v, "false"));
    EXPECT_EQ_INT(leptjson::LEPT_FALSE, leptjson::lept_get_type(&v));
}

#define TEST_NUMBER(expect, json)                                               \
    do                                                                          \
    {                                                                           \
        leptjson::lept_value v;                                                 \
        EXPECT_EQ_INT(leptjson::LEPT_PARSE_OK, leptjson::lept_parse(&v, json)); \
        EXPECT_EQ_INT(leptjson::LEPT_NUMBER, leptjson::lept_get_type(&v));      \
        EXPECT_EQ_DOUBLE(expect, leptjson::lept_get_number(&v));                \
    } while (0)

void test_parse_number()
{
    TEST_NUMBER(0.0, "0");
    TEST_NUMBER(0.0, "-0");
    TEST_NUMBER(0.0, "-0.0");
    TEST_NUMBER(1.0, "1");
    TEST_NUMBER(-1.0, "-1");
    TEST_NUMBER(1.5, "1.5");
    TEST_NUMBER(-1.5, "-1.5");
    TEST_NUMBER(3.1416, "3.1416");
    TEST_NUMBER(1E10, "1E10");
    TEST_NUMBER(1e10, "1e10");
    TEST_NUMBER(1E+10, "1E+10");
    TEST_NUMBER(1E-10, "1E-10");
    TEST_NUMBER(-1E10, "-1E10");
    TEST_NUMBER(-1e10, "-1e10");
    TEST_NUMBER(-1E+10, "-1E+10");
    TEST_NUMBER(-1E-10, "-1E-10");
    TEST_NUMBER(1.234E+10, "1.234E+10");
    TEST_NUMBER(1.234E-10, "1.234E-10");
    TEST_NUMBER(0.0, "1e-10000"); /* must underflow */

    TEST_NUMBER(1.0000000000000002, "1.0000000000000002");           /* the smallest number > 1 */
    TEST_NUMBER(4.9406564584124654e-324, "4.9406564584124654e-324"); /* minimum denormal */
    TEST_NUMBER(-4.9406564584124654e-324, "-4.9406564584124654e-324");
    TEST_NUMBER(2.2250738585072009e-308, "2.2250738585072009e-308"); /* Max subnormal double */
    TEST_NUMBER(-2.2250738585072009e-308, "-2.2250738585072009e-308");
    TEST_NUMBER(2.2250738585072014e-308, "2.2250738585072014e-308"); /* Min normal positive double */
    TEST_NUMBER(-2.2250738585072014e-308, "-2.2250738585072014e-308");
    TEST_NUMBER(1.7976931348623157e+308, "1.7976931348623157e+308"); /* Max double */
    TEST_NUMBER(-1.7976931348623157e+308, "-1.7976931348623157e+308");
}

#define TEST_ERROR(error, json)                                          \
    do                                                                   \
    {                                                                    \
        leptjson::lept_value v;                                          \
        v.type = leptjson::LEPT_FALSE;                                   \
        EXPECT_EQ_INT(error, leptjson::lept_parse(&v, json));            \
        EXPECT_EQ_INT(leptjson::LEPT_NULL, leptjson::lept_get_type(&v)); \
    } while (0)

void test_parse_expect_value()
{
    TEST_ERROR(leptjson::LEPT_PARSE_EXPECT_VALUE, "");
    TEST_ERROR(leptjson::LEPT_PARSE_EXPECT_VALUE, " ");
}

void test_parse_invalid_value()
{
    TEST_ERROR(leptjson::LEPT_PARSE_INVALID_VALUE, "nul");
    TEST_ERROR(leptjson::LEPT_PARSE_INVALID_VALUE, "?");

#if 1
    // invalid number
    TEST_ERROR(leptjson::LEPT_PARSE_INVALID_VALUE, "+0");
    TEST_ERROR(leptjson::LEPT_PARSE_INVALID_VALUE, "+1");
    TEST_ERROR(leptjson::LEPT_PARSE_INVALID_VALUE, ".123"); /* at least one digit before '.' */
    TEST_ERROR(leptjson::LEPT_PARSE_INVALID_VALUE, "1.");   /* at least one digit after '.' */
    TEST_ERROR(leptjson::LEPT_PARSE_INVALID_VALUE, "INF");
    TEST_ERROR(leptjson::LEPT_PARSE_INVALID_VALUE, "inf");
    TEST_ERROR(leptjson::LEPT_PARSE_INVALID_VALUE, "NAN");
    TEST_ERROR(leptjson::LEPT_PARSE_INVALID_VALUE, "nan");
#endif
}

void test_parse_root_not_singular()
{
    TEST_ERROR(leptjson::LEPT_PARSE_ROOT_NOT_SINGULAR, "null x");

#if 1
    // invalid number
    TEST_ERROR(leptjson::LEPT_PARSE_ROOT_NOT_SINGULAR, "0123"); // after zero shold be '.','E','e' or nothing
    TEST_ERROR(leptjson::LEPT_PARSE_ROOT_NOT_SINGULAR, "0x0");
    TEST_ERROR(leptjson::LEPT_PARSE_ROOT_NOT_SINGULAR, "0x123");
#endif
}

void test_parse_number_too_big()
{
#if 1
    TEST_ERROR(leptjson::LEPT_PARSE_NUMBER_TOO_BIG, "1e309");
    TEST_ERROR(leptjson::LEPT_PARSE_NUMBER_TOO_BIG, "-1e309");
#endif
}

void test_parse()
{
    test_parse_null();
    test_parse_true();
    test_parse_false();
    test_parse_number();
    test_parse_expect_value();
    test_parse_invalid_value();
    test_parse_root_not_singular();
    test_parse_number_too_big();
}

int main()
{
    test_parse();
    std::cout << test_pass << "/" << test_count << " " << test_pass * 100.0 / test_count << "%" << std::endl;
    return main_ret;
}