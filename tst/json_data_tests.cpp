#include "gtest.h"
#include "json.h"

// JSON::Data with value as JSON::Null

TEST(JSONDataValueNull, CanConstructDataWithJSONNull) {
    JSON::Null null;
    JSON::Data data(null);
    EXPECT_TRUE(data.isType<JSON::Null>());
    EXPECT_TRUE(data.index() == JSON::Type::JSON_NULL);
    EXPECT_EQ(std::get<JSON::Null>(data.value), null);
}

TEST(JSONDataValueNull, CanAssignDataToJSONNull) {
    JSON::Null null;
    JSON::Data data;
    data = null;
    EXPECT_TRUE(data.isType<JSON::Null>());
    EXPECT_TRUE(data.index() == JSON::Type::JSON_NULL);
    EXPECT_EQ(std::get<JSON::Null>(data.value), null);
}

TEST(JSONDataValueNull, CanConstructDataWithNullptr) {
    JSON::Null null;
    JSON::Data data(nullptr);
    EXPECT_TRUE(data.isType<JSON::Null>());
    EXPECT_TRUE(data.index() == JSON::Type::JSON_NULL);
    EXPECT_EQ(std::get<JSON::Null>(data.value), null);
}

TEST(JSONDataValueNull, CanAssignDataToNullptr) {
    JSON::Data data;
    data = nullptr;
    EXPECT_TRUE(data.isType<JSON::Null>());
    EXPECT_TRUE(data.index() == JSON::Type::JSON_NULL);
    EXPECT_EQ(std::get<JSON::Null>(data.value), JSON::Null{});
}

TEST(JSONDataValueNull, IndexShouldMatchTypeJSONNull) {
    JSON::Data data;
    data.value = JSON::Null{};
    EXPECT_EQ(data.index(), JSON::Type::JSON_NULL);
}

TEST(JSONDataValueNull, IndexShouldntMatchTypeJSONNullWhenNotNull) {
    JSON::Data data(5);
    EXPECT_NE(data.index(), JSON::Type::JSON_NULL);
}

TEST(JSONDataValueNull, IsNullShouldReturnTrueWhenValueIsJSONNull) {
    JSON::Data data;
    data.value = JSON::Null{};
    EXPECT_TRUE(data.isType<JSON::Null>());
}

TEST(JSONDataValueNull, IsNullShouldReturnFalseWhenValueIsntJSONNull) {
    JSON::Data data(5);
    EXPECT_FALSE(data.isType<JSON::Null>());
}

TEST(JSONDataValueNull, CanRetreiveJSONNullFromDataUsingConversionOperator) {
    JSON::Data data(JSON::Null{});
    JSON::Null null = data;
    EXPECT_EQ(std::get<JSON::Null>(data.value), null);
}

TEST(JSONDataValueNull, EqualityWithJSONNullShouldBeTrue) {
    JSON::Data data(JSON::Null{});
    JSON::Null null = data;
    EXPECT_TRUE(data == null);
}

TEST(JSONDataValueNull, EqualityWithNonJSONNullShouldBeFalse) {
    JSON::Data data(JSON::Null{});
    int other1 = 5;
    bool other2 = true;
    double other3 = 9.9;
    EXPECT_TRUE(data != other1);
    EXPECT_TRUE(data != other2);
    EXPECT_TRUE(data != other3);
}

// JSON::Data with value as int

TEST(JSONDataValueInt, CanConstructDataWithInt) {
    int num = 5;
    JSON::Data data(num);
    EXPECT_TRUE(data.isType<int>());
    EXPECT_TRUE(data.index() == JSON::Type::INT);
    EXPECT_EQ(std::get<int>(data.value), num);
}

TEST(JSONDataValueInt, CanAssignDataToInt) {
    int num = 5;
    JSON::Data data;
    data = num;
    EXPECT_TRUE(data.isType<int>());
    EXPECT_TRUE(data.index() == JSON::Type::INT);
    EXPECT_EQ(std::get<int>(data.value), num);
}

TEST(JSONDataValueInt, IndexShouldMatchTypeInt) {
    JSON::Data data;
    data.value = 5;
    EXPECT_EQ(data.index(), JSON::Type::INT);
}

TEST(JSONDataValueInt, IndexShouldntMatchTypeIntWhenNotInt) {
    JSON::Data data(JSON::Null{});
    EXPECT_NE(data.index(), JSON::Type::INT);
}

TEST(JSONDataValueInt, isIntShouldReturnTrueWhenValueIsInt) {
    JSON::Data data;
    data.value = 5;
    EXPECT_TRUE(data.isType<int>());
}

TEST(JSONDataValueInt, isIntShouldReturnFalseWhenValueIsntInt) {
    JSON::Data data(JSON::Null{});
    EXPECT_FALSE(data.isType<int>());
}

TEST(JSONDataValueInt, CanRetreiveIntFromDataUsingConversionOperator) {
    JSON::Data data(5);
    int num = data;
    EXPECT_EQ(std::get<int>(data.value), num);
}

TEST(JSONDataValueInt, EqualityWithIntShouldBeTrue) {
    JSON::Data data(5);
    int num = data;
    EXPECT_TRUE(data == num);
}

TEST(JSONDataValueInt, EqualityWithNonIntShouldBeFalse) {
    JSON::Data data(5);
    JSON::Null other1;
    bool other2 = true;
    double other3 = 9.9;
    EXPECT_TRUE(data != other1);
    EXPECT_TRUE(data != other2);
    EXPECT_TRUE(data != other3);
}

// JSON::Data with value as unsigned unsigned int

TEST(JSONDataValueUnsignedInt, CanConstructDataWithUnsignedInt) {
    unsigned int num = 5;
    JSON::Data data(num);
    EXPECT_TRUE(data.isType<unsigned int>());
    EXPECT_TRUE(data.index() == JSON::Type::UINT);
    EXPECT_EQ(std::get<unsigned int>(data.value), num);
}

TEST(JSONDataValueUnsignedInt, CanAssignDataToUnsignedInt) {
    unsigned int num = 5;
    JSON::Data data;
    data = num;
    EXPECT_TRUE(data.isType<unsigned int>());
    EXPECT_TRUE(data.index() == JSON::Type::UINT);
    EXPECT_EQ(std::get<unsigned int>(data.value), num);
}

TEST(JSONDataValueUnsignedInt, IndexShouldMatchTypeUnsignedInt) {
    JSON::Data data;
    data.value = 5U;
    EXPECT_EQ(data.index(), JSON::Type::UINT);
}

TEST(JSONDataValueUnsignedInt, IndexShouldntMatchTypeUnsignedIntWhenNotUnsignedInt) {
    JSON::Data data(JSON::Null{});
    EXPECT_NE(data.index(), JSON::Type::UINT);
}

TEST(JSONDataValueUnsignedInt, isUnsignedIntShouldReturnTrueWhenValueIsUnsignedInt) {
    JSON::Data data;
    data.value = 5U;
    EXPECT_TRUE(data.isType<unsigned int>());
}

TEST(JSONDataValueUnsignedInt, isUnsignedIntShouldReturnFalseWhenValueIsntUnsignedInt) {
    JSON::Data data(JSON::Null{});
    EXPECT_FALSE(data.isType<unsigned int>());
}

TEST(JSONDataValueUnsignedInt, CanRetreiveUnsignedIntFromDataUsingConversionOperator) {
    JSON::Data data(5U);
    unsigned int num = data;
    EXPECT_EQ(std::get<unsigned int>(data.value), num);
}

TEST(JSONDataValueUnsignedInt, EqualityWithUnsignedIntShouldBeTrue) {
    JSON::Data data(5U);
    unsigned int num = data;
    EXPECT_TRUE(data == num);
}

TEST(JSONDataValueUnsignedInt, EqualityWithNonuUnsignedIntShouldBeFalse) {
    JSON::Data data(5U);
    JSON::Null other1;
    bool other2 = true;
    double other3 = 9.9;
    EXPECT_TRUE(data != other1);
    EXPECT_TRUE(data != other2);
    EXPECT_TRUE(data != other3);
}

// JSON::Data with value as double

TEST(JSONDataValueDouble, CanConstructDataWithDouble) {
    double num = 5.0;
    JSON::Data data(num);
    EXPECT_TRUE(data.isType<double>());
    EXPECT_TRUE(data.index() == JSON::Type::DOUBLE);
    EXPECT_EQ(std::get<double>(data.value), num);
}

TEST(JSONDataValueDouble, CanConstructDataWithFloatAsDouble) {
    float num = 5.0f;
    JSON::Data data(num);
    EXPECT_TRUE(data.isType<double>());
    EXPECT_TRUE(data.index() == JSON::Type::DOUBLE);
    EXPECT_EQ(std::get<double>(data.value), num);
}

TEST(JSONDataValueDouble, CanAssignDataToDouble) {
    double num = 5.0;
    JSON::Data data;
    data = num;
    EXPECT_TRUE(data.isType<double>());
    EXPECT_TRUE(data.index() == JSON::Type::DOUBLE);
    EXPECT_EQ(std::get<double>(data.value), num);
}

TEST(JSONDataValueDouble, CanAssignDataToFloatAsDouble) {
    float num = 5.0f;
    JSON::Data data;
    data = num;
    EXPECT_TRUE(data.isType<double>());
    EXPECT_TRUE(data.index() == JSON::Type::DOUBLE);
    EXPECT_EQ(std::get<double>(data.value), num);
}

TEST(JSONDataValueDouble, IndexShouldMatchTypeDouble) {
    JSON::Data data;
    data.value = 5.0;
    EXPECT_EQ(data.index(), JSON::Type::DOUBLE);
}

TEST(JSONDataValueDouble, IndexWithFloatShouldMatchTypeDouble) {
    JSON::Data data;
    data.value = 5.0f;
    EXPECT_EQ(data.index(), JSON::Type::DOUBLE);
}

TEST(JSONDataValueDouble, IndexShouldntMatchTypeDoubleWhenNotDouble) {
    JSON::Data data(JSON::Null{});
    EXPECT_NE(data.index(), JSON::Type::DOUBLE);
}

TEST(JSONDataValueDouble, isDoubleShouldReturnTrueWhenValueIsDouble) {
    JSON::Data data;
    data.value = 5.0;
    EXPECT_TRUE(data.isType<double>());
}

TEST(JSONDataValueDouble, isDoubleShouldReturnTrueWhenValueIsFloatAsDouble) {
    JSON::Data data;
    data.value = 5.0f;
    EXPECT_TRUE(data.isType<double>());
}

TEST(JSONDataValueDouble, isDoubleShouldReturnFalseWhenValueIsntDouble) {
    JSON::Data data(JSON::Null{});
    EXPECT_FALSE(data.isType<double>());
}

TEST(JSONDataValueDouble, CanRetreiveDoubleFromDataUsingConversionOperator) {
    JSON::Data data(5.0);
    double num = data;
    EXPECT_EQ(std::get<double>(data.value), num);
}

TEST(JSONDataValueDouble, CanRetreiveFloatAsDoubleFromDataUsingConversionOperator) {
    JSON::Data data(5.0f);
    float num = data;
    EXPECT_EQ(std::get<double>(data.value), num);
}

TEST(JSONDataValueDouble, EqualityWithDoubleShouldBeTrue) {
    JSON::Data data(5.0);
    double num = data;
    EXPECT_TRUE(data == num);
}

TEST(JSONDataValueDouble, EqualityWithNonDoubleShouldBeFalse) {
    JSON::Data data(5.0);
    JSON::Null other1;
    bool other2 = true;
    double other3 = 9.9;
    EXPECT_TRUE(data != other1);
    EXPECT_TRUE(data != other2);
    EXPECT_TRUE(data != other3);
}

// JSON::Data with value as bool

TEST(JSONDataValueBool, CanConstructDataWithBool) {
    bool b = false;
    JSON::Data data(b);
    EXPECT_TRUE(data.isType<bool>());
    EXPECT_TRUE(data.index() == JSON::Type::BOOL);
    EXPECT_EQ(std::get<bool>(data.value), b);
}

TEST(JSONDataValueBool, CanAssignDataToBool) {
    bool b = true;
    JSON::Data data;
    data = b;
    EXPECT_TRUE(data.isType<bool>());
    EXPECT_TRUE(data.index() == JSON::Type::BOOL);
    EXPECT_EQ(std::get<bool>(data.value), b);
}

TEST(JSONDataValueBool, IndexShouldMatchTypeBool) {
    JSON::Data data;
    data.value = true;
    EXPECT_EQ(data.index(), JSON::Type::BOOL);
}

TEST(JSONDataValueBool, IndexShouldntMatchTypeBoolWhenNotBool) {
    JSON::Data data(JSON::Null{});
    EXPECT_NE(data.index(), JSON::Type::BOOL);
}

TEST(JSONDataValueBool, isBoolShouldReturnTrueWhenValueIsBool) {
    JSON::Data data;
    data.value = false;
    EXPECT_TRUE(data.isType<bool>());
}

TEST(JSONDataValueBool, isBoolShouldReturnFalseWhenValueIsntBool) {
    JSON::Data data(JSON::Null{});
    EXPECT_FALSE(data.isType<bool>());
}

TEST(JSONDataValueBool, CanRetreiveBoolFromDataUsingConversionOperator) {
    JSON::Data data(true);
    bool b = data;
    EXPECT_EQ(std::get<bool>(data.value), b);
}

TEST(JSONDataValueBool, EqualityWithBoolShouldBeTrue) {
    JSON::Data data(false);
    bool b = data;
    EXPECT_TRUE(data == b);
}

TEST(JSONDataValueBool, EqualityWithNonBoolShouldBeFalse) {
    JSON::Data data(true);
    JSON::Null other1;
    int other2 = 5;
    double other3 = 9.9;
    EXPECT_TRUE(data != other1);
    EXPECT_TRUE(data != other2);
    EXPECT_TRUE(data != other3);
}

// JSON::Data with value as std::string

TEST(JSONDataValueStdString, CanConstructDataWithStdString) {
    std::string s = "Test String";
    JSON::Data data(s);
    EXPECT_TRUE(data.isType<std::string>());
    EXPECT_TRUE(data.index() == JSON::Type::STD_STRING);
    EXPECT_EQ(std::get<std::string>(data.value), s);
}

TEST(JSONDataValueStdString, CanAssignDataToStdString) {
    std::string s = "Test String";
    JSON::Data data;
    data = s;
    EXPECT_TRUE(data.isType<std::string>());
    EXPECT_TRUE(data.index() == JSON::Type::STD_STRING);
    EXPECT_EQ(std::get<std::string>(data.value), s);
}

TEST(JSONDataValueStdString, IndexShouldMatchTypeStdString) {
    JSON::Data data;
    data.value = "Test String";
    EXPECT_EQ(data.index(), JSON::Type::STD_STRING);
}

TEST(JSONDataValueStdString, IndexShouldntMatchTypeStdStringWhenNotStdString) {
    JSON::Data data(JSON::Null{});
    EXPECT_NE(data.index(), JSON::Type::STD_STRING);
}

TEST(JSONDataValueStdString, isStringShouldReturnTrueWhenValueIsStdString) {
    JSON::Data data;
    data.value = "Test String";
    ;
    EXPECT_TRUE(data.isType<std::string>());
}

TEST(JSONDataValueStdString, isStringShouldReturnFalseWhenValueIsntStdString) {
    JSON::Data data(JSON::Null{});
    EXPECT_FALSE(data.isType<std::string>());
}

TEST(JSONDataValueStdString, CanRetreiveStdStringFromDataUsingConversionOperator) {
    JSON::Data data("Test String");
    std::string s = data;
    EXPECT_EQ(std::get<std::string>(data.value), s);
}

TEST(JSONDataValueStdString, EqualityWithStdStringShouldBeTrue) {
    JSON::Data data("Test String");
    std::string s = data;
    EXPECT_TRUE(data == s);
}

TEST(JSONDataValueStdString, EqualityWithNonStdStringShouldBeFalse) {
    JSON::Data data("Test String");
    JSON::Null other1;
    int other2 = 5;
    double other3 = 9.9;
    EXPECT_TRUE(data != other1);
    EXPECT_TRUE(data != other2);
    EXPECT_TRUE(data != other3);
}

// JSON::Data with value as JSON::Object

TEST(JSONDataValueJSONObject, CanConstructDataWithJSONObject) {
    JSON::Object o = { { "Test String", 1 }, { "Test String 2", 5.5 }, { "Test String 3", true } };
    JSON::Data data(o);
    EXPECT_TRUE(data.isType<JSON::Object>());
    EXPECT_TRUE(data.index() == JSON::Type::JSON_OBJECT);
    EXPECT_EQ(std::get<JSON::Object>(data.value), o);
}

TEST(JSONDataValueJSONObject, CanAssignDataToJSONObject) {
    JSON::Object o = { { "Test String", 1 }, { "Test String 2", 5.5 }, { "Test String 3", true } };
    JSON::Data data;
    data = o;
    EXPECT_TRUE(data.isType<JSON::Object>());
    EXPECT_TRUE(data.index() == JSON::Type::JSON_OBJECT);
    EXPECT_EQ(std::get<JSON::Object>(data.value), o);
}

TEST(JSONDataValueJSONObject, IndexShouldMatchTypeJSONObject) {
    JSON::Data data;
    data.value = JSON::Object{ { "Test String", 1 }, { "Test String 2", 5.5 }, { "Test String 3", true } };
    EXPECT_EQ(data.index(), JSON::Type::JSON_OBJECT);
}

TEST(JSONDataValueJSONObject, IndexShouldntMatchTypeJSONObjectWhenNotJSONObject) {
    JSON::Data data(JSON::Null{});
    EXPECT_NE(data.index(), JSON::Type::JSON_OBJECT);
}

TEST(JSONDataValueJSONObject, isObjectShouldReturnTrueWhenValueIsJSONObject) {
    JSON::Data data;
    data.value = JSON::Object{ { "Test String", 1 }, { "Test String 2", 5.5 }, { "Test String 3", true } };
    EXPECT_TRUE(data.isType<JSON::Object>());
}

TEST(JSONDataValueJSONObject, isObjectShouldReturnFalseWhenValueIsntJSONObject) {
    JSON::Data data(JSON::Null{});
    EXPECT_FALSE(data.isType<JSON::Object>());
}

TEST(JSONDataValueJSONObject, CanRetreiveJSONObjectFromDataUsingConversionOperator) {
    JSON::Data data = JSON::Object{ { "Test String", 1 }, { "Test String 2", 5.5 }, { "Test String 3", true } };
    JSON::Object o = data;
    EXPECT_EQ(std::get<JSON::Object>(data.value), o);
}

TEST(JSONDataValueJSONObject, EqualityWithJSONObjectShouldBeTrue) {
    JSON::Data data = JSON::Object{ { "Test String", 1 }, { "Test String 2", 5.5 }, { "Test String 3", true } };
    JSON::Object o = data;
    EXPECT_TRUE(data == o);
}

TEST(JSONDataValueJSONObject, EqualityWithNonJSONObjectShouldBeFalse) {
    JSON::Data data = JSON::Object{ { "Test String", 1 }, { "Test String 2", 5.5 }, { "Test String 3", true } };
    JSON::Null other1;
    int other2 = 5;
    double other3 = 9.9;
    EXPECT_TRUE(data != other1);
    EXPECT_TRUE(data != other2);
    EXPECT_TRUE(data != other3);
}

// JSON::Data with value as JSON::Array

TEST(JSONDataValueJSONArray, CanConstructDataWithJSONArray) {
    JSON::Array a = { "Test String", 1, 6.5, false, 7U };
    JSON::Data data(a);
    EXPECT_TRUE(data.isType<JSON::Array>());
    EXPECT_TRUE(data.index() == JSON::Type::JSON_ARRAY);
    EXPECT_EQ(std::get<JSON::Array>(data.value), a);
}

TEST(JSONDataValueJSONArray, CanAssignDataToJSONArray) {
    JSON::Array a = { "Test String", 1, 6.5, false, 7U };
    JSON::Data data;
    data = a;
    EXPECT_TRUE(data.isType<JSON::Array>());
    EXPECT_TRUE(data.index() == JSON::Type::JSON_ARRAY);
    EXPECT_EQ(std::get<JSON::Array>(data.value), a);
}

TEST(JSONDataValueJSONArray, IndexShouldMatchTypeJSONArray) {
    JSON::Data data;
    data.value = JSON::Array{ "Test String", 1, 6.5, false, 7U };
    EXPECT_EQ(data.index(), JSON::Type::JSON_ARRAY);
}

TEST(JSONDataValueJSONArray, IndexShouldntMatchTypeJSONArrayWhenNotJSONArray) {
    JSON::Data data(JSON::Null{});
    EXPECT_NE(data.index(), JSON::Type::JSON_ARRAY);
}

TEST(JSONDataValueJSONArray, isArrayShouldReturnTrueWhenValueIsJSONArray) {
    JSON::Data data;
    data.value = JSON::Array{ "Test String", 1, 6.5, false, 7U };
    EXPECT_TRUE(data.isType<JSON::Array>());
}

TEST(JSONDataValueJSONArray, isArrayShouldReturnFalseWhenValueIsntJSONArray) {
    JSON::Data data(JSON::Null{});
    EXPECT_FALSE(data.isType<JSON::Array>());
}

TEST(JSONDataValueJSONArray, CanRetreiveJSONArrayFromDataUsingConversionOperator) {
    JSON::Data data = JSON::Array{ "Test String", 1, 6.5, false, 7U };
    JSON::Array a = data;
    EXPECT_EQ(std::get<JSON::Array>(data.value), a);
}

TEST(JSONDataValueJSONArray, EqualityWithJSONArrayShouldBeTrue) {
    JSON::Data data = JSON::Array{ "Test String", 1, 6.5, false, 7U };
    JSON::Array a = data;
    EXPECT_TRUE(data == a);
}

TEST(JSONDataValueJSONArray, EqualityWithNonJSONArrayShouldBeFalse) {
    JSON::Data data = JSON::Array{ "Test String", 1, 6.5, false, 7U };
    JSON::Null other1;
    int other2 = 5;
    double other3 = 9.9;
    EXPECT_TRUE(data != other1);
    EXPECT_TRUE(data != other2);
    EXPECT_TRUE(data != other3);
}

TEST(JSONData, CanAccessDataValueObjectViaSubscriptOperator) {
    JSON::Data data = JSON::Object{ { "Test1", 5.5 },
                                    { "Test2", 500 } };

    EXPECT_EQ(data["Test1"], 5.5);
    EXPECT_EQ(data["Test2"], 500);
}
TEST(JSONData, CanAccessDataValueArrayViaSubscriptOperator) {
    JSON::Data data = JSON::Array{ { true, "Test1", 5.5 } };
    bool result = data[0];
    EXPECT_EQ(result, true);
    EXPECT_EQ(data[1], "Test1");
    EXPECT_EQ(data[2], 5.5);
}