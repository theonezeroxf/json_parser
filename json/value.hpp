#ifndef JSON_VALUE_HPP
#define JSON_VALUE_HPP

#include <string>
#include <variant>
#include <vector>
#include <map>
namespace json {
class Value {
public:
    enum class Type {
        STRING,
        NUMBER,
        OBJECT,
        ARRAY,
        BOOLEAN,
        NULL_TYPE
    };

    Value();
    Value(const std::string& str);
    Value(double num);
    Value(bool boolean);
    Value(const std::map<std::string, Value>& obj);
    Value(const std::vector<Value>& arr);

    Type getType() const;

    std::string asString() const;
    double asNumber() const;
    bool asBoolean() const;
    std::map<std::string, Value> asObject() const;
    std::vector<Value> asArray() const;
    bool isNull() const;
private:
    Type type;
    std::variant<std::monostate, std::string, double, bool, std::map<std::string, Value>, std::vector<Value>> value;
};

}

#endif // JSON_VALUE_HPP