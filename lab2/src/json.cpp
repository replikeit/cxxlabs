//
// Created by replikeit on 12/25/21.
//

#include "json.h"

JObject::JObject() {
    root = KeyValue();
};

JObject::JObject(JArray array) {
    root = array;
}

JObject::JObject(std::initializer_list<Value> initializer_list) {
    root = initializer_list;
}

JObject::JObject(std::initializer_list<std::pair<const std::string, Value>> initializer_map) {
    root = initializer_map;
}


JObject::JObject(const JObject& json) {
    visit([this](Object const& arg) {
        if (holds_alternative<KeyValue>(arg)) {
            auto v_map = get<KeyValue>(arg);
            this->root = v_map;
        }
        else if (holds_alternative<JArray>(arg)) {
            auto v_array = get<JArray>(arg);
            this->root = v_array;
        }
    }, json.root);
}

bool JObject::isEmpty() {
    return visit([](Object const& arg) -> bool {
        if (holds_alternative<KeyValue>(arg)) {
            auto v_map = get<KeyValue>(arg);
            return v_map.empty();
        }
        else if (holds_alternative<JArray>(arg)) {
            auto v_array = get<JArray>(arg);
            return v_array.empty();
        }
    }, root);
}

bool JObject::isArray() {
    return holds_alternative<JArray>(root);
}

void JObject::add(const std::string& key, Value value) {
    if (holds_alternative<KeyValue>(root)) {
        auto v_map = get<KeyValue>(root);
        v_map[key] = value;
        root = v_map;
    }
}

void JObject::add(const Value& value) {
    if (holds_alternative<JArray>(root)) {
        auto v_array = get<JArray>(root);
        v_array.push_back(value);
        root = v_array;
    }
}

void JObject::edit(const std::string& forKey, const Value& newValue) {
    if (holds_alternative<KeyValue>(root)) {
        auto v_map = get<KeyValue>(root);
        if (v_map.find(forKey) != v_map.end()) {
            v_map[forKey] = newValue;
            root = v_map;
        }
    }
}

void JObject::edit(int atIndex, const Value& newValue) {
    if (holds_alternative<JArray>(root)) {
        auto v_array = get<JArray>(root);
        v_array[atIndex] = newValue;
        root = v_array;
    }
}

void JObject::remove(const std::string& forKey) {
    if (holds_alternative<KeyValue>(root)) {
        auto v_map = get<KeyValue>(root);
        if (v_map.find(forKey) != v_map.end()) {
            auto it = v_map.find(forKey);
            v_map.erase(it);
            root = v_map;
        }
    }
}

void JObject::remove(int atIndex) {
    if (holds_alternative<JArray>(root)) {
        auto v_array = get<JArray>(root);
        v_array.erase(v_array.begin() + atIndex);
        root = v_array;
    }
}

std::optional<JArray> JObject::asArray() {
    if (std::holds_alternative<JArray>(root)) {
        return std::get<JArray>(root);
    }
    else {
        return std::nullopt;
    }
}

JObject::JSONIterator JObject::begin() {
    if (std::holds_alternative<JArray>(root)) {
        return JSONIterator(std::get<JArray>(root).begin());
    }
    else {
        return JSONIterator(std::get<KeyValue>(root).begin());
    }
}

JObject::JSONIterator JObject::end() {
    if (std::holds_alternative<JArray>(root)) {
        return JSONIterator(std::get<JArray>(root).end());
    }
    else {
        return JSONIterator(std::get<KeyValue>(root).end());
    }
}

