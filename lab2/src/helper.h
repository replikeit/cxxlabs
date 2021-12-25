//
// Created by replikeit on 12/25/21.
//

#ifndef TMP_HELPER_H
#define TMP_HELPER_H
class JObject;
using Value = std::variant<void*, bool, int, double, std::string, JObject>;
using KeyValue = std::map<std::string, Value>;
using JArray = std::vector<Value>;


#endif //TMP_HELPER_H
