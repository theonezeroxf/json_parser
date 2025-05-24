#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include "value.hpp"
#include <string>
#include <string_view>

namespace json {

class Parser {
public:
    // 从字符串解析 JSON
    static Value parse(const std::string& json);
    
private:
    Parser(std::string_view input);
    
    // 解析方法
    Value parseValue();
    Value parseObject();
    Value parseArray();
    Value parseString();
    Value parseNumber();
    Value parseBoolean();
    Value parseNull();
    
    // 辅助方法
    void skipWhitespace();
    bool match(char expected);
    char peek() const;
    char advance();
    bool isAtEnd() const;
    void expect(char expected);
    
    // 成员变量
    std::string_view input_;
    size_t current_ = 0;
};

} // namespace json

#endif // JSON_PARSER_HPP