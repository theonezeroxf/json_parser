#include "../json/parser.hpp"
#include <stdexcept>
#include <cctype>

namespace json {

Value Parser::parse(const std::string& json) {
    Parser parser(json);
    return parser.parseValue();
}

Parser::Parser(std::string_view input) : input_(input) {}

Value Parser::parseValue() {
    skipWhitespace();
    
    if (isAtEnd()) {
        throw std::runtime_error("Unexpected end of input");
    }
    
    switch (peek()) {
        case '{': return parseObject();
        case '[': return parseArray();
        case '"': return parseString();
        case 't':
        case 'f': return parseBoolean();
        case 'n': return parseNull();
        default:
            if (std::isdigit(peek()) || peek() == '-') {
                return parseNumber();
            }
            throw std::runtime_error("Unexpected character");
    }
}

Value Parser::parseObject() {
    expect('{');
    std::map<std::string, Value> object;
    
    skipWhitespace();
    if (peek() == '}') {
        advance();
        return Value(object);
    }
    
    while (true) {
        // 解析键
        skipWhitespace();
        Value key = parseString();
        
        // 解析冒号
        skipWhitespace();
        expect(':');
        
        // 解析值
        skipWhitespace();
        Value val = parseValue();
        
        object[key.asString()] = val;
        
        skipWhitespace();
        if (peek() == '}') {
            advance();
            break;
        }
        
        expect(',');
    }
    
    return Value(object);
}

Value Parser::parseArray() {
    expect('[');
    std::vector<Value> array;
    
    skipWhitespace();
    if (peek() == ']') {
        advance();
        return Value(array);
    }
    
    while (true) {
        array.push_back(parseValue());
        
        skipWhitespace();
        if (peek() == ']') {
            advance();
            break;
        }
        
        expect(',');
    }
    
    return Value(array);
}

Value Parser::parseString() {
    expect('"');
    std::string str;
    
    while (!isAtEnd() && peek() != '"') {
        char c = advance();
        if (c == '\\') {
            if (isAtEnd()) {
                throw std::runtime_error("Unterminated string");
            }
            switch (advance()) {
                case '"': str += '"'; break;
                case '\\': str += '\\'; break;
                case '/': str += '/'; break;
                case 'b': str += '\b'; break;
                case 'f': str += '\f'; break;
                case 'n': str += '\n'; break;
                case 'r': str += '\r'; break;
                case 't': str += '\t'; break;
                default: throw std::runtime_error("Invalid escape sequence");
            }
        } else {
            str += c;
        }
    }
    
    expect('"');
    return Value(str);
}

Value Parser::parseNumber() {
    size_t start = current_;
    if (peek() == '-') advance();
    
    while (!isAtEnd() && std::isdigit(peek())) {
        advance();
    }
    
    if (!isAtEnd() && peek() == '.') {
        advance();
        if (!std::isdigit(peek())) {
            throw std::runtime_error("Invalid number format");
        }
        while (!isAtEnd() && std::isdigit(peek())) {
            advance();
        }
    }
    
    std::string num_str(input_.data() + start, current_ - start);
    return Value(std::stod(num_str));
}

Value Parser::parseBoolean() {
    if (peek() == 't') {
        expect('t');
        expect('r');
        expect('u');
        expect('e');
        return Value(true);
    } else {
        expect('f');
        expect('a');
        expect('l');
        expect('s');
        expect('e');
        return Value(false);
    }
}

Value Parser::parseNull() {
    expect('n');
    expect('u');
    expect('l');
    expect('l');
    return Value();
}

void Parser::skipWhitespace() {
    while (!isAtEnd() && std::isspace(peek())) {
        advance();
    }
}

bool Parser::match(char expected) {
    if (isAtEnd() || peek() != expected) {
        return false;
    }
    advance();
    return true;
}

char Parser::peek() const {
    if (isAtEnd()) return '\0';
    return input_[current_];
}

char Parser::advance() {
    if (isAtEnd()) {
        throw std::runtime_error("Unexpected end of input");
    }
    return input_[current_++];
}

bool Parser::isAtEnd() const {
    return current_ >= input_.length();
}

void Parser::expect(char expected) {
    if (!match(expected)) {
        throw std::runtime_error(std::string("Expected '") + expected + "'");
    }
}

} // namespace json