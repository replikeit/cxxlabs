//
// Created by replikeit on 1/11/22.
//

#ifndef LAB3_REST_SERVICE_H
#define LAB3_REST_SERVICE_H

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <stdio.h>
namespace fs = std::filesystem;

#include "served/served.hpp"
#include "nlohmann/json.hpp"

class rest_service
{
public:
    rest_service();
    void run(const std::string& ip, const std::string& port, int threads_count);
private:
    served::multiplexer mux;
    int id_counter=0;
};


#endif //LAB3_REST_SERVICE_H
