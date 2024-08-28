// 养成好习惯
//_H__为结尾后缀，如果项目很大，这命名格式为 项目名称_目录_文件名称_H__
#ifndef LEPTJSON_H__
#define LEPTJSON_H__

namespace leptjson
{
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
        LEPT_PARSE_EXPECT_VALUE,      //若一个 JSON 只含有空白
        LEPT_PARSE_INVALID_VALUE,     //若值不是那三种字面值
        LEPT_PARSE_ROOT_NOT_SINGULAR  //若一个值之后，在空白之后还有其他字符
    };

    int lept_parse(lept_value *v, const char *json);

    lept_type lept_get_type(const lept_value *v);

} // namespace leptjson
#endif // LEPTJSON_H__