#include <primer/json.h>

#include <primer/core/json.h>

namespace pr {

JsonValue::JsonValue(std::nullptr_t)
{
    this->_json_value = pr_json_null_new();
}

JsonValue::JsonValue(bool value)
{
    this->_json_value = pr_json_bool_new(value);
}

JsonValue::JsonValue(int32_t value)
{
    this->_json_value = pr_json_int_new(value);
}

JsonValue::JsonValue(int64_t value)
{
    this->_json_value = pr_json_int_new(value);
}

JsonValue::JsonValue(double value)
{
    this->_json_value = pr_json_double_new(value);
}

JsonType JsonValue::type() const
{
    switch (this->_json_value.json_type) {
    case PR_JSON_TYPE_NULL:
        return JsonType::Null;
    case PR_JSON_TYPE_BOOL:
        return JsonType::Bool;
    case PR_JSON_TYPE_INT:
        return JsonType::Int;
    case PR_JSON_TYPE_DOUBLE:
        return JsonType::Double;
    case PR_JSON_TYPE_STRING:
        return JsonType::String;
    case PR_JSON_TYPE_ARRAY:
        return JsonType::Array;
    case PR_JSON_TYPE_OBJECT:
        return JsonType::Object;
    default:
        return JsonType::Null;
    }
}

bool JsonValue::to_bool() const
{
    return pr_json_value_to_bool(&this->_json_value);
}

int64_t JsonValue::to_int() const
{
    return pr_json_value_to_int(&this->_json_value);
}

double JsonValue::to_double() const
{
    return pr_json_value_to_double(&this->_json_value);
}


JsonArray::JsonArray()
{
    this->_json_value = pr_json_array_new();
}

JsonArray::JsonArray(std::initializer_list<pr::JsonValue> values)
{
    this->_json_value = pr_json_array_new();
}

}
