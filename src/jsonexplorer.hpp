#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include <regex>
#include<common.hpp>
#include<nlohmann/json.hpp>
using nlohmann::json;
using std::shared_ptr;
using std::make_shared;

std::string preprocess_json(const std::string& raw_json) {
    // 正则表达式：匹配未加引号的属性名，并添加双引号
    std::regex re_unquoted(R"((\s*)(\w+)(\s*):)");
    std::string result = std::regex_replace(raw_json, re_unquoted, R"($1"$2"$3:)");

    // 正则表达式：匹配单引号，并替换为双引号
    std::regex re_single_quotes(R"('([^']*)')");
    result = std::regex_replace(result, re_single_quotes, R"("$1")");

    return result;
}

class JsonExplorer{
    AbstractIconFactory icon_factory;
    AbstractStyleFactory style_factory;

    int max_len=0;
    std::shared_ptr<Component> root=nullptr;

    std::shared_ptr<Component> parse_json(const json& j, const std::string& key, int level) {
        if (j.is_object()) {
            auto container = std::make_shared<Container>(key, level);
            for (auto it = j.begin(); it != j.end(); ++it) {
                container->add(parse_json(it.value(), it.key(), level+1));
            }
            return container;
        } else {
            std::string val=j.dump();
            val = (val=="null")?"":val;
            int currnet_len=level*3+key.size()+val.size()+3;
            max_len = max_len < currnet_len ? currnet_len:max_len;
            return std::make_shared<Leaf>(key, level, val);
        }
    }

public:
    JsonExplorer(int style_id,int icon_id){
        icon_factory.set_id(icon_id);
        style_factory.set_id(style_id);
    }

    void _load(std::string filename){
        std::ifstream ifs(filename);
        if(!ifs.is_open()){
            std::printf("file not exist.\n");
            return;
        }
        std::stringstream buffer;
        buffer << ifs.rdbuf();
        std::string raw_json = buffer.str();
        // 格式化json
        std::string processed_json = preprocess_json(raw_json);
        // 解析json
        json j = json::parse(processed_json);
        // 转成所实现的组合模式
        root = parse_json(j, "root", 0);
    }

    //打印json组合模式
    void show(){
        shared_ptr<Icon> icon=icon_factory.create();
        shared_ptr<Style> style=style_factory.create(icon);
        if(root!=nullptr){
            ComponentIter iter(root,max_len);
            for(iter;!iter.is_end();iter.next()){
                iter.draw(*style);
            }
        }else{
            std::cout<<"file not loaded.\n";
        }
    }

};