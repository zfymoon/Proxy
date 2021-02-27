//
// Created by Zmoon on 2021/2/26.
//

#ifndef ZHUQUE_CONFIG_H
#define ZHUQUE_CONFIG_H

#include <map>
#include <string>
#include <utility>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

class Config {
private:
    std::string configPath;
    std::map<std::string,std::string> config{};
public:
    explicit Config(std::string  path):configPath(std::move(path)){
        initConfig();
    }

    void initConfig(){
        std::ifstream  input(configPath);
        if(input){
            std::string tmp;
            std::vector<std::string> tmpResult;
            while(getline(input,tmp)){
                boost::trim(tmp);
                if(!tmp.empty() && !tmp.starts_with("#")){
                    boost::algorithm::split(tmpResult,tmp,boost::is_any_of("="));
                    if(tmpResult.size() >= 2){
                        config[tmpResult[0]] = tmpResult[1];
                        tmpResult.clear();
                    }
                }
            }

        }

    }

    std::string & operator[](const std::string & key){
        if(!config.count(key)){
            config[key] = std::string();
        }
        return config[key];
    }

};


#endif //ZHUQUE_CONFIG_H
