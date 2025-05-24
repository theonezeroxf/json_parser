#include "../json/value.hpp"
#include "../json/exceptions.hpp"
#include <variant>

// Implementation of the Value class methods
using namespace json;

Value::Value() : type(Type::NULL_TYPE), value(std::monostate{}) {}

Value::Value(const std::string& str) : type(Type::STRING), value(str) {}

Value::Value(double num) : type(Type::NUMBER), value(num) {}

Value::Value(bool b) : type(Type::BOOLEAN), value(b) {}

Value::Value(const std::map<std::string, Value>& obj) : type(Type::OBJECT), value(obj) {}

Value::Value(const std::vector<Value>& arr) : type(Type::ARRAY), value(arr) {}

Value::Type Value::getType() const {
    return type;
}

std::string Value::asString() const {
    if (type != Type::STRING) {
        throw TypeError("Value is not a string");
    }
    return std::get<std::string>(value);
}

double Value::asNumber() const {
    if (type != Type::NUMBER) {
        throw TypeError("Value is not a number");
    }
    return std::get<double>(value);
}

bool Value::asBoolean() const {
    if (type != Type::BOOLEAN) {
        throw TypeError("Value is not a boolean");
    }
    return std::get<bool>(value);
}

std::map<std::string, Value> Value::asObject() const {
    if (type != Type::OBJECT) {
        throw TypeError("Value is not an object");
    }
    return std::get<std::map<std::string, Value>>(value);
}

std::vector<Value> Value::asArray() const {
    if (type != Type::ARRAY) {
        throw TypeError("Value is not an array");
    }
    return std::get<std::vector<Value>>(value);
}

bool Value::isNull() const {
    return type == Type::NULL_TYPE;
}