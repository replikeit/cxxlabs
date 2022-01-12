#include <iostream>
#include "lib/rest_service.h"

int main()
{
    nlohmann::json j2 = {
            {"pi", 3.141},
            {"happy", true},
            {"name", "Niels"},
            {"nothing", nullptr},
            {"answer", {
                           {"everything", 42}
                   }},
            {"list", {1, 0, 2}},
            {"object", {
                           {"currency", "USD"},
                         {"value", 42.99}
                   }}
    };

    std::cout << to_string(j2);
    for (auto i = std::begin(j2); i != std::end(j2); ++i){
        std::cout << i.key() << " " << i.value();
    }
    rest_service ser;
    ser.run("127.0.0.1", "8888", 10);
    return 0;
}
