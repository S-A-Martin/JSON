// #include "gtest.h"
// #include "json_null.h"
// #include "json_types.h"
// #include "json_data.h"
// #include "json_util.h"

// ///// JSON Data Constructors

// TEST(JSON_Data, ConstructorWithNullptrShouldSetValueToJSONNull) {
//     JSON::Null null;
//     JSON::Data data(nullptr);
//     EXPECT_EQ(data.index(), JSON::Type::JSON_NULL);
//     EXPECT_EQ(std::get<JSON::Null>(data.value), null);
// }

// TEST(JSON_Data, ConstructorWithIntShouldSetValueToInt) {
//     int x = 5;
//     JSON::Data data(x);
//     EXPECT_EQ(data.index(), JSON::Type::INT);
//     EXPECT_EQ(std::get<int>(data.value), x);
// }

// TEST(JSON_Data, ConstructorWithUnsignedIntShouldSetValueToUnsignedInt) {
//     unsigned int x = 5;
//     JSON::Data data(x);
//     EXPECT_EQ(data.index(), JSON::Type::UINT);
//     EXPECT_EQ(std::get<unsigned int>(data.value), x);
// }

// TEST(JSON_Data, ConstructorWithDoubleShouldSetValueToDouble) {
//     double x = 5.5;
//     JSON::Data data(x);
//     EXPECT_EQ(data.index(), JSON::Type::DOUBLE);
//     EXPECT_EQ(std::get<double>(data.value), x);
// }

// TEST(JSON_Data, ConstructorWithFloatShouldSetValueToFloat) {
//     float x = 5.5f;
//     JSON::Data data(x);
//     EXPECT_EQ(data.index(), JSON::Type::DOUBLE);
//     EXPECT_EQ(std::get<double>(data.value), x);
// }

// TEST(JSON_Data, ConstructorWithBoolShouldSetValueToBool) {
//     bool x = true;
//     JSON::Data data(x);
//     EXPECT_EQ(data.index(), JSON::Type::BOOL);
//     EXPECT_EQ(std::get<bool>(data.value), x);
// }

// TEST(JSON_Data, ConstructorWithJSONArrayShouldSetValueToJSONArray) {
//     JSON::Array array = { { 1 }, { 1 }, { 1 } };
//     JSON::Data data(array);
//     EXPECT_EQ(data.index(), JSON::Type::JSON_ARRAY);
//     EXPECT_EQ(std::get<JSON::Array>(data.value), array);
// }

// TEST(JSON_Data, ConstructorWithJSONObjectShouldSetValueToJSONObject) {
//     JSON::Object object = {
//         { "key1", nullptr },
//         { "key2", nullptr }
//     };
//     JSON::Data data(object);
//     EXPECT_EQ(data.index(), JSON::Type::JSON_OBJECT);
//     EXPECT_EQ(std::get<JSON::Object>(data.value), object);
// }

// TEST(JSON_Data, ConstructorWithConstCharPtrShouldSetValueToString) {
//     std::string x = "This is a test";
//     JSON::Data data("This is a test");
//     EXPECT_EQ(data.index(), JSON::Type::STD_STRING);
//     EXPECT_EQ(std::get<std::string>(data.value), x);
// }

// TEST(JSON_Data, ConstructorWithStringShouldSetValueToString) {
//     std::string x = "This is a test";
//     JSON::Data data(x);
//     EXPECT_EQ(data.index(), JSON::Type::STD_STRING);
//     EXPECT_EQ(std::get<std::string>(data.value), x);
// }

// ///// JSON ARRAY

// TEST(JSON_Data, AssignmentWithJSONNullSetsValue) {
//     JSON::Data data(5);
//     JSON::Null x;
//     data = x;
//     EXPECT_EQ(data.index(), JSON::Type::JSON_NULL);
//     EXPECT_EQ(std::get<JSON::Null>(data.value), x);
// }

// TEST(JSON_Data, AssignmentWithIntSetsValue) {
//     JSON::Data data;
//     int x = 50;
//     data = x;
//     EXPECT_EQ(data.index(), JSON::Type::INT);
//     EXPECT_EQ(std::get<int>(data.value), x);
// }

// TEST(JSON_Data, AssignmentWithUnsignedIntSetsValue) {
//     JSON::Data data;
//     unsigned int x = 50;
//     data = x;
//     EXPECT_EQ(data.index(), JSON::Type::UINT);
//     EXPECT_EQ(std::get<unsigned int>(data.value), x);
// }

// TEST(JSON_Data, AssignmentWithDoubleSetsValue) {
//     JSON::Data data;
//     double x = 50.5;
//     data = x;
//     EXPECT_EQ(data.index(), JSON::Type::DOUBLE);
//     EXPECT_EQ(std::get<double>(data.value), x);
// }

// TEST(JSON_Data, AssignmentWithFloatSetsValue) {
//     JSON::Data data;
//     float x = 50.5f;
//     data = x;
//     EXPECT_EQ(data.index(), JSON::Type::DOUBLE);
//     EXPECT_EQ(std::get<double>(data.value), x);
// }

// TEST(JSON_Data, AssignmentWithBoolSetsValue) {
//     JSON::Data data;
//     bool x = false;
//     data = x;
//     EXPECT_EQ(data.index(), JSON::Type::BOOL);
//     EXPECT_EQ(std::get<bool>(data.value), x);
// }

// TEST(JSON_Data, AssignmentWithJSONArraySetsValue) {
//     JSON::Data data;
//     JSON::Array x = { { 1 }, { 2.5 }, { false } };
//     data = x;
//     EXPECT_EQ(data.index(), JSON::Type::JSON_ARRAY);
//     EXPECT_EQ(std::get<JSON::Array>(data.value), x);
// }

// TEST(JSON_Data, AssignmentWithJSONObjectSetsValue) {
//     JSON::Data data;
//     JSON::Object x = {
//         { "key1", nullptr },
//         { "key2", nullptr }
//     };
//     data = x;
//     EXPECT_EQ(data.index(), JSON::Type::JSON_OBJECT);
//     EXPECT_EQ(std::get<JSON::Object>(data.value), x);
// }

// TEST(JSON_Data, AssignmentWithStringSetsValue) {
//     JSON::Data data;
//     std::string x("Test");
//     data = x;
//     EXPECT_EQ(data.index(), JSON::Type::STD_STRING);
//     EXPECT_EQ(std::get<std::string>(data.value), x);
// }

// TEST(JSON_Data, ConversionOperatorAllowsConversionToNull) {
//     JSON::Data x = JSON::Null{};
//     JSON::Null y;
//     y = x;
//     EXPECT_EQ(std::get<JSON::Null>(x.value), y);
// }

// TEST(JSON_Data, ConversionOperatorAllowsConversionToInt) {
//     JSON::Data x = 1;
//     int y = x;
//     EXPECT_EQ(std::get<int>(x.value), y);
// }

// TEST(JSON_Data, ConversionOperatorAllowsConversionToUnsignedInt) {
//     JSON::Data x = 1U;
//     unsigned int y = x;
//     EXPECT_EQ(std::get<unsigned int>(x.value), y);
// }

// TEST(JSON_Data, ConversionOperatorAllowsConversionToDouble) {
//     JSON::Data x = 4.5;
//     double y = x;
//     EXPECT_EQ(std::get<double>(x.value), y);
// }

// TEST(JSON_Data, ConversionOperatorAllowsConversionToFloat) {
//     JSON::Data x = 5.5f;
//     float y = x;
//     EXPECT_EQ(std::get<double>(x.value), y);
// }

// TEST(JSON_Data, ConversionOperatorAllowsConversionToBool) {
//     JSON::Data x = false;
//     bool y = x;
//     EXPECT_EQ(std::get<bool>(x.value), y);
// }

// TEST(JSON_Data, ConversionOperatorAllowsConversionToJSONArray) {
//     JSON::Data x = JSON::Array{ 1, 2.2, 3.3f, true, "test" };
//     JSON::Array y = x;
//     EXPECT_EQ(std::get<JSON::Array>(x.value), y);
// }

// TEST(JSON_Data, ConversionOperatorAllowsConversionToJSONObject) {
//     JSON::Data x = JSON::Object{ { "test", 1 } };
//     JSON::Object y = x;
//     EXPECT_EQ(std::get<JSON::Object>(x.value), y);
// }

// TEST(JSON_Data, ConversionOperatorAllowsConversionToString) {
//     JSON::Data x = "Test String";
//     std::string y = x;
//     EXPECT_EQ(std::get<std::string>(x.value), y);
// }

// TEST(JSON_Data, SquareBracketsWithIntCanAccessJSONArray) {
//     JSON::Data data = JSON::Array{ 5, 5.5, false, "Test" };
//     EXPECT_EQ(data[2], std::get<JSON::Array>(data.value)[2]);
//     EXPECT_EQ(data[2], false);
// }

// TEST(JSON_Data, SquareBracketsWithConstCharPtrCanAccessJSONObject) {
//     JSON::Data data = JSON::Object{ { "value1", 1 }, { "value2", 2 } };
//     EXPECT_EQ(data["value1"], std::get<JSON::Object>(data.value)["value1"]);
//     EXPECT_EQ(data["value1"], 1);
// }

// TEST(JSON_Data, SquareBracketsWithStringCanAccessJSONObject) {
//     JSON::Data data = JSON::Object{ { "value1", 1 }, { "value2", 2 } };
//     std::string str("value1");
//     EXPECT_EQ(data[str], std::get<JSON::Object>(data.value)[str]);
//     EXPECT_EQ(data[str], 1);
// }

// TEST(JSON_Data, JSONNullInsertionOperatorReturnsCorrectString) {
//     JSON::Data data;
//     std::stringstream ss;
//     ss << data;
//     EXPECT_EQ(ss.str(), "JSON::Null");
// }

// TEST(JSON_Data, IntInsertionOperatorReturnsCorrectString) {
//     JSON::Data data = 420;
//     std::stringstream ss;
//     ss << data;
//     EXPECT_EQ(ss.str(), "420");
// }

// TEST(JSON_Data, DoubleInsertionOperatorReturnsCorrectString) {
//     JSON::Data data = 5.67;
//     std::stringstream ss;
//     ss << data;
//     EXPECT_EQ(ss.str(), "5.67");
// }

// TEST(JSON_Data, FloatInsertionOperatorReturnsCorrectString) {
//     JSON::Data data = 8.76f;
//     std::stringstream ss;
//     ss << data;
//     EXPECT_EQ(ss.str(), "8.76");
// }

// TEST(JSON_Data, BoolInsertionOperatorReturnsCorrectString) {
//     JSON::Data data = false;
//     std::stringstream ss;
//     ss << data;
//     EXPECT_EQ(ss.str(), "false");
// }

// TEST(JSON_Data, JSONArrayInsertionOperatorReturnsCorrectString) {
//     JSON::Data data = JSON::Array{ true, 5, 8.2f };
//     std::stringstream ss;
//     ss << data;
//     EXPECT_EQ(ss.str(), "\"Invalid Output (JSON::Array)\"");
// }

// TEST(JSON_Data, JSONObjectInsertionOperatorReturnsCorrectString) {
//     JSON::Data data = JSON::Object{ { "test1", 1 }, { "test2", 2 } };
//     std::stringstream ss;
//     ss << data;
//     EXPECT_EQ(ss.str(), "\"Invalid Output (JSON::Object)\"");
// }

// TEST(JSON_Data, StringInsertionOperatorReturnsCorrectString) {
//     JSON::Data data = "Test String";
//     std::stringstream ss;
//     ss << data;
//     EXPECT_EQ(ss.str(), "\"Test String\"");
// }

// TEST(JSON_Data, JSONNullTypeToStringReturnsCorrectString) {
//     JSON::Data data;
//     std::stringstream ss;
//     ss << JSON::typeToString(data);
//     EXPECT_EQ(ss.str(), "<JSON::Null>");
// }

// TEST(JSON_Data, DoubleTypeToStringReturnsCorrectString) {
//     JSON::Data data = 5.67;
//     std::stringstream ss;
//     ss << JSON::typeToString(data);
//     EXPECT_EQ(ss.str(), "<double>");
// }

// TEST(JSON_Data, BoolTypeToStringReturnsCorrectString) {
//     JSON::Data data = false;
//     std::stringstream ss;
//     ss << JSON::typeToString(data);
//     EXPECT_EQ(ss.str(), "<bool>");
// }

// TEST(JSON_Data, JSONArrayTypeToStringReturnsCorrectString) {
//     JSON::Data data = JSON::Array{ true, 5, 8.2f };
//     std::stringstream ss;
//     ss << JSON::typeToString(data);
//     EXPECT_EQ(ss.str(), "<JSON::Array>");
// }

// TEST(JSON_Data, JSONObjectTypeToStringReturnsCorrectString) {
//     JSON::Data data = JSON::Object{ { "test1", 1 }, { "test2", 2 } };
//     std::stringstream ss;
//     ss << JSON::typeToString(data);
//     EXPECT_EQ(ss.str(), "<JSON::Object>");
// }

// TEST(JSON_Data, StringTypeToStringReturnsCorrectString) {
//     JSON::Data data = "Test String";
//     std::stringstream ss;
//     ss << JSON::typeToString(data);
//     EXPECT_EQ(ss.str(), "<std::string>");
// }

// TEST(JSON_Data, EqualityOperator) {
//     JSON::Data d1a = "test";
//     JSON::Data d1b = "test";
//     JSON::Data d2a = 45;
//     JSON::Data d2b = 46;

//     EXPECT_TRUE(d1a == d1b);
//     EXPECT_FALSE(d2a == d2b);

//     EXPECT_FALSE(d1a != d1b);
//     EXPECT_TRUE(d2a != d2b);
// }

// ///// JSON ARRAY
// /* As JSON::Array is just a pre-define on the template type of std::vector
// we're not going to fully test the std::vector API. */

// TEST(JSON_Array, CanBeEmptyObject) {
//     JSON::Array array;
//     EXPECT_TRUE(true);
// }

// TEST(JSON_Array, EmptyValuesAreNull) {
//     JSON::Array array{ { /* null */ }, 5, "Test" };
//     EXPECT_EQ(array[0], JSON::Null{});
//     EXPECT_TRUE(array[0] == JSON::Null{});
// }

// TEST(JSON_Array, CanContainDifferingPrimativesViaJSONData) {
//     JSON::Array array = { 1, 5.5f, true, "Test String" };
//     EXPECT_TRUE(true);
// }

// TEST(JSON_Array, CanAccessJSONArrayElements) {
//     JSON::Array array = { { 1 }, { 5.5f }, { true }, { "Test String" } };
//     int a = std::get<int>(array[0].value);
//     double b = std::get<double>(array[1].value);
//     bool c = std::get<bool>(array[2].value);
//     std::string d = std::get<std::string>(array[3].value);

//     EXPECT_EQ(std::get<int>(array[0].value), a);
//     EXPECT_EQ(std::get<double>(array[1].value), b);
//     EXPECT_EQ(std::get<bool>(array[2].value), c);
//     EXPECT_EQ(std::get<std::string>(array[3].value), d);
// }

// TEST(JSON_Array, CanAccessArrayDirectlyViaImplicitConversionOperator) {
//     JSON::Array array = { { 1 }, { 5.5f }, { true }, { "Test String" } };
//     int a = array[0];
//     double b = array[1];
//     bool c = array[2];
//     std::string d = array[3];

//     EXPECT_EQ(std::get<int>(array[0].value), a);
//     EXPECT_EQ(std::get<double>(array[1].value), b);
//     EXPECT_EQ(std::get<bool>(array[2].value), c);
//     EXPECT_EQ(std::get<std::string>(array[3].value), d);
// }

// /////// JSON File (Object)

// TEST(JSON_Object, CanBeEmptyObject) {
//     JSON::Object json;
//     EXPECT_TRUE(true);
// }

// TEST(JSON_Object, KeyWithEmptyValueIsNull) {
//     JSON::Object json{ { "Value", { /* null */ } } };
//     EXPECT_EQ(json["Value"], JSON::Null{});
//     EXPECT_TRUE(json["Value"] == JSON::Null{});
// }

// TEST(JSON_Object, CanAddJSONDataViaKeys) {
//     JSON::Object json;
//     json["value1"] = 364;
//     EXPECT_EQ(json["value1"], 364);
// }

// TEST(JSON_Object, CanAccessDifferingJSONDataPrimitivesViaKeys) {
//     JSON::Object json;
//     json["value1"] = 364;
//     json["value2"] = true;
//     json["value3"] = "test string";
//     json["value4"] = 4.53f;
//     json["value5"] = 7.56;
//     json["value6"] = JSON::Array{ 4, 5.5f, "test", false };
//     json["value7"] = JSON::Object{ { "nested1", 1 }, { "nested2", 2 } };

//     EXPECT_EQ(json["value1"], 364);
//     EXPECT_EQ(json["value2"], true);
//     EXPECT_EQ(json["value3"], "test string");
//     EXPECT_EQ(json["value4"], 4.53f);
//     EXPECT_EQ(json["value5"], 7.56);
//     EXPECT_EQ(json["value6"][1], 5.5f);
//     EXPECT_EQ(json["value7"]["nested1"], 1);
// }

// // TEST(JSON_PRETTY_PRINT, PrintObjectParenthesis) {
// //     //     JSON::Data json =
// //     //         JSON::Object{
// //     //             { "product-info", JSON::Object{ { "artist", "Mateus Asato" }, { "title", "20 Killer Licks" }, { "difficulty", "Advanced" }, { "price", 29.99 }, { "release-year", "2022" } } },
// //     //             { "tracks", JSON::Array{ JSON::Object{ { "filename", "source/videos/biggerandbetter.mp4" }, { "video-extension", "mp4" }, { "context", "Bigger And Better" }, { "type", "Solo" }, { "iteration", nullptr }, { "pretty-name", nullptr } }, JSON::Object{ { "filename", "source/videos/biggerandbetter_lick1.mp4" }, { "video-extension", "mp4" }, { "context", "Bigger And Better" }, { "type", "Lick" }, { "iteration", 1 }, { "pretty-name", "Bigger And Better Lick 1" } }, JSON::Object{ { "filename", "source/videos/biggerandbetter_lick2.mp4" }, { "video-extension", "mp4" }, { "context", "Bigger And Better" }, { "type", "Lick" }, { "iteration", 2 }, { "pretty-name", "Bigger And Better Lick 2" } }, JSON::Object{ { "filename", "source/videos/deadonthetracks.mp4" }, { "video-extension", "mp4" }, { "context", "Dead On The Tracks" }, { "type", "Solo" }, { "iteration", nullptr }, { "pretty-name", nullptr } }, JSON::Object{ { "filename", "source/videos/flogthat.mp4" }, { "video-extension", "mp4" }, { "context", "Flog That" }, { "type", "Solo" }, { "iteration", nullptr }, { "pretty-name", nullptr } } } }
// //     //         };

// //     //     std::string expected = R"({
// //     //     "product-info": {
// //     //         "artist": "Mateus Asato",
// //     //         "difficulty": "Advanced",
// //     //         "price": 29.99,
// //     //         "release-year": "2022",
// //     //         "title": "20 Killer Licks"
// //     //     },
// //     //     "tracks": [
// //     //         {
// //     //             "context": "Bigger And Better",
// //     //             "filename": "source/videos/biggerandbetter.mp4",
// //     //             "iteration": null,
// //     //             "pretty-name": null,
// //     //             "type": "Solo",
// //     //             "video-extension": "mp4"
// //     //         },
// //     //         {
// //     //             "context": "Bigger And Better",
// //     //             "filename": "source/videos/biggerandbetter_lick1.mp4",
// //     //             "iteration": 1,
// //     //             "pretty-name": "Bigger And Better Lick 1",
// //     //             "type": "Lick",
// //     //             "video-extension": "mp4"
// //     //         },
// //     //         {
// //     //             "context": "Bigger And Better",
// //     //             "filename": "source/videos/biggerandbetter_lick2.mp4",
// //     //             "iteration": 2,
// //     //             "pretty-name": "Bigger And Better Lick 2",
// //     //             "type": "Lick",
// //     //             "video-extension": "mp4"
// //     //         },
// //     //         {
// //     //             "context": "Dead On The Tracks",
// //     //             "filename": "source/videos/deadonthetracks.mp4",
// //     //             "iteration": null,
// //     //             "pretty-name": null,
// //     //             "type": "Solo",
// //     //             "video-extension": "mp4"
// //     //         },
// //     //         {
// //     //             "context": "Flog That",
// //     //             "filename": "source/videos/flogthat.mp4",
// //     //             "iteration": null,
// //     //             "pretty-name": null,
// //     //             "type": "Solo",
// //     //             "video-extension": "mp4"
// //     //         }
// //     //     ]
// //     // })";
// //     //     EXPECT_EQ(JSON::prettyPrint(json), expected);
// //     EXPECT_EQ(true, false);
// // }

// // TEST(JSON_Parse, BasicKeyParse) {
// //     std::string fileStr = JSON::readFile("./example2.json");
// //     JSON::Data json = JSON::parse(fileStr);
// //     EXPECT_EQ(json["name"], "found");
// // }