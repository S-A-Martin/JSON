#include "gtest.h"
#include "json.h"

TEST(JSONParser, parseCreatesCorrectObject) {
    JSON::Data data = JSON::parseFile("../tst/test_JSON.json");

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
    JSON::Data dataPreSave = JSON::parseFile("../tst/test_JSON.json");

    dataPreSave["Nested Object"]["Array Test"][5]["Object Inside Array"] = "Edited Value";
    JSON::saveFile(dataPreSave, "../tst/save_test.json");

    JSON::Data dataPostSave = JSON::parseFile("../tst/save_test.json");
    std::remove("../tst/save_test.json");

    EXPECT_EQ(dataPreSave, dataPostSave);
}