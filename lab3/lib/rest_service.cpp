//
// Created by replikeit on 1/11/22.
//

#include "rest_service.h"

using namespace nlohmann;
using namespace std;
using namespace served;

void get_all_documents(response& res, const request& req){
    json array_obj = json::array();

    string path = "files/";
    for (const auto & entry : fs::directory_iterator(path)){
        string tmp = entry.path();
        array_obj.push_back(tmp.substr(tmp.find_last_of("/\\") + 1));
    }

    res << to_string(json{{"files", array_obj}});
}

void get_documents_filtered(response& res, const request& req, map<string, string>& params){
    string path = "files/";
    json array_obj = json::array();
    for (const auto & entry : fs::directory_iterator(path)){
        string tmp = entry.path();

        ifstream file(tmp);
        std::string content((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());

        auto obj = json::parse(content);
        for (auto i = obj.begin(); i != obj.end(); ++i){
            if (i.key() == params["key"]){
                if((params.contains("value") && params["value"] == i.value()) || !params.contains("value"))
                    array_obj.push_back(tmp.substr(tmp.find_last_of("/\\") + 1));
            }
        }
    }

    if (array_obj.empty()){
        res.set_status(404);
        res << "Files not found";
        return;
    }

    res << to_string(json{{"files", array_obj}});
}

void get_documents(response& res, const request& req){
    map<string, string> params;
    for ( const auto & query_param : req.query )
        params.emplace(query_param.first, query_param.second);

    if (!params.contains("key"))
        get_all_documents(res, req);
    else
        get_documents_filtered(res, req, params);
}

void write_to_file(string path, string text){
    ofstream file(path);
    file << text;
    file.close();
}

void create_new_document(response& res, const request& req){
    int id = rand();
    write_to_file("files/" + to_string(id) + ".json", req.body());
    res << to_string(json{"id", {id}});
}

void edit_document(response& res, const request& req){
    string id = req.params["id"];
    string path = "files/" + id + ".json";

    if (!fs::exists(path)){
        res.set_status(404);
        res << "File not found";
        return;
    }

    write_to_file(path, req.body());
    res << to_string(json{"id", {id}});
}

void remove_document(response& res, const request& req){
    string id = req.params["id"];
    string path = "files/" + id + ".json";

    if (!fs::exists(path)){
        res.set_status(404);
        res << "File not found";
        return;
    }

    remove(path.c_str());
    res << to_string(json{"id", {id}});
}

void get_document_content(response& res, const request& req){
    string id = req.params["id"];
    string path = "files/" + id + ".json";

    if (!fs::exists(path)){
        res.set_status(404);
        res << "File not found";
        return;
    }

    ifstream file(path);
    std::string content((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());
    res << content;
    file.close();
}

rest_service::rest_service()
{
    srand(time(NULL));

    mux.handle("/serviceurl/{id}")
            .put(&edit_document)
            .del(&remove_document)
            .get(&get_document_content);

    mux.handle("/serviceurl")
            .get(&get_documents)
            .post(&create_new_document);
}

void rest_service::run(const std::string& ip, const std::string& port, int threads_count)
{
    net::server server(ip, port, mux);
    server.run(threads_count);
}

