// 养成好习惯
//_H__为结尾后缀，如果项目很大，这命名格式为 项目名称_目录_文件名称_H__
#ifndef LEPTJSON_H__
#define LEPTJSON_H__

// 枚举数据类型
enum lept_type
{
    LEPT_NULL,
    LEPT_FALSE,
    LEPT_TRUE,
    LEPT_NUMBER,
    LEPT_STRING,
    LEPT_ARRAY,
    LEPT_OBJECT
};

struct lept_value
{
    lept_type type;
};

// 返回值类型
enum
{
    LEPT_PARSE_OK = 0,
    LEPT_PARSE_EXPECT_VALUE,
    LEPT_PARSE_INVALID_VALUE,
    LEPT_PARSE_ROOT_NOT_SINGULAR
};

class LeptJson
{
private:
    /* data */
public:
    LeptJson(/* args */);
    ~LeptJson();

    static int lept_parse(lept_value *v, const char *json);

    static lept_type lept_get_type(const lept_value *v);
};

#endif // LEPTJSON_H__