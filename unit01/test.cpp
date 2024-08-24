#include <stdio.h>

#include "leptjson.h"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality,expect,actual,format) \
    do{\
        test_count++;\
        if(equality)\
            test_pass++;
        else{\
            fprintf(stderr,"%s:%d: expect: "format "actual:" format "\n",__FILE__,__LINE__,expect,actual);\
            main_ret = 1;\
        }\
    }while(0)

#define EXPECT_EQ_INT(expect,actual) EXPECT_EQ_BASE((expect) == (actual),ecpect,actual,"%d")

static void test_parse_null(){
    lept_value v;
    v.type = LEPT_FALSE;
    ESPECT_EQ_INT(LEPT_PARSE_OK,lept_parse(&v,"null"));
}

void test_parse(){
    test_parse_null();
}


int main(){
    test_pase();
    cout <<test_pass<<"/"<<test_count<<" "<<test_pass*100.0/test_count<<"%"<<endl;
    return main_ret;
}