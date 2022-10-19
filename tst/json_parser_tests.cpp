#include "gtest.h"
#include "json.h"

TEST(JSONParser, ReadFileCreatesCorrectString) {
    // clang-format off
    std::string result = JSON::readFile("../tst/test_JSON.json");
    std::string expected =
R"({
    "Nested Object": {
        "Array Test": [
            5.4,
            "Array String",
            true,
            null,
            [
                8.5,
                "Test123",
                false
            ],
            {
                "Object Inside Array": "Yes"
            }
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

    EXPECT_EQ(result, expected);
    // clang-format on
}

TEST(JSONParser, parseCreatesCorrectObject) {
    std::string jsonString = JSON::readFile("../tst/test_JSON.json");
    JSON::Data data = JSON::parse(jsonString);

    EXPECT_EQ(data["Simple Test"], nullptr);
    EXPECT_EQ(data["Simple Test1"], -5000);
    EXPECT_EQ(data["Simple Test2"], 5000);
    EXPECT_EQ(data["Simple Test3"], 6.67);
    EXPECT_EQ(data["Simple Test4"], true);
    EXPECT_EQ(data["Simple Test5"], "Test String");
    EXPECT_EQ(data["Nested Object"]["Nested 1"], false);
    EXPECT_EQ(data["Nested Object"]["Nested 2"], 4.4);
    EXPECT_EQ(data["Nested Object"]["Nested 3"], "Other String");
    EXPECT_EQ(data["Nested Object"]["Nested 4"], -5);
    EXPECT_EQ(data["Nested Object"]["Array Test"][0], 5.4);
    EXPECT_EQ(data["Nested Object"]["Array Test"][1], "Array String");
    EXPECT_EQ(data["Nested Object"]["Array Test"][2], true);
    EXPECT_EQ(data["Nested Object"]["Array Test"][3], nullptr);
    EXPECT_EQ(data["Nested Object"]["Array Test"][4][0], 8.5);
    EXPECT_EQ(data["Nested Object"]["Array Test"][4][1], "Test123");
    EXPECT_EQ(data["Nested Object"]["Array Test"][4][2], false);
    EXPECT_EQ(data["Nested Object"]["Array Test"][5]["Object Inside Array"], "Yes");
}

TEST(JSONParser, SaveCreatesCorrectObject) {
    std::string preSaveString = JSON::readFile("../tst/test_JSON.json");
    JSON::Data dataPreSave = JSON::parse(preSaveString);

    dataPreSave["Nested Object"]["Array Test"][5]["Object Inside Array"] = "Edited Value";
    JSON::saveFile(dataPreSave, "../tst/save_test.json");

    std::string postSaveString = JSON::readFile("../tst/save_test.json");
    JSON::Data dataPostSave = JSON::parse(postSaveString);
    std::remove("../tst/save_test.json");

    EXPECT_EQ(dataPreSave, dataPostSave);
}