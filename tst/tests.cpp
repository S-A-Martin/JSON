#include "gtest.h"
#include "json.h"

TEST(JSON_Data, DefaultConstructorValueShouldBeNull) {
    JSON::Data data;
    JSON::Null null;
    EXPECT_EQ(std::get<JSON::Null>(data.value), null);
}

TEST(JSON_Data, DefaultConstructorValueIndexShouldBeOne) {
    JSON::Data data;
    EXPECT_EQ(data.value.index(), 1);
}