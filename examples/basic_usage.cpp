#include <iostream>
#include "json/parser.hpp"
#include "json/value.hpp"

int main() {
    // 创建一个解析器实例
    Parser parser;

    // 示例 JSON 字符串
    std::string jsonString = R"({"name": "John", "age": 30, "isStudent": false})";

    try {
        // 解析 JSON 字符串
        Value jsonValue = parser.parse(jsonString);

        // 获取并输出值
        std::cout << "Name: " << jsonValue["name"].asString() << std::endl;
        std::cout << "Age: " << jsonValue["age"].asInt() << std::endl;
        std::cout << "Is Student: " << jsonValue["isStudent"].asBool() << std::endl;
    } catch (const ParseException& e) {
        std::cerr << "解析错误: " << e.what() << std::endl;
    } catch (const InvalidValueException& e) {
        std::cerr << "无效值错误: " << e.what() << std::endl;
    }

    return 0;
}