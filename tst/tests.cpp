#include "gtest.h"
#include "json.h"

// // Only applicable for testing. For sanity, double check these
// // match the std::variant value types in JSON::Data:
enum Type {
    JSONNULL = 0,
    INT,
    DOUBLE,
    FLOAT,
    BOOL,
    JSONARRAY,
    JSONOBJECT,
    STRING
};

TEST(JSON_Data, DefaultConstructorValueShouldBeNull) {
    JSON::Data data;
    JSON::Null null;
    EXPECT_EQ(data.value.index(), Type::JSONNULL);
    EXPECT_EQ(std::get<JSON::Null>(data.value), null);
}

TEST(JSON_Data, ConstructorWithNullptrShouldSetValueToJSONNull) {
    JSON::Data data(nullptr);
    JSON::Null null;
    EXPECT_EQ(std::get<JSON::Null>(data.value), null);
}

TEST(JSON_Data, ConstructorWithIntShouldSetValueToInt) {
    int x = 5;
    JSON::Data data(x);
    EXPECT_EQ(data.value.index(), Type::INT);
    EXPECT_EQ(std::get<int>(data.value), x);
}

TEST(JSON_Data, ConstructorWithDoubleShouldSetValueToDouble) {
    double x = 5.5;
    JSON::Data data(x);
    EXPECT_EQ(data.value.index(), Type::DOUBLE);
    EXPECT_EQ(std::get<double>(data.value), x);
}

TEST(JSON_Data, ConstructorWithFloatShouldSetValueToFloat) {
    float x = 5.5f;
    JSON::Data data(x);
    EXPECT_EQ(data.value.index(), Type::FLOAT);
    EXPECT_EQ(std::get<float>(data.value), x);
}

TEST(JSON_Data, ConstructorWithBoolShouldSetValueToBool) {
    bool x = true;
    JSON::Data data(x);
    EXPECT_EQ(data.value.index(), Type::BOOL);
    EXPECT_EQ(std::get<bool>(data.value), x);
}

TEST(JSON_Data, ConstructorWithJSONArrayShouldSetValueToJSONArray) {
    JSON::Array array = { { 1 }, { 1 }, { 1 } };
    JSON::Data data(array);
    EXPECT_EQ(data.value.index(), Type::JSONARRAY);
    EXPECT_EQ(std::get<JSON::Array>(data.value), array);
}

TEST(JSON_Data, ConstructorWithJSONObjectShouldSetValueToJSONObject) {
    JSON::Object object = {
        { "key1", nullptr },
        { "key2", nullptr }
    };
    JSON::Data data(object);
    EXPECT_EQ(data.value.index(), Type::JSONOBJECT);
    EXPECT_EQ(std::get<JSON::Object>(data.value), object);
}

TEST(JSON_Data, ConstructorWithConstCharPtrShouldSetValueToString) {
    std::string x = "This is a test";
    JSON::Data data("This is a test");
    EXPECT_EQ(data.value.index(), 7);
    EXPECT_EQ(std::get<std::string>(data.value), x);
}

TEST(JSON_Data, ConstructorWithStringShouldSetValueToString) {
    std::string x = "This is a test";
    JSON::Data data(x);
    EXPECT_EQ(data.value.index(), Type::STRING);
    EXPECT_EQ(std::get<std::string>(data.value), x);
}

TEST(JSON_Data, CanEqualJSONNullAndSetsValue) {
    JSON::Data data(5);
    JSON::Null x;
    data = x;
    EXPECT_EQ(data.value.index(), Type::JSONNULL);
    EXPECT_EQ(std::get<JSON::Null>(data.value), x);
}

TEST(JSON_Data, CanEqualIntAndSetsValue) {
    JSON::Data data;
    int x = 50;
    data = x;
    EXPECT_EQ(data.value.index(), Type::INT);
    EXPECT_EQ(std::get<int>(data.value), x);
}

TEST(JSON_Data, CanEqualDoubleAndSetsValue) {
    JSON::Data data;
    double x = 50.5;
    data = x;
    EXPECT_EQ(data.value.index(), Type::DOUBLE);
    EXPECT_EQ(std::get<double>(data.value), x);
}

TEST(JSON_Data, CanEqualFloatAndSetsValue) {
    JSON::Data data;
    float x = 50.5f;
    data = x;
    EXPECT_EQ(data.value.index(), Type::FLOAT);
    EXPECT_EQ(std::get<float>(data.value), x);
}

TEST(JSON_Data, CanEqualBoolAndSetsValue) {
    JSON::Data data;
    bool x = false;
    data = x;
    EXPECT_EQ(data.value.index(), Type::BOOL);
    EXPECT_EQ(std::get<bool>(data.value), x);
}

TEST(JSON_Data, CanEqualJSONArrayAndSetsValue) {
    JSON::Data data;
    JSON::Array x = { { 1 }, { 2.5 }, { false } };
    data = x;
    EXPECT_EQ(data.value.index(), Type::JSONARRAY);
    EXPECT_EQ(std::get<JSON::Array>(data.value), x);
}

TEST(JSON_Data, CanEqualJSONObjectAndSetsValue) {
    JSON::Data data;
    JSON::Object x = {
        { "key1", nullptr },
        { "key2", nullptr }
    };
    data = x;
    EXPECT_EQ(data.value.index(), Type::JSONOBJECT);
    EXPECT_EQ(std::get<JSON::Object>(data.value), x);
}

TEST(JSON_Data, CanEqualStringAndSetsValue) {
    JSON::Data data;
    std::string x("Test");
    data = x;
    EXPECT_EQ(data.value.index(), Type::STRING);
    EXPECT_EQ(std::get<std::string>(data.value), x);
}

TEST(JSON_Data, ConversionOperatorAllowsConversionToInt) {
    JSON::Data x = 1;
    int y = x;
    EXPECT_EQ(std::get<int>(x.value), y);
}

TEST(JSON_Data, ConversionOperatorAllowsConversionToDouble) {
    JSON::Data x = 4.5;
    double y = x;
    EXPECT_EQ(std::get<double>(x.value), y);
}

TEST(JSON_Data, ConversionOperatorAllowsConversionToFloat) {
    JSON::Data x = 5.5f;
    float y = x;
    EXPECT_EQ(std::get<float>(x.value), y);
}

TEST(JSON_Data, ConversionOperatorAllowsConversionToBool) {
    JSON::Data x = false;
    bool y = x;
    EXPECT_EQ(std::get<bool>(x.value), y);
}

TEST(JSON_Data, ConversionOperatorAllowsConversionToJSONArray) {
    JSON::Data x = JSON::Array{ 1, 2.2, 3.3f, true, "test" };
    JSON::Array y = x;
    EXPECT_EQ(std::get<JSON::Array>(x.value), y);
}

TEST(JSON_Data, ConversionOperatorAllowsConversionToJSONObject) {
    JSON::Data x = JSON::Object{ { "test", 1 } };
    JSON::Object y = x;
    EXPECT_EQ(std::get<JSON::Object>(x.value), y);
}

TEST(JSON_Data, ConversionOperatorAllowsConversionToString) {
    JSON::Data x = "Test String";
    std::string y = x;
    EXPECT_EQ(std::get<std::string>(x.value), y);
}

TEST(JSON_Array, CanContainDifferingPrimatives) {
    JSON::Array array = { { 1 }, { 5.5f }, { true }, { "Test String" } };
}

TEST(JSON_Array, CanAccessJSONArrayElements) {
    JSON::Array array = { { 1 }, { 5.5f }, { true }, { "Test String" } };
    int a = std::get<int>(array[0].value);
    float b = std::get<float>(array[1].value);
    bool c = std::get<bool>(array[2].value);
    std::string d = std::get<std::string>(array[3].value);
    // 'Bad Variant' exception thrown will fail the test

    EXPECT_EQ(std::get<int>(array[0].value), a);
    EXPECT_EQ(std::get<float>(array[1].value), b);
    EXPECT_EQ(std::get<bool>(array[2].value), c);
    EXPECT_EQ(std::get<std::string>(array[3].value), d);
}

TEST(JSON_Array, CanAccessArrayDirectlyViaConversionOperator) {
    JSON::Array array = { { 1 }, { 5.5f }, { true }, { "Test String" } };
    int a = array[0];
    float b = array[1];
    bool c = array[2];
    std::string d = array[3];
    // 'Bad Variant' exception thrown will fail the test

    EXPECT_EQ(std::get<int>(array[0].value), a);
    EXPECT_EQ(std::get<float>(array[1].value), b);
    EXPECT_EQ(std::get<bool>(array[2].value), c);
    EXPECT_EQ(std::get<std::string>(array[3].value), d);
}