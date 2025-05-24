#ifndef JSON_EXCEPTIONS_HPP
#define JSON_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>

namespace json {

// JSON解析的基础异常类
class JsonException : public std::runtime_error {
public:
    explicit JsonException(const std::string& message) 
        : std::runtime_error(message) {}
};

// 语法错误异常
class SyntaxError : public JsonException {
public:
    explicit SyntaxError(const std::string& message) 
        : JsonException("Syntax error: " + message) {}
};

// 类型错误异常
class TypeError : public JsonException {
public:
    explicit TypeError(const std::string& message)
        : JsonException("Type error: " + message) {}
};

// 越界访问异常
class OutOfRangeError : public JsonException {
public:
    explicit OutOfRangeError(const std::string& message)
        : JsonException("Out of range error: " + message) {}
};

// 键不存在异常
class KeyError : public JsonException {
public:
    explicit KeyError(const std::string& key)
        : JsonException("Key not found: " + key) {}
};

// 解析错误异常
class ParseError : public JsonException {
public:
    ParseError(const std::string& message, size_t line, size_t column)
        : JsonException("Parse error at line " + std::to_string(line) + 
                       ", column " + std::to_string(column) + ": " + message),
          line_(line),
          column_(column) {}

    size_t getLine() const { return line_; }
    size_t getColumn() const { return column_; }

private:
    size_t line_;
    size_t column_;
};

} // namespace json

#endif // JSON_EXCEPTIONS_HPP