//
// Created by Zmoon on 2021/2/27.
//

#ifndef ZHUQUE_LOG_H
#define ZHUQUE_LOG_H
#include <string>
#include <iostream>
class Log {
public:
    static void e(const std::string & tag,const std::string & message){
        std::cerr<<"["<<tag<<"]"<<message<<std::endl;
    }
    static void d(const std::string & tag,const std::string & message){
        std::cout<<"["<<tag<<"]"<<message<<std::endl;
    }
};


#endif //ZHUQUE_LOG_H
