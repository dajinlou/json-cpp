#include "leptjson.h"

LeptJson::LeptJson(/* args */)
{
}

LeptJson::~LeptJson()
{
}

inline int LeptJson::lept_parse(lept_value *v, const char *json)
{
    return 0;
}

inline lept_type LeptJson::lept_get_type(const lept_value *v)
{
    return lept_type();
}
