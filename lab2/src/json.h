//
// Created by replikeit on 12/25/21.
//

#ifndef TMP_JSON_H
#define TMP_JSON_H

#include <vector>
#include <map>
#include <unordered_map>
#include <variant>
#include <string>
#include <utility>
#include <iostream>
#include <initializer_list>
#include <optional>

#include "helper.h"

#pragma warning(disable:4996)

class JObject {
public:
    using Object = std::variant<KeyValue, JArray>;

    JObject();
    JObject(JArray array);
    JObject(std::initializer_list<Value>);
    JObject(std::initializer_list<std::pair<const std::string, Value>>);
    JObject(const JObject& json);

    void add(const std::string& key, Value value);
    void add(const Value& value);
    void edit(const std::string& forKey, const Value& newValue);
    void edit(int atIndex, const Value& newValue);
    void remove(const std::string& forKey);
    void remove(int atIndex);

    template<typename T>
    std::optional<T> getVal(const std::string& key);
    std::optional<JArray> asArray();

    bool isEmpty();
    bool isArray();

    class JSONIterator : public std::iterator<std::input_iterator_tag, Value> {
    public:

        typedef std::variant<JArray::iterator, KeyValue::iterator> iterator;
        typedef std::variant<JArray::const_iterator, KeyValue::const_iterator> const_iterator;

        JSONIterator(iterator it) {
            this->it = it;
        }

        bool operator!=(JSONIterator const& other) const {
            return !(it == other.it);
        }

        bool operator==(JSONIterator const& other) const {
            if (it.index() != other.it.index()) return false;
            if (std::holds_alternative<KeyValue::iterator>(it)) {
                auto f = std::get<KeyValue::iterator>(it);
                auto s = std::get<KeyValue::iterator>(other.it);
                return f == s;
            }
            else if (std::holds_alternative<JArray::iterator>(it)) {
                auto f = std::get<JArray::iterator>(it);
                auto s = std::get<JArray::iterator>(other.it);
                return f == s;
            }
        }

        typename JSONIterator::reference operator*() const {
            if (std::holds_alternative<KeyValue::iterator>(it)) {
                return std::get<KeyValue::iterator>(it)->second;
            }
            else {
                return *std::get<JArray::iterator>(it);
            }
        }

        JSONIterator& operator++() {
            if (std::holds_alternative<KeyValue::iterator>(it)) {
                it = ++std::get<KeyValue::iterator>(it);
            }
            else {
                it = ++std::get<JArray::iterator>(it);
            }
            return *this;
        }

    private:
        iterator it;
    };

    JSONIterator begin();

    JSONIterator end();

private:
    Object root;

};

template<typename T>
std::optional<T> JObject::getVal(const std::string& key) {
    if (std::holds_alternative<KeyValue>(root)) {
        KeyValue v_map = std::get<KeyValue>(root);
        try {
            return std::optional<T>{std::get<T>(v_map[key])};
        }
        catch (std::bad_variant_access ex) {
            return std::nullopt;
        }
    }
    else {
        return std::nullopt;
    }
}

#endif //TMP_JSON_H
