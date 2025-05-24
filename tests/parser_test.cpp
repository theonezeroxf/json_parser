#include <iostream>
#include "../json/parser.hpp"
#include "../json/value.hpp"
#include "../json/exceptions.hpp"

int main() {
    try {
        // 嵌套对象的 JSON 字符串
        std::string json_str = R"({
            "name": "张三",
            "address": {
                "city": "北京",
                "detail": {
                    "street": "朝阳区",
                    "number": "123号"
                }
            },
            "contacts": {
                "phone": "12345678",
                "email": "zhangsan@example.com"
            }
        })";
        
        json::Value value = json::Parser::parse(json_str);
        
        // 访问嵌套对象
        auto address = value.asObject()["address"].asObject();
        auto detail = address["detail"].asObject();
        
        std::cout << "街道: " << detail["street"].asString() << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "解析错误: " << e.what() << std::endl;
    }
}