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

static void test_parse_null()
{
    leptjson::lept_value v;
    v.type = leptjson::LEPT_FALSE;
    EXPECT_EQ_INT(leptjson::LEPT_PARSE_OK, leptjson::lept_parse(&v, "null"));
    EXPECT_EQ_INT(leptjson::LEPT_NULL, leptjson::lept_get_type(&v));
}

void test_parse_expect_value()
{
    leptjson::lept_value v;
    v.type = leptjson::LEPT_FALSE;
    EXPECT_EQ_INT(leptjson::LEPT_PARSE_EXPECT_VALUE, lept_parse(&v, ""));
    EXPECT_EQ_INT(leptjson::LEPT_NULL, leptjson::lept_get_type(&v));
}

void test_parse_invalid_value()
{
    leptjson::lept_value v;
    v.type = leptjson::LEPT_FALSE;
    EXPECT_EQ_INT(leptjson::LEPT_PARSE_INVALID_VALUE, lept_parse(&v, "nul"));
    EXPECT_EQ_INT(leptjson::LEPT_NULL, leptjson::lept_get_type(&v));

    v.type = leptjson::LEPT_NULL;
    EXPECT_EQ_INT(leptjson::LEPT_PARSE_INVALID_VALUE, leptjson::lept_parse(&v, "?"));
    EXPECT_EQ_INT(leptjson::LEPT_NULL, leptjson::lept_get_type(&v));
}

void test_parse_root_not_singular()
{
    leptjson::lept_value v;
    v.type = leptjson::LEPT_FALSE;
    EXPECT_EQ_INT(leptjson::LEPT_PARSE_ROOT_NOT_SINGULAR, leptjson::lept_parse(&v, "null x"));
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

void test_parse()
{
    test_parse_null();
    test_parse_true();
    test_parse_false();
    test_parse_expect_value();
    test_parse_invalid_value();
    test_parse_root_not_singular();
}

int main()
{
    test_parse();
    std::cout << test_pass << "/" << test_count << " " << test_pass * 100.0 / test_count << "%" << std::endl;
    return main_ret;
}