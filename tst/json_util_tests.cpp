#include "gtest.h"
#include "json.h"

TEST(JSON_Util, TypeToStringWithJSONNullReturnsCorrectString) {
    JSON::Data data = nullptr;
    EXPECT_EQ(JSON::typeToString(data), "<JSON::Null>");
}

TEST(JSON_Util, TypeToStringWithIntReturnsCorrectString) {
    JSON::Data data = 600;
    EXPECT_EQ(JSON::typeToString(data), "<int>");
}

TEST(JSON_Util, TypeToStringWithUnsignedIntReturnsCorrectString) {
    JSON::Data data = 600U;
    EXPECT_EQ(JSON::typeToString(data), "<unsigned int>");
}

TEST(JSON_Util, TypeToStringWithBoolReturnsCorrectString) {
    JSON::Data data = false;
    EXPECT_EQ(JSON::typeToString(data), "<bool>");
}

TEST(JSON_Util, TypeToStringWithStdStringReturnsCorrectString) {
    JSON::Data data = "Testing";
    EXPECT_EQ(JSON::typeToString(data), "<std::string>");
}

TEST(JSON_Util, TypeToStringWithDoubleReturnsCorrectString) {
    JSON::Data data = 9.87;
    EXPECT_EQ(JSON::typeToString(data), "<double>");
}

TEST(JSON_Util, TypeToStringWithJSONObjectReturnsCorrectString) {
    JSON::Data data = JSON::Object{};
    EXPECT_EQ(JSON::typeToString(data), "<JSON::Object>");
}

TEST(JSON_Util, TypeToStringWithJSONArrayReturnsCorrectString) {
    JSON::Data data = JSON::Array{};
    EXPECT_EQ(JSON::typeToString(data), "<JSON::Array>");
}