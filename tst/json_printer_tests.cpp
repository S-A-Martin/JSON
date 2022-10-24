#include "gtest.h"
#include "json.h"

TEST(JSONDataValueUnsignedInt, StreamOverloadShouldPrintCorrectString) {
    std::stringstream ss;
    JSON::Data data(5U);
    ss << data;
    EXPECT_EQ(ss.str(), "5");
}

TEST(JSONDataValueDouble, StreamOverloadShouldPrintCorrectString) {
    std::stringstream ss;
    JSON::Data data(5.6);
    ss << data;
    EXPECT_EQ(ss.str(), "5.6");
}

TEST(JSONDataValueDouble, StreamOverloadWithFloatConstructShouldPrintCorrectString) {
    std::stringstream ss;
    JSON::Data data(5.6f);
    ss << data;
    EXPECT_EQ(ss.str(), "5.6");
}

TEST(JSONDataValueBool, StreamOverloadShouldPrintCorrectString) {
    std::stringstream ss;
    JSON::Data data1(true);
    JSON::Data data2(false);
    ss << data1 << " " << data2;
    EXPECT_EQ(ss.str(), "true false");
}

TEST(JSONDataValueStdString, StreamOverloadShouldPrintCorrectString) {
    std::stringstream ss;
    JSON::Data data("Test String");
    ss << data;
    EXPECT_EQ(ss.str(), "\"Test String\"");
}

TEST(JSONDataValueJSONObject, StreamOverloadShouldPrintCorrectString) {
    std::stringstream ss;
    JSON::Data data = JSON::Object{ { "Test String", 1 }, { "Test String 2", 5.5 }, { "Test String 3", true } };
    ss << data;
    std::string expected =
        // clang format off
        R"({
    "Test String": 1,
    "Test String 2": 5.5,
    "Test String 3": true
})";
    EXPECT_EQ(ss.str(), expected);
}

TEST(JSONDataValueJSONArray, StreamOverloadShouldPrintCorrectString) {
    std::stringstream ss;
    JSON::Data data = JSON::Array{ "Test String", 1, 6.5, false, 7U };
    ss << data;
    // clang-format off
    std::string expected = 
R"([
    "Test String",
    1,
    6.5,
    false,
    7
])";
    // clang-format on
    EXPECT_EQ(ss.str(), expected);
}

TEST(JSONPrinter, PrettyPrintingDataWithJSONNullProducesCorrectString) {
    JSON::Data data(JSON::Null{});
    std::string dataStr = JSON::prettyPrint(data);
    EXPECT_EQ(dataStr, "null");
}

TEST(JSONPrinter, PrettyPrintingDataWithIntProducesCorrectString) {
    JSON::Data data(5);
    JSON::Data data2(-5);
    std::string dataStr = JSON::prettyPrint(data);
    std::string dataStr2 = JSON::prettyPrint(data2);
    EXPECT_EQ(dataStr, "5");
    EXPECT_EQ(dataStr2, "-5");
}

TEST(JSONPrinter, PrettyPrintingDataWithUnsignedIntProducesCorrectString) {
    JSON::Data data(5U);
    std::string dataStr = JSON::prettyPrint(data);
    EXPECT_EQ(dataStr, "5");
}

TEST(JSONPrinter, PrettyPrintingDataWithDoubleProducesCorrectString) {
    JSON::Data data(5.5557);
    std::string dataStr = JSON::prettyPrint(data);
    EXPECT_EQ(dataStr, "5.5557");
}

TEST(JSONPrinter, PrettyPrintingDataWithBoolProducesCorrectString) {
    JSON::Data data(true);
    JSON::Data data2(false);
    std::string dataStr = JSON::prettyPrint(data);
    std::string dataStr2 = JSON::prettyPrint(data2);
    EXPECT_EQ(dataStr, "true");
    EXPECT_EQ(dataStr2, "false");
}

TEST(JSONPrinter, PrettyPrintingDataWithStdStringProducesCorrectString) {
    JSON::Data data("Test String");
    std::string dataStr = JSON::prettyPrint(data);
    EXPECT_EQ(dataStr, "\"Test String\"");
}

TEST(JSONPrinter, PrettyPrintingDataWithSimpleJSONObjectProducesCorrectString) {
    JSON::Data data = JSON::Object{
        { "Simple Test", true }
    };

    std::string dataStr = JSON::prettyPrint(data);

    // clang-format off
    std::string expected =
R"({
    "Simple Test": true
})";
    // clang-format on

    EXPECT_EQ(dataStr, expected);
}

TEST(JSONPrinter, PrettyPrintingDataWithComplexJSONObjectProducesCorrectString) {
    JSON::Data data = JSON::Object{
        { "Simple Test", nullptr },
        { "Simple Test1", -5000 },
        { "Simple Test2", 5000U },
        { "Simple Test3", 6.67 },
        { "Simple Test4", true },
        { "Simple Test5", "Test String" }
    };

    std::string dataStr = JSON::prettyPrint(data);

    std::string expected =
        // clang-format off
R"({
    "Simple Test": null,
    "Simple Test1": -5000,
    "Simple Test2": 5000,
    "Simple Test3": 6.67,
    "Simple Test4": true,
    "Simple Test5": "Test String"
})";
    // clang-format on

    EXPECT_EQ(dataStr, expected);
}

TEST(JSONPrinter, PrettyPrintingDataWithNestedJSONObjectProducesCorrectString) {
    // clang-format off
    JSON::Data data = JSON::Object{
        { "Simple Test", nullptr },
        { "Simple Test1", -5000 },
        { "Simple Test2", 5000U },
        { "Simple Test3", 6.67 },
        { "Simple Test4", true },
        { "Simple Test5", "Test String" },
        { "Nested Object", JSON::Object{
                                { "Nested 1", false },
                                { "Nested 2", 4.4 },
                                { "Nested 3", "Other String" },
                                { "Nested 4", -5 },
                                { "Array Test", JSON::Array{ 5.4, "Array String", true, nullptr } }
                            }
        }
    };

    std::string dataStr = JSON::prettyPrint(data);

    std::string expected =
// Map will order alphabetically by keys which means a reshuffle inside each object
R"({
    "Nested Object": {
        "Array Test": [
            5.4,
            "Array String",
            true,
            null
        ],
        "Nested 1": false,
        "Nested 2": 4.4,
        "Nested 3": "Other String",
        "Nested 4": -5
    },
    "Simple Test": null,
    "Simple Test1": -5000,
    "Simple Test2": 5000,
    "Simple Test3": 6.67,
    "Simple Test4": true,
    "Simple Test5": "Test String"
})";

    EXPECT_EQ(dataStr, expected);
    // clang-format on
}

TEST(JSONPrinter, FlatPrintingDataWithComplexJSONObjectProducesCorrectString) {
    JSON::Data data = JSON::Object{
        { "Simple Test", nullptr },
        { "Simple Test1", -5000 },
        { "Simple Test2", 5000U },
        { "Simple Test3", 6.67 },
        { "Simple Test4", true },
        { "Simple Test5", "Test String" }
    };

    std::string dataStr = JSON::print(data);
    std::string expected = R"({ "Simple Test": null, "Simple Test1": -5000, "Simple Test2": 5000, "Simple Test3": 6.67, "Simple Test4": true, "Simple Test5": "Test String" })";
    EXPECT_EQ(dataStr, expected);
}
