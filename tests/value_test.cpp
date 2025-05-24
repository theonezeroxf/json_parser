#include <gtest/gtest.h>
#include "../json/value.hpp"
#include "../json/exceptions.hpp"
#include <string>
#include <vector>
#include <map>

namespace json {
namespace test {

class ValueTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 设置基本类型测试数据
        strValue = Value("test string");
        numValue = Value(42.5);
        boolValue = Value(true);
        nullValue = Value();
        
        // 创建嵌套数组
        std::vector<Value> innerArr = {Value(1.0), Value(2.0)};
        std::vector<Value> arr = {Value(1.0), Value("two"), Value(true), Value(innerArr)};
        arrayValue = Value(arr);
        
        // 创建嵌套对象
        std::map<std::string, Value> innerObj;
        innerObj["key"] = Value("value");
        
        std::map<std::string, Value> obj;
        obj["name"] = Value("test");
        obj["age"] = Value(25.0);
        obj["active"] = Value(true);
        obj["data"] = Value(innerObj);
        objectValue = Value(obj);
    }

    Value strValue;
    Value numValue;
    Value boolValue;
    Value nullValue;
    Value arrayValue;
    Value objectValue;
};

// 字符串类型测试
TEST_F(ValueTest, StringType) {
    EXPECT_EQ(strValue.getType(), Value::Type::STRING);
    EXPECT_EQ(strValue.asString(), "test string");
    EXPECT_THROW(strValue.asNumber(), TypeError);
    EXPECT_THROW(strValue.asBoolean(), TypeError);
    EXPECT_THROW(strValue.asArray(), TypeError);
    EXPECT_THROW(strValue.asObject(), TypeError);
    EXPECT_FALSE(strValue.isNull());
}

// 数值类型测试
TEST_F(ValueTest, NumberType) {
    EXPECT_EQ(numValue.getType(), Value::Type::NUMBER);
    EXPECT_EQ(numValue.asNumber(), 42.5);
    EXPECT_THROW(numValue.asString(), TypeError);
    EXPECT_THROW(numValue.asBoolean(), TypeError);
    EXPECT_THROW(numValue.asArray(), TypeError);
    EXPECT_THROW(numValue.asObject(), TypeError);
    EXPECT_FALSE(numValue.isNull());
}

// 布尔类型测试
TEST_F(ValueTest, BooleanType) {
    EXPECT_EQ(boolValue.getType(), Value::Type::BOOLEAN);
    EXPECT_EQ(boolValue.asBoolean(), true);
    EXPECT_THROW(boolValue.asString(), TypeError);
    EXPECT_THROW(boolValue.asNumber(), TypeError);
    EXPECT_THROW(boolValue.asArray(), TypeError);
    EXPECT_THROW(boolValue.asObject(), TypeError);
    EXPECT_FALSE(boolValue.isNull());
}

// 空值类型测试
TEST_F(ValueTest, NullType) {
    EXPECT_EQ(nullValue.getType(), Value::Type::NULL_TYPE);
    EXPECT_TRUE(nullValue.isNull());
    EXPECT_THROW(nullValue.asString(), TypeError);
    EXPECT_THROW(nullValue.asNumber(), TypeError);
    EXPECT_THROW(nullValue.asBoolean(), TypeError);
    EXPECT_THROW(nullValue.asArray(), TypeError);
    EXPECT_THROW(nullValue.asObject(), TypeError);
}

// 数组类型测试，包括嵌套数组
TEST_F(ValueTest, ArrayType) {
    EXPECT_EQ(arrayValue.getType(), Value::Type::ARRAY);
    auto arr = arrayValue.asArray();
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0].asNumber(), 1);
    EXPECT_EQ(arr[1].asString(), "two");
    EXPECT_EQ(arr[2].asBoolean(), true);
    
    // 测试嵌套数组
    auto innerArr = arr[3].asArray();
    EXPECT_EQ(innerArr.size(), 2);
    EXPECT_EQ(innerArr[0].asNumber(), 1);
    EXPECT_EQ(innerArr[1].asNumber(), 2);
    
    EXPECT_THROW(arrayValue.asString(), TypeError);
    EXPECT_THROW(arrayValue.asNumber(), TypeError);
    EXPECT_THROW(arrayValue.asBoolean(), TypeError);
    EXPECT_THROW(arrayValue.asObject(), TypeError);
    EXPECT_FALSE(arrayValue.isNull());
}

// 对象类型测试，包括嵌套对象
TEST_F(ValueTest, ObjectType) {
    EXPECT_EQ(objectValue.getType(), Value::Type::OBJECT);
    auto obj = objectValue.asObject();
    EXPECT_EQ(obj["name"].asString(), "test");
    EXPECT_EQ(obj["age"].asNumber(), 25);
    EXPECT_EQ(obj["active"].asBoolean(), true);
    
    // 测试嵌套对象
    auto innerObj = obj["data"].asObject();
    EXPECT_EQ(innerObj["key"].asString(), "value");
    
    EXPECT_THROW(objectValue.asString(), TypeError);
    EXPECT_THROW(objectValue.asNumber(), TypeError);
    EXPECT_THROW(objectValue.asBoolean(), TypeError);
    EXPECT_THROW(objectValue.asArray(), TypeError);
    EXPECT_FALSE(objectValue.isNull());
}

// 拷贝构造测试
TEST_F(ValueTest, CopyConstruction) {
    Value copy(strValue);
    EXPECT_EQ(copy.getType(), Value::Type::STRING);
    EXPECT_EQ(copy.asString(), strValue.asString());
    
    // 测试嵌套对象的深拷贝
    Value objCopy(objectValue);
    auto obj = objCopy.asObject();
    EXPECT_EQ(obj["name"].asString(), "test");
    auto innerObj = obj["data"].asObject();
    EXPECT_EQ(innerObj["key"].asString(), "value");
}

// 移动构造测试
TEST_F(ValueTest, MoveConstruction) {
    std::string testStr = "move test";
    Value original(testStr);
    Value moved(std::move(original));
    EXPECT_EQ(moved.asString(), testStr);
}

// 赋值操作符测试
TEST_F(ValueTest, AssignmentOperator) {
    Value value;
    value = strValue;
    EXPECT_EQ(value.getType(), Value::Type::STRING);
    EXPECT_EQ(value.asString(), strValue.asString());
    
    // 测试自赋值
    value = value;
    EXPECT_EQ(value.getType(), Value::Type::STRING);
    EXPECT_EQ(value.asString(), strValue.asString());
}

// 移动赋值操作符测试
TEST_F(ValueTest, MoveAssignmentOperator) {
    Value value;
    std::string testStr = "move assign test";
    value = Value(testStr);
    EXPECT_EQ(value.asString(), testStr);
}

} // namespace test
} // namespace json