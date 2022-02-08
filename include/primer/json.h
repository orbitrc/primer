#ifndef _PRIMER_JSON_H
#define _PRIMER_JSON_H

#include <stdint.h>

#include <tuple>
#include <initializer_list>

#include <primer/core/json.h>

namespace pr {

enum class JsonType {
    Null = PR_JSON_TYPE_NULL,
    Bool = PR_JSON_TYPE_BOOL,
    Int = PR_JSON_TYPE_INT,
    Double = PR_JSON_TYPE_DOUBLE,
    String = PR_JSON_TYPE_STRING,
    Array = PR_JSON_TYPE_ARRAY,
    Object = PR_JSON_TYPE_OBJECT,
};

class JsonArray;

class JsonValue
{
public:
    JsonValue(std::nullptr_t value);

    JsonValue(bool value);

    JsonValue(int32_t value);

    JsonValue(int64_t value);

    JsonValue(double value);

    JsonValue(const JsonArray& value);

    JsonType type() const;

    bool to_bool() const;

    int64_t to_int() const;

    double to_double() const;

private:
    pr_json_value _json_value;
};

class JsonArray
{
public:
    JsonArray();

    JsonArray(std::initializer_list<JsonValue> values);

private:
    pr_json_value _json_value;
};

} // namespace pr

#endif /* _PRIMER_JSON_H */
