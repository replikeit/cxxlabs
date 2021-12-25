#include <gtest/gtest.h>
#include <json.h>

#include <string>

using namespace std;

TEST(JsonLibtesting, SimpleJSON) {
    auto json = JObject{ {"32", 2}, { "2" , 1}};

    ASSERT_EQ( json.getVal<int>("32").value(), 2);
}

TEST(JsonLibtesting, JsonObjInJsonObj) {
    auto json = JObject{ {"32", JObject{"11", 1}}, { "2" , 1}};

    ASSERT_EQ(json.getVal<JObject>("32").value().getVal<int>("11").value(), 1);
}

TEST(JsonLibtesting, JsonArray) {
    auto arr = JArray{1, "2", 2.0, true};

    ASSERT_EQ(std::get<int>(arr[3]), true);
}


